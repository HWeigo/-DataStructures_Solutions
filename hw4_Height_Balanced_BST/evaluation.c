#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "evaluation.h"
#include "tree.h"
#include "hbt.h"

#define DEBUG_HBT
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

	int nodesNum = 0;
	size_t numGet1, numGet2;
	int char1;
	char char2;
	while(!feof(fptr))
	{
		numGet1 = fread(&char1, sizeof(int), 1, fptr);
        if(feof(fptr))
        {
            break;
        }
        numGet2 = fread(&char2, sizeof(char), 1, fptr);
        if((numGet1 != 1) || (numGet2 != 1) || char2 >= 4) 
        {
			fprintf(stdout, "%d,%d,%d\n", isValid, isBST, isHeightBalanced);
            fclose(fptr);
			return false;
        }
		nodesNum++;
	}
	isValid = 1;

	int *keys = malloc(sizeof(int) * nodesNum);
	char *branchs = malloc(sizeof(char) * nodesNum);
	fseek(fptr, 0, SEEK_SET);
	for(int i=0; i<nodesNum; i++)
	{
		numGet1 = fread(&char1, sizeof(int), 1, fptr);
        numGet2 = fread(&char2, sizeof(char), 1, fptr);
		keys[i] = char1;
		branchs[i] = char2;
#ifdef DEBUG_HBT
		//printf("%d %c\n", keys[i], branchs[i] + 0x30);
#endif
	}

	Tnode *root = NULL;
	int idx = 0;
	//root = PreorderBSTConstruct(keys, &idx, nodesNum, 10000);
	root = TreeReconstruct(keys, branchs, &idx, nodesNum);
	if(root == NULL)
	{
		free(keys);
		fclose(fptr);
		return false;
	}

	isBST = CheckBST(root);
	isHeightBalanced = 1;
	CheckHeightBalance(root, &isHeightBalanced);
#ifdef DEBUG_HBT 
 	PrintTreePreorder(root);
#endif 

	fprintf(stdout, "%d,%d,%d\n", isValid, isBST, isHeightBalanced);
	fclose(fptr);
	return true;
}
 

