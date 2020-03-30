#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "evaluation.h"
#include "hbt.h"
#include "tree.h"
#include "avl_constructor.h"

int main(int argc, char **argv)
{
//	bool isSuccess = true;
//	//isSuccess = Txt2Binary(argv[1], argv[2]);
//	//isSuccess = Binary2Txt(argv[1], argv[2]);
//	isSuccess = Evaluation(argv[1]); 
//	if(isSuccess == false)
//	{
//		return EXIT_FAILURE;
//	}
	Tnode *root = NULL;
	int isUnbalanced = 0;
	root = Insert(root, -5, &isUnbalanced);
	root = Insert(root, -4, &isUnbalanced);
	root = Insert(root, -3, &isUnbalanced);
	printf("print tree.\n");
	PrintTreePreorder(root);
	root = Insert(root, -2, &isUnbalanced);
	printf("print tree.\n");
	PrintTreePreorder(root);
	root = Insert(root, -1, &isUnbalanced);
	printf("print tree.\n");
	PrintTreePreorder(root);
	root = Insert(root, 0, &isUnbalanced);
	root = Insert(root, 1, &isUnbalanced);
	root = Insert(root, 2, &isUnbalanced);
	root = Insert(root, 3, &isUnbalanced);
	root = Insert(root, 4, &isUnbalanced);
	
	printf("print tree.\n");
	PrintTreePreorder(root);

	return EXIT_SUCCESS;
}
