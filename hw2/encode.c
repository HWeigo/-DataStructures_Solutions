#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "tree_construct.h"
#include "encode.h"

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
	
	Queue *trail = malloc(sizeof(*trail));
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

void Enqueue(Queue *q, int value)
{
	
}
