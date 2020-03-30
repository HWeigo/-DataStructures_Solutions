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
	bool isSuccess = true;

	if((argc < 3) || (argc > 4))
	{
		fprintf(stderr, "wrong commend.");
		return EXIT_FAILURE;
	}

	if(!strcmp(argv[1], "-b"))
	{
		isSuccess = AVLConstruct(argv[2], argv[3]);
	}
	else if(!strcmp(argv[1], "-e"))
	{
		isSuccess = Evaluation(argv[2]); 
	}
	else if(!strcmp(argv[1], "-t2b"))
	{
		isSuccess = Txt2Binary(argv[2], argv[3]);
	}
	else if(!strcmp(argv[1], "-b2t"))
	{
		isSuccess = Binary2Txt(argv[2], argv[3]);
	}
	else
	{
		fprintf(stderr, "wrong commend.");
		return EXIT_FAILURE;
	}

	if(isSuccess == false)
	{
		return EXIT_FAILURE;
	}

//	Tnode *root = NULL;
//	int isUnbalancedInsert = 0;
//	int isUnbalancedDelete = 0;
//	root = Insert(root, 3, &isUnbalancedInsert);
//	root = Insert(root, 3, &isUnbalancedInsert);
//	root = Insert(root, 3, &isUnbalancedInsert);
//	root = Insert(root, 3, &isUnbalancedInsert);
//	root = Insert(root, 1, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);
//	root = Insert(root, 1, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);
//	root = Insert(root, 1, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);	
//	root = Insert(root, 1, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);	
//	root = Insert(root, 2, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);	
//	root = Insert(root, 2, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);
//	root = Insert(root, 2, &isUnbalancedInsert);
//	printf("print tree.\n");
//	PrintTreePreorder(root);
//	root = Delete(root, 3, &isUnbalancedDelete);	
//	printf("print tree.\n");
//	PrintTreePreorder(root);

	return EXIT_SUCCESS;
}
