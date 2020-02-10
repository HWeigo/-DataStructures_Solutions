#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_list.h"

#define DEBUG_HW

static typedef struct _subList {
	Node *node;
	struct subList *next;
} subList;

static typedef struct _ListHeads {
    subList *list;
	long size;
    struct ListHeads *next;
} ListHeads;

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

static subList *subList_construct(Node *addr)
{
    subList *p = malloc(sizeof(subList));
    p->node = addr;
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
        fclose(fptr);
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
	while(p != NULL)
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

Node *List_Shellsort(Node *list, long *n_comp)
{
	for k in list 
	
	Node *p = list;
	// count list size
	long size = 0;
	while(p != NULL)
	{
		p = p->next;
		++size;
	}

	ListHeads *head;
	ListHeads *tail;
	long subList_size = 0;
	lptr = malloc(sizeof(ListHeads));
	head->list = subList_create(p, size, k, &subList_size);
	head->size = subList_size;
	head->next = NULL;
	tail = head;

}

static void subList_sort(Node *nptr, long size, long k)
{
	ListHeads *head = NULL;
	ListHeads *tail = NULL;
	long subList_size = 0;

	head = malloc(sizeof(ListHeads));
	head->list = subList_create(nptr, size, k, subList_size);
	head->size = subList_size;
	head->next = NULL;
	tail = head;
	for(long i=0; i<k; ++i)
	{
		tail->next = malloc(sizeof(ListHeads));
		tail = tail->next;
		tail->list = subList_create(nptr, size, k, subList_size);
		tail->size = subList_size;
		tail->next = NULL;

		nptr = nptr->next;
	}
}

static subList *subList_create(Node *nptr, long size, long k, long *subList_size)
{
	if(nptr == NULL)
	{
		return NULL;
	}

	subList *head = NULL;
    subList *tail = NULL;
	
	head = subList_construct(nptr);
	tail = head;
	*subList_size = 1;
	while(nptr != NULL)
	{
		for(long i=0; i<k;++i)
		{
			nptr = nptr->next;
			if(nptr == NULL)
			{
				return head;
			}
		}
		(*subList_size)++;
		tail->next = subList_construct(nptr);
		tail = tail->next;
	}
}

static void subList_print(subList *head)
{
	while(head != NULL)
	{
		printf("%ld ", (head->node)->value);
		head = head->next;
	} 
}
