#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "tree_construct.h"

int main(int argc, char **argv)
{
//	if(argc != 4)
//	{
//		return EXIT_FAILURE;
//	}
	
//	bool isSuccess = false;

//	TreeNode *root = NULL;
	//isSuccess = TreeConstruct(argv[1], root);
//	if(isSuccess == false)
//	{
//		fprintf(stderr, "tree construct fail.");
//		return EXIT_FAILURE;
//	}

    FILE *fptr = NULL;
    fptr = fopen(argv[1], "r");
    if(fptr == NULL)
    {   
        fprintf(stderr, "fopen failed.");
        return false;
    }   

    int id; 
    int width;
    int height;
    int numGet = 0;
	char temp;
    do  
    {   
        numGet = fscanf(fptr, "%d(%d,%d)\n", &id, &width, &height);
		if(numGet == 0)
		{
			//numGet = fgetc(fptr);
			numGet = fscanf(fptr, "%c\n", &temp);
			printf("temp:%c\n", temp);
			width = 0;
			height = 0;
		}
        printf("num match: %d\n", numGet);
        printf("id: %d\n", id);
        printf("width: %d\n", width);
        printf("height: %d\n", height);
    }while(!feof(fptr));



	return EXIT_SUCCESS;
}
