#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "tree_construct.h"
#include "encode.h"

static ListNode *ListNodeConstruct(int value);

int **ConstructTable(TreeNode *root)
{
	int treeHeight = CalTreeHeight(root);
	printf("%d\n", treeHeight);
	int **table;
	table = malloc(sizeof(int*) * 256);
	for(int i=0; i<256; i++)
	{
		table[i] = malloc(sizeof(int) * treeHeight);
	}
	
	Stack *trail = malloc(sizeof(*trail));
	trail->head = NULL;
	trail->tail = NULL;

	free(trail);

	return table;
}

void FreeTable(int **table)
{
	for(int i=0; i<256; i++)
	{
		free(table[i]);
	}
	free(table);
}

void Push(Stack *s, int value)
{
	if(s->head == NULL)
	{
		s->head = ListNodeConstruct(value);
		s->tail =s->head;
		return;
	}
	(s->tail)->next = ListNodeConstruct(value);
	s->tail = (s->tail)->next;
}

int Pop(Stack *s)
{
	if(s->head == NULL)
	{
		return -1;
	}
	if(s->head == s->tail)
	{
		int topValue = (s->head)->value;
		free(s->head);
		s->head = NULL;
		s->tail = NULL;
		return topValue;
	}
	
	ListNode *p = s->head;
	ListNode *q = p->next;
	while(q != s->tail)
	{
		p = q;
		q = p->next;
	}

	// q is now tail of stack, p is the node in front of q
	int topValue = q->value;
	p->next = NULL;
	free(q);

	return topValue;
}

static ListNode *ListNodeConstruct(int value)
{
    ListNode *p = malloc(sizeof(*p));
    p->next = NULL;
    p->value = value;
    return p;
}
