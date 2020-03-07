#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_construct.h"

bool TreeConstruct(char *filename, TreeNode *root)
{
	FILE *fptr = NULL;
	fptr = fopen(filename, "r");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return false;
	}

	int id;
	int width;
	int height;
	int numGet = 0;
	do
	{
		numGet = fscanf(fptr, "%d(%d,%d)\n", &id, &width, &height);
		printf("num match: %d\n", numGet);
		printf("id: %d\n", id);
		printf("width: %d\n", width);
		printf("height: %d\n", height);
	}while(!feof(fptr));

	fclose(fptr);
	return true;
}
