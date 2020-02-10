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

int Array_Save_To_File(char *filename, long *array, int size)
{
#ifdef DEBUG_HW
	printf("After sorting:\n");
	printArray(array, size);
#endif

	FILE *fptr;
	fptr  = fopen(filename, "w");

	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		fclose(fptr);
		return -1;
	}
	
	int cnt = 0;
	for(int i=0; i<size; ++i)
	{
		size_t tmp = fwrite(&array[i], sizeof(long), 1, fptr);
		if(tmp != 1)
		{
			fclose(fptr);
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

void Array_Shellsort(long *array, int size, long *n_comp)
{
	long k = 1;
	int p = 1;
	while(k < size)
	{
		k = k*3 +1;
		p += 1;
	}
	k = (k-1)/3;

	long temp;
	int i;
	while(k >= 1)
	{
		for(int j=k; j<size; j++)
		{
			temp = array[j];
			i = j;
			while((i >= k) && (array[i-k] > temp))
			{
				array[i] = array[i-k];
				i -= k;
				(*n_comp)++;
			}
			array[i] = temp;
		}
		
		k = (k-1)/3;
	}
}

