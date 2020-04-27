#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "file_converter.h"

bool Binary2Txt(char *inputFile, char *outputFile)
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

	size_t numGet = 0;
	short m;
	numGet = fread(&m, sizeof(short), 1, inFptr);
	if((numGet != 1) || (m <= 0) || (m>SHRT_MAX))
	{
		fprintf(stderr, "wrong format");
		fclose(inFptr);
		fclose(outFptr);
		return false;
	}
	short n;
	numGet = fread(&n, sizeof(short), 1, inFptr);
	if((numGet != 1) || (n <= 0) || (n>SHRT_MAX))
	{
		fprintf(stderr, "wrong format");
		fclose(inFptr);
		fclose(outFptr);
		return false;
	}

	fprintf(outFptr, "%hd %hd\n",m,n);
	
	short tmp;	
	for(int i=0; i<m;++i)
	{
		for(int j=0;j<(n-1);++j)
		{
			numGet = fread(&tmp, sizeof(short), 1, inFptr);
			if((numGet != 1) || (tmp<SHRT_MIN) || (tmp>SHRT_MAX))
			{
				fprintf(stderr, "wrong format");
				fclose(inFptr);
				fclose(outFptr);
				return false;
			}	
			fprintf(outFptr, "%hd ",tmp);
		}
		numGet = fread(&tmp, sizeof(short), 1, inFptr);
		if((numGet != 1) || (tmp<SHRT_MIN) || (tmp>SHRT_MAX))
		{
			fprintf(stderr, "wrong format");
			fclose(inFptr);
			fclose(outFptr);
			return false;
		}	
		fprintf(outFptr, "%hd\n",tmp);
	}
	
	fclose(inFptr);
	fclose(outFptr);
	return true;
}

void SequenceConstruct(char *filename)
{
	FILE *fptr = fopen(filename, "w");
	if(fptr == NULL)
	{
		return;
	}
	int length = 5;
	fwrite(&length, sizeof(int), 1, fptr);
	short *sequence = malloc(sizeof(short) * (length-1));
	for(int i=0;i<(length*2);++i)
	{
		sequence[i] = 0;
	}
	for(int i=0;i<(length*2);++i)
	{
		fwrite(&sequence[i], sizeof(short), 1, fptr);
	}
	free(sequence);
	fclose(fptr);
}

void TableConstruct(char *filename)
{
	FILE *fptr = fopen(filename, "w");
	if(fptr == NULL)
	{
		return;
	}
	short m = 2;
	short n = 5;
	fwrite(&m, sizeof(short), 1, fptr);
	fwrite(&n, sizeof(short), 1, fptr);
	short *table = malloc(sizeof(short) * m*n);
	for(int i=0;i<(m*n);++i)
	{
		table[i] = i;
	}
	table[5] = 0;
	for(int i=0;i<(m*n);++i)
	{
		fwrite(&table[i], sizeof(short), 1, fptr);
	}
	free(table);
	fclose(fptr);
}
