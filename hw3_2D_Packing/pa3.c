#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree_construct.h"
#include "packing_operation.h"

int main(int argc, char **argv)
{
//	if(argc != 4)
//	{
//		return EXIT_FAILURE;
//	}
  
	bool isSuccess = false;

	TreeNode *root = NULL;
	isSuccess = TreeConstruct(argv[1], &root);
	if(isSuccess == false)
	{
		fprintf(stderr, "tree construct fail.");
		return EXIT_FAILURE;
	}
	//PreorderTraversal(root);
	
	CalcDimension(root);
	PrintDimension(root);
	TreeDestroy(root);

	return EXIT_SUCCESS;
}
