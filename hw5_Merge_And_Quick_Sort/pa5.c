#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

#define DEBUG_HW 

static long *LoadIntoArray(char *filename, int *size);
static void printArray(long *array, int size);

int main(int argc, char **argv)
{
    if(argc != 4)
    {   
        fprintf(stderr, "missing argument.");
		return EXIT_FAILURE;
    }

	int size = 0;
	long *array = LoadIntoArray(argv[2], &size);
	if(array == NULL)
	{
		return EXIT_FAILURE;
	}


    return EXIT_SUCCESS;
}

static long *LoadIntoArray(char *filename, int *size)
{
	FILE *fptr;
	fptr = fopen(filename, "r");

	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		fclose(fptr);
		return NULL;
	}

	long tmp1;
	int cnt  = 0;
	while(fread(&tmp1, sizeof(long), 1,fptr))
	{
		cnt++;
	}

	*size = cnt;

	if((*size) == 0)
	{
		fclose(fptr);
		return NULL;
	}

	fseek(fptr, 0, SEEK_SET);

	long *lptr = NULL;
	lptr = malloc(sizeof(long) * cnt);

	size_t tmp2;
	for(int i=0; i<(*size); i++)
	{
		tmp2 = fread(&(lptr[i]), sizeof(long),1,fptr);
		if(tmp2 != 1)
		{
			free(lptr);
			fclose(fptr);
			return NULL;
		}
	}

	fclose(fptr);

#ifdef DEBUG_HW
	printf("Before sorting:\n");
	printArray(lptr, *size);
#endif
	return lptr;
}


static void printArray(long *array, int size)
{
	for(int i=0; i<size;++i)
	{
		printf("%ld ", array[i]);
	}
	printf("\n");
}
