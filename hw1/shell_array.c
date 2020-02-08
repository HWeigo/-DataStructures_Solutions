#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_array.h"

#define DEBUG_HW

static void printArray(long *array, int size)
{
	for(int i=0; i<size;++i)
	{
		printf("%ld ", array[i]);
	}
	printf("\n");
}

long *Array_Load_From_File(char *filename, int *size)
{
	FILE *fptr;
	fptr = fopen(filename, "r");
	
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
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
		return NULL;
	}

	fseek(fptr, 0, SEEK_SET);

	long *lptr = NULL;
	lptr = malloc(sizeof(long) * cnt);
	
	size_t tmp2;
	for(int i=0; i<(*size); i++)
	{
		tmp2 = fread(&(lptr[i]), sizeof(long),1,fptr);
		if(tmp2 != 1) return NULL;
	}
	
	fclose(fptr);

#ifdef DEBUG_HW
	printf("Before sorting:\n");
	printArray(lptr, *size);
#endif
	return lptr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
#ifdef DEBUG_HW
	printf("After sorting:\n");
	printArray(array, *size);
#endif

	FILE *fptr;
	fptr  = fopen(filename, "w");

	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
	}
	
	int cnt = 0;
	for(int i=0; i<size; ++i)
	{
		size_t tmp = fwrite(&array[i], sizeof(long), 1, fptr);
		if(tmp != 1)
		{
			return -1;
		}
		else
		{
			cnt++;
		}
	}

	fclose(fptr);
	return cnt;

}



