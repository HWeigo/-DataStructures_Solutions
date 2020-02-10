#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char ** argv)
{
    //argv[1]: name of input file (binary)
    //argv[2]: name of output file (binary)
    if(argc != 4)
    {   
        return EXIT_FAILURE;
    } 

	if(!strcmp(argv[1], "-l"))
	{
		printf("Sort in linked list.\n");
		Node *head = NULL;
		head = List_Load_From_File(argv[2]);
		long num_comp =0;
		head = List_Shellsort(head, &num_comp);
		printf("%ld\n", num_comp);
		
		int writeNum;
		writeNum = List_Save_To_File(argv[3], head);
		printf("%d\n", writeNum);
		if(writeNum == 0)
		{
			return EXIT_FAILURE;
		}
	
		//free memory in nodes
		while(head != NULL)
		{
			Node *p  = head->next;
			free(head);
			head = p;
		}
	}

	if(!strcmp(argv[1], "-a"))
	{
		printf("Sort in array.\n");

	    int size;    
		long *arr = NULL;
	    
		arr = Array_Load_From_File(argv[2], &size);
		printf("cnt = %d\n", size);
		
		long num_comp = 0;
		Array_Shellsort(arr, size, &num_comp);
		printf("%ld\n", num_comp);
	
		int writeNum;
		writeNum = Array_Save_To_File(argv[3], arr, size);
	    if(writeNum != size)
		{
			return EXIT_FAILURE;
		}
	
		free(arr);
	}

	
    return EXIT_SUCCESS;

}

