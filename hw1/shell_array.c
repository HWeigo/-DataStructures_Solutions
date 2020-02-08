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
	return lptr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
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



