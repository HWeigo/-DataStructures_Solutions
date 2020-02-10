#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_list.h"

#define DEBUG_HW

//static Node *List_insert(Node *head, long v);
static Node *Node_construct(long v);
static void printList(Node *head);
static void List_destroy(Node *head);

//static Node *List_insert(Node *head, long v)
//{
//	Node *p = Node_construct(v);
//	p->next = head;
//	return p;
//}

static void List_destroy(Node *head)
{
	while(head != NULL)
	{
		Node *p = head->next;
		free(head);
		head = p;
	}

}

static Node *Node_construct(long v)
{
	Node *p = malloc(sizeof(Node));
	p->value = v;
	p->next = NULL;
	return p;
}

static void printList(Node *head)
{
	Node *p = head;
	int cnt = 0;
	while(p != NULL)
	{
		printf("%ld ", p->value);
		p = p->next;
		cnt++;
	}
	printf("\n Number in linked list: %d\n", cnt);
}

Node *List_Load_From_File(char *filename)
{
	FILE *fptr;
    fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "fopen failed.");
        return NULL;
    }

    long tmp1;
    int cnt  = 0;
    while(fread(&tmp1, sizeof(long), 1,fptr))
    {   
        cnt++;
    }   

//	Node *head = NULL;
//	fseek(fptr, 0, SEEK_SET);
//	size_t tmp2;
//	for(int i=cnt-1;i>=0;i--)
//	{
//		fseek(fptr, sizeof(long)*i, SEEK_SET);
//		tmp2 = fread(&tmp1, sizeof(long), 1, fptr);
//		if(tmp2 != 1) return NULL; // Last element fread return tmp2=0
//		head = List_insert(head, tmp1);	
//	}

	Node *head = NULL;
	Node *tail = NULL;
	size_t tmp2;

	fseek(fptr, 0, SEEK_SET);
	tmp2 = fread(&tmp1, sizeof(long), 1, fptr);
	if(tmp2 != 1) return NULL; // Last element fread return tmp2=0
	head = Node_construct(tmp1);
	tail = head;
	
	for(int i=0; i<cnt-1; i++)
	{
		tmp2 = fread(&tmp1, sizeof(long), 1, fptr);
		if(tmp2 != 1) return NULL; // Last element fread return tmp2=0
		tail->next = Node_construct(tmp1);
		tail = tail->next;
	}

	fclose(fptr);
#ifdef DEBUG_HW
	printList(head);
#endif
	return head;
}

int List_Save_To_File(char *filename, Node *head)
{
	FILE *fptr;
	fptr = fopen(filename, "w");

	Node *p = head;
	int cnt = 0;
	while(p->next != NULL)
	{
		size_t tmp = fwrite(&(p->value), sizeof(long), 1, fptr);
		if(tmp != 1)
		{
			return -1;
		}
		else
		{
			p = p->next;
			cnt++;
		}
	}

	fclose(fptr);
	return cnt;
}

