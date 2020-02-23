#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "tree_construct.h"
#include "encode.h"

static ListNode *ListNodeConstruct(int value);
static void Push(Stack *s, int value);
static void Pop(Stack *s);
static void PrintStack(Stack *s);
void Encode(TreeNode *root, Stack *trail, int **table, int *bitWidth, FILE *fptr);

int **ConstructTable(TreeNode *root, char *codeFilename, int *bitWidth)
{
	int treeHeight = CalTreeHeight(root);
	printf("%d\n", treeHeight);
	int **table;
	table = malloc(sizeof(int*) * 256);
	for(int i=0; i<256; i++)
	{
		table[i] = malloc(sizeof(int) * treeHeight);
		bitWidth[i] = 0;
	}


	// Initialization
	for(int i=0;i<256;i++)
	{
		for(int j=0;j<treeHeight;j++)
		{
			table[i][j] = -1;
		}
	}
	
	Stack *trail = malloc(sizeof(*trail));
	trail->head = NULL;
	trail->tail = NULL;
	
	FILE *fptr = fopen(codeFilename, "w+");
	Encode(root, trail, table, bitWidth, fptr);

	fclose(fptr);
	free(trail);

	return table;
}

void Encode(TreeNode *root, Stack *trail, int **table, int *bitWidth, FILE *fptr)
{
	if(fptr == NULL)
	{
		return;
	}

	printf("%c: %ld\n", root->charIdx, root->freq);
	if(root->charIdx != -1)
	{
		PrintStack(trail);
		fprintf(fptr,"%c:",root->charIdx);
		ListNode *head = trail->head;
		int bit = 0;
		while(head != NULL)
		{
			table[root->charIdx][bit] = head->value;
			bit++;
			fprintf(fptr,"%d",head->value);
			head = head->next;
		}
		fprintf(fptr,"\n");
		bitWidth[root->charIdx] = bit;
		Pop(trail);

		return;
	}
	Push(trail, 0);
	Encode(root->left, trail, table, bitWidth, fptr);
	Push(trail, 1);
	Encode(root->right, trail, table, bitWidth, fptr);

	Pop(trail);

}


void FreeTable(int **table)
{
	for(int i=0; i<256; i++)
	{
		free(table[i]);
	}
	free(table);
}

static void Push(Stack *s, int value)
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

static void Pop(Stack *s)
{
	if(s->head == NULL)
	{
		return;
	}
	if(s->head == s->tail)
	{
		//int topValue = (s->head)->value;
		free(s->head);
		s->head = NULL;
		s->tail = NULL;
		return;
	}
	
	ListNode *p = s->head;
	ListNode *q = p->next;
	while(q != s->tail)
	{
		p = q;
		q = p->next;
	}

	// q is now tail of stack, p is the node in front of q
	//int topValue = q->value;
	p->next = NULL;
	s->tail = p;
	free(q);

	return;
}

static void PrintStack(Stack *s)
{
	ListNode *head = s->head;
	while(head != NULL)
	{
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

static ListNode *ListNodeConstruct(int value)
{
    ListNode *p = malloc(sizeof(*p));
    p->next = NULL;
    p->value = value;
    return p;
}
