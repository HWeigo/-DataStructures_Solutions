#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "shell_array.h"
#include "shell_list.h"

#define list
//#define array
int main(int argc, char ** argv)
{
    //argv[1]: name of input file (binary)
    //argv[2]: name of output file (binary)
    if(argc != 3)
    {   
        return EXIT_FAILURE;
    } 
#ifdef array 
    int size;    
	long *arr = NULL;
    
	arr = Array_Load_From_File(argv[1], &size);
	printf("cnt = %d\n", size);
	
	long num_comp = 0;
	Array_Shellsort(arr, size, &num_comp);

	int writeNum;
	writeNum = Array_Save_To_File(argv[2], arr, size);
    if(writeNum != size)
	{
		return EXIT_FAILURE;
	}

	free(arr);
#endif

#ifdef list
	Node *head = NULL;
	head = List_Load_From_File(argv[1]);
	long num_comp =0;
	head = List_Shellsort(head, &num_comp);

	int writeNum;
	writeNum = List_Save_To_File(argv[2], head);
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
	
#endif 
    return EXIT_SUCCESS;

}

