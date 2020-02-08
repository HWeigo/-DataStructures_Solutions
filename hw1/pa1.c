#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "shell_array.h"

int main(int argc, char ** argv)
{
    //argv[1]: name of input file (binary)
    //argv[2]: name of output file (binary)
    if(argc != 3)
    {   
        return EXIT_FAILURE;
    }   
    int size;    
	long *arr = NULL;
    
	arr = Array_Load_From_File(argv[1], &size);
	printf("cnt = %d\n", size);

	int writeNum;
	writeNum = Array_Save_To_File(argv[2], arr, size);
    if(writeNum != size)
	{
		return EXIT_FAILURE;
	}

	free(arr);
    return EXIT_SUCCESS;

}

