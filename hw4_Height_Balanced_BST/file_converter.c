#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"

bool Txt2Binary(char *inputFile, char *outputFile)
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
	int char1;
	char char2[10];
	do
	{
		numGet = fscanf(inFptr, "%d %s\n", &char1, char2);
		if(numGet != 2)
		{
			fprintf(stderr, "numGet !=2.");
			fclose(inFptr);
			fclose(outFptr);
			return false;
		}
		//printf("%d %s\n", char1, char2);
		fwrite(&char1, sizeof(int), 1, outFptr);
		fwrite(char2, sizeof(char), 1, outFptr);
	}while(!feof(inFptr));

	fclose(inFptr);
	fclose(outFptr);
	return true;
}

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

	int char1;
	//char char2[10];
	char char2;
	//size_t numGet1, numGet2;
	while(!feof(inFptr))
	{
		fread(&char1, sizeof(int), 1, inFptr);
		fread(&char2, sizeof(char), 1, inFptr);
		if(feof(inFptr))
		{
			break;
		}
		if(char2 <4)
		{
			char2 += 0x30;
		}
		fprintf(outFptr, "%d %c\n", char1, char2);
	}

	fclose(inFptr);
	fclose(outFptr);
	return true;
}
