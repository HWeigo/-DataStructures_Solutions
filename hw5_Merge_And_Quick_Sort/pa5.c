#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

#define DEBUG_HW 

static long *LoadIntoArray(char *filename, int *size);
static void printArray(long *array, int size);
static int SaveToFile(char *filename, long *array, int size);
static bool Txt2Binary(char *inputFile, char *outputFile);

int main(int argc, char **argv)
{
    if(argc != 4)
    {   
        fprintf(stderr, "missing argument.");
		return EXIT_FAILURE;
    }

	if(!strcmp(argv[1], "-c"))
	{
		Txt2Binary(argv[2], argv[3]);
		return EXIT_SUCCESS;
	}
	
	int size = 0;
	long *array = LoadIntoArray(argv[2], &size);
	if(array == NULL)
	{
		return EXIT_FAILURE;
	}

	if(!strcmp(argv[1], "-q"))
	{
		Quick_Sort(array, size);
		printArray(array, size);
	}

	if(!strcmp(argv[1], "-m"))
	{
	}
	
	int num2File = SaveToFile(argv[3], array, size);
	if(size != num2File)
	{
		fprintf(stderr, "fail to save array into file.");
		free(array);
		return EXIT_FAILURE;
	}
	free(array);

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

static int SaveToFile(char *filename, long *array, int size)
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


static void printArray(long *array, int size)
{
	for(int i=0; i<size;++i)
	{
		printf("%ld ", array[i]);
	}
	printf("\n");
}


static bool Txt2Binary(char *inputFile, char *outputFile)
{
	FILE *inFptr = NULL;
	inFptr = fopen(inputFile, "r");

	if(inFptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return false;
	}

	FILE *outFptr = NULL;
	outFptr = fopen(outputFile, "w");

	if(outFptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return false;
	}

	int numGet = 0;
	long char1;
	do
	{
		numGet = fscanf(inFptr, "%ld\n", &char1);
		if(numGet != 1)
		{
			fprintf(stderr, "numGet !=2.");
			fclose(inFptr);
			fclose(outFptr);
			return false;
		}
		//printf("%d %s\n", char1, char2);
		fwrite(&char1, sizeof(long), 1, outFptr);
	}while(!feof(inFptr));

	fclose(inFptr);
	fclose(outFptr);
	return true;
}

