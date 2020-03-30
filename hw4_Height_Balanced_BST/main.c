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
	//isSuccess = Txt2Binary(argv[1], argv[2]);
	//isSuccess = Binary2Txt(argv[1], argv[2]);
	//isSuccess = Evaluation(argv[1]); 
	isSuccess = AVLConstruct(argv[1]);
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
