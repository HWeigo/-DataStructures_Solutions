#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree_construct.h"
#include "packing_operation.h"

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		fprintf(stderr, "argc != 5.");
		return EXIT_FAILURE;
	}
  
	bool isSuccess = false;

	TreeNode *root = NULL;
	isSuccess = TreeConstruct(argv[1], &root);
	if(isSuccess == false)
	{
		fprintf(stderr, "tree construct fail.\n");
		return EXIT_FAILURE;
	}

    FILE *fptr = NULL;
    fptr = fopen(argv[2], "w");
    if(fptr == NULL)
    {   
        fprintf(stderr, "fopen failed.");
        return false;
    }
	PreorderTraversal(root, fptr);
	fclose(fptr);

	CalcDimension(root);
	fptr = fopen(argv[3], "w");
    if(fptr == NULL)
    {   
        fprintf(stderr, "fopen failed.");
        return false;
    }
	PrintDimension(root, fptr);
	fclose(fptr);
	
	CalcCoordinates(root);
    fptr = fopen(argv[4], "w");
    if(fptr == NULL)
    {   
        fprintf(stderr, "fopen failed.");
        return false;
    }
	PrintCoordinates(root, fptr);
	fclose(fptr);

	TreeDestroy(root);

	return EXIT_SUCCESS;
}
