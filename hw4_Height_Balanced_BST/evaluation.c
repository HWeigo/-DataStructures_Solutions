#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "evaluation.h"
#include "hbt.h"

// Return true only in input file is valid 
bool Evaluation(char *filename)
{
	int isValid = -1; // -1: cannot open file, 0: wrong format, 1: correct format
	int isBST = 0; // 0: not a BST, 1: is a BST 
	int isHeightBalanced = 0; // 0: tree is not height-balaced, 1: is height-balanced 

	FILE *fptr = NULL;
	fptr = fopen(filename, "r");

	if(fptr == NULL)
	{
		fprintf(stdout, "%d,%d,%d\n", isValid, isBST, isHeightBalanced);
		return false;
	}
	isValid = 0;

	size_t numGet1, numGet2;
	int char1;
	char char2[10];
	while(!feof(fptr))
	{
		numGet1 = fread(&char1, sizeof(int), 1, fptr);
        if(feof(fptr))
        {
            break;
        }
        numGet2 = fread(&char2, sizeof(char), 1, fptr);
        if((numGet1 != 1) || (numGet2 != 1) || char2[0] >= 4) 
        {
			fprintf(stdout, "%d,%d,%d\n", isValid, isBST, isHeightBalanced);
            return false;
        }

	}
	isValid = 1;
 	
	fprintf(stdout, "%d,%d,%d\n", isValid, isBST, isHeightBalanced);
	return true;
}
 
Tnode *PreorderBstConstruct(FILE *fptr, int ub, int *isValid)
{
	size_t numGet1, numGet2;
	if((feof(fptr) || (*isValid == 0)))
	{
		return NULL;
	}
	numGet1 = fread(&char1, sizeof(int), 1, fptr);
    if(feof(fptr))
    {
        return NULL;
    }
    numGet2 = fread(&char2, sizeof(char), 1, fptr);
    if((numGet1 != 1) || (numGet2 != 1) || char2[0] >= 4) 
    {
		isValid = 0;
        return NULL;
    }

	
	if()



}


Tnode *CreateTNode(int key)
{
	Tnode *node = malloc(sizeof(*node));
	node->key = key;
	node->balance = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}
