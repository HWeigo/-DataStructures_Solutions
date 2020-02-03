#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_array.h"

int countIntegers(char *filename)
{
	FILE *fptr;
	fptr = fopen(filename, "r");
	
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return -1;
	}

	long tmp;
	int cnt  = 0;
	while(fread(&tmp, sizeof(long), 1,fptr))
	{
		cnt++;
	}

	fclose(fptr);
	return cnt;
}

long *Array_Load_From_File(char *filename, int *size)
{
	long *lptr = NULL;
	*lptr = 1;
	return lptr;
}

int main(int argc, char ** argv)
{
	//argv[1]: name of input file (binary)
	//argv[2]: name of output file (binary)
	if(argc != 3)
	{
		return EXIT_FAILURE;
	}

	printf("cnt = %d\n", countIntegers(argv[1]));
	
	return EXIT_SUCCESS;

}

