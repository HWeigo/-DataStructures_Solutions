#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "evaluation.h"
#include "tree.h"
#include "hbt.h"

#define DEBUG_TREE

Tnode *TreeReconstruct(int *arr, char *branch, int *idx, int size)
{
	if((*idx) == size)
	{
		return NULL;
	}
	Tnode *node = CreateTreeNode(arr[*idx]);
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	int currIdx = *idx;
	(*idx)++;
	
	node->left = NULL;
	node->right = NULL;
	if((branch[currIdx] == 2) || (branch[currIdx] == 3))
	{
		node->left = TreeReconstruct(arr, branch, idx, size);
	}
	if((branch[currIdx] == 1) || (branch[currIdx] == 3))
	{
		node->right = TreeReconstruct(arr, branch, idx, size);
	}
	
	return node;
}

Tnode *PreorderBSTConstruct(int *arr, int *idx, int size, int ub)
{
	if((*idx) == size)
	{
		return NULL;
	}
	if(arr[*idx] > ub)
	{
		return NULL;
	}
	Tnode *node = CreateTreeNode(arr[*idx]);
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	(*idx)++;
	node->left = PreorderBSTConstruct(arr, idx, size, node->key);
	node->right = PreorderBSTConstruct(arr, idx, size, ub);

	return node;
}

Tnode *CreateTreeNode(int key)
{
	Tnode *node = malloc(sizeof(*node));
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	node->key = key;
	node->balance = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int CheckBST(Tnode *root)
{
	if(root == NULL)
	{
		return 1;
	}
	if((root->left != NULL) && ((root->left)->key > root->key))
	{
		return 0;
	}
	if((root->right != NULL) && ((root->right)->key < root->key))
	{
		return 0;
	}
	if((!CheckBST(root->left) || (!CheckBST(root->right))))
	{
		return 0;
	}

	return 1;
}

static int MAX(int a, int b)
{
	return (a>b?a:b);
}

int CheckHeightBalance(Tnode *root, int *isHB)
{
	if(root == NULL)
	{
		return 0;
	}
	int left = CheckHeightBalance(root->left, isHB);
	int right = CheckHeightBalance(root->right, isHB);
	root->balance = left-right;
	if((root->balance > 1) || (root->balance < -1))
	{
		*isHB = 0;
	}
	return (1 + MAX(left, right));
}

void TreeDestroy(Tnode *root)
{
	if(root == NULL)
	{
		return;
	}
	TreeDestroy(root->left);
	TreeDestroy(root->right);
	free(root);
}

void PrintTreePreorder(Tnode *root)
{
	if(root == NULL)
	{
		return;
	}
	int num = 0;
	if(root->left != NULL)
	{
		num += 2;
	}
	if(root->right != NULL)
	{
		num += 1;
	}
	fprintf(stdout, "%d %d %d\n", root->key, (int)root->balance, num);
	PrintTreePreorder(root->left);
	PrintTreePreorder(root->right);
}

void SaveTreeToFile(Tnode *root, FILE *fptr)
{
	if(root == NULL)
	{
		return;
	}
	char branch = 0;
	if(root->left != NULL)
	{
		branch += 2;
	}
	if(root->right != NULL)
	{
		branch += 1;
	}
    fwrite(&(root->key), sizeof(int), 1, fptr);
	fwrite(&branch, sizeof(char), 1, fptr);

	SaveTreeToFile(root->left, fptr);
	SaveTreeToFile(root->right, fptr);
}
