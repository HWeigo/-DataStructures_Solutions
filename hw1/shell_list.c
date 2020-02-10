#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_list.h"

//#define DEBUG_HW

typedef struct _subList {
	Node *node;
	struct _subList *next;
} subList;

typedef struct _ListHeads {
    subList *list;
	long size;
    struct _ListHeads *next;
} ListHeads;

//static Node *List_insert(Node *head, long v);
static Node *Node_construct(long v);
//static void List_destroy(Node *head);
static subList *subList_construct(Node *addr);
static Node *subList_sort(Node *nptr, long size, long k, long *n_comp);
static subList *subList_create(Node *nptr, long size, long k, long *subList_size);
static void bubbleSort(subList *head, long size, long *n_comp);

#ifdef DEBUG_HW 
static void subList_print(subList *head);
static void printList(Node *head);
#endif 

//static Node *List_insert(Node *head, long v)
//{
//	Node *p = Node_construct(v);
//	p->next = head;
//	return p;
//}

//static void List_destroy(Node *head)
//{
//	while(head != NULL)
//	{
//		Node *p = head->next;
//		free(head);
//		head = p;
//	}
//}

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
			fclose(fptr);
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
    long k = 1;
    int p = 1;

	
	Node *output = list;
	// count list size
	long size = 0;
	while(output != NULL)
	{
		output = output->next;
		++size;
	}
	
	while(k < size)
    {   
        k = k*3 +1; 
        p += 1;
    }   
    k = (k-1)/3;

	output = list;
	while(k >= 1)
	{
		output = subList_sort(output, size, k, n_comp);
		k = (k-1)/3;
	}
#ifdef DEBUG_HW 
	printList(output);
#endif

	return output;

}

// bubbleSort used to sort subarray
static void bubbleSort(subList *head, long size, long *n_comp)
{
	if((size == 0) || (head == NULL))
	{
		return;
	}
	bool isChange = true;
	for(long i = 0; i<(size-1); ++i)
	{
		subList *p = head;
		for(long j=0; j<(size-1-i);++j)
		{
			if(((p->node)->value) > ((p->next)->node)->value)
			{
				//swap address in p->node and p->next->node
				Node *tmp = p->node;
				p->node = (p->next)->node;
				(p->next)->node = tmp;

				isChange = true;
			}
			(*n_comp)++;
			p = p->next;
		}
		if(!isChange)
		{
			return;
		}
	}
	return;
}

static void insertionSort(subList *head, long *n_comp)
{

}

static Node *subList_sort(Node *nptr, long size, long k, long *n_comp)
{
	ListHeads *head = NULL;
	ListHeads *tail = NULL;
	long subList_size = 0;

	head = malloc(sizeof(ListHeads));
	head->list = subList_create(nptr, size, k, &subList_size);
	head->size = subList_size;
	head->next = NULL;
	tail = head;
	nptr = nptr->next;
	for(long i=1; i<k; ++i)
	{
		tail->next = malloc(sizeof(ListHeads));
		tail = tail->next;
		tail->list = subList_create(nptr, size, k, &subList_size);
		tail->size = subList_size;
		tail->next = NULL;

		nptr = nptr->next;
	}

	ListHeads *p = head;
	while(p != NULL)
	{
		bubbleSort(p->list, p->size, n_comp);
#ifdef DEBUG_HW
		subList_print(p->list);
		printf("Number in subarray: %ld\n", p->size);
#endif 
		p = p->next;
	} 

	// link nodes in different subList 
	Node *new = (head->list)->node;
	Node *nodeptr = new;
	ListHeads *listprt = head;
	subList *subptr = listprt->list;
	subList *stmp;
	for(long i=0; i<(head->size);++i)
	{
		for(long j=0; j<(k-1); ++j)
		{
			//ltmp = listprt;
			stmp = listprt->list;
			if((listprt->next)->list == NULL)
			{
				nodeptr->next = NULL;
				
				// free memory in ListHeads
				while(head != NULL)
				{
					ListHeads *nextList = head->next;
					free(head);
					head = nextList;
				}
				free(stmp);	
				return new;
			}
			subptr = (listprt->next)->list;
			nodeptr->next = subptr->node;
			nodeptr = nodeptr->next;
#ifdef DEBUG_HW 
			printf("Adding:%ld \n", nodeptr->value);
#endif 
			listprt->list = stmp->next;
			listprt=listprt->next;
			//free subListNode
			free(stmp);

		}
		stmp = listprt->list;

		subptr = head->list;
		if(head->list == NULL)
		{
			nodeptr->next = NULL;
			
			// free memory in ListHeads
			while(head != NULL)
			{
				ListHeads *nextList = head->next;
				free(head);
				head = nextList;
			}
			free(stmp);
			return new;
		}
		nodeptr->next = subptr->node;
		nodeptr = nodeptr->next;
#ifdef DEBUG_HW 
		printf("Adding:%ld \n", nodeptr->value);
#endif 
		listprt->list = stmp->next;
		listprt=head;
		//free subListNode
		free(stmp);
	}
	nodeptr->next = NULL;
	
	// free memory in ListHeads
	while(head != NULL)
	{
		ListHeads *nextList = head->next;
		free(head);
		head = nextList;
	}
	return new;
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
#ifdef DEBUG_HW
				//subList_print(head);
#endif 
				return head;
			}
		}
		(*subList_size)++;
		tail->next = subList_construct(nptr);
		tail = tail->next;
	}

	return head;
}
#ifdef DEBUG_HW 
static void subList_print(subList *head)
{
	while(head != NULL)
	{
		printf("%ld ", (head->node)->value);
		head = head->next;
	} 
	printf("\n");
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
#endif 

