#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

bool Evaluation(char *inputFile, char *outputFile)
{
	int isBinaryValid = 0;
	int isSequenceValid = 0;
	int isIncreasing = 0;
	int isMaximal = 0;

	FILE *inFptr = fopen(inputFile, "r");
	if(inFptr == NULL)
	{
		isBinaryValid = -1;
	}
	
	FILE *outFptr = fopen(outputFile, "r");
	if(outFptr == NULL)
	{
		isSequenceValid = -1;
	}
	
	if((isBinaryValid == -1) || (isSequenceValid == -1))
	{
		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
		fclose(inFptr);
		fclose(outFptr);
		return false;
	}
	
	// Check whether binary file is valid 
	isBinaryValid = 1;
	size_t numGet = 0;
    short m;
    numGet = fread(&m, sizeof(short), 1, inFptr);
    if((numGet != 1) || (m <= 0) || (m>SHRT_MAX))
    {
		isBinaryValid = 0;
    	printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        fclose(inFptr);
		fclose(outFptr);
        return false;
	}   
    short n;
    numGet = fread(&n, sizeof(short), 1, inFptr);
    if((numGet != 1) || (n <= 0) || (n>SHRT_MAX))
    {   
		isBinaryValid = 0;
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        fclose(inFptr);
		fclose(outFptr);
        return false;
	}   
    
    // Store values into nodes 
    int totalNodes = (int) m*n;
    short *nodes = NULL;
    nodes = malloc(sizeof(short) * totalNodes);
    if(nodes == NULL)
    { 
		isBinaryValid = 0;
		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        fclose(inFptr);
		fclose(outFptr);
        return false;
    }   
    short value;
    for(int i=0;i<totalNodes;++i)
    {   
        numGet = fread(&value, sizeof(short), 1 , inFptr);
        if((numGet != 1) || (value<SHRT_MIN) || (value>SHRT_MAX))
        {
			isBinaryValid = 0;
			printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,\
					isIncreasing,isMaximal);
			fclose(inFptr);
			fclose(outFptr);
            free(nodes);
            return NULL;
        }
        nodes[i] = value;
#ifdef DEBUG_HW 
        printf("%d:%hd ",i, value);
#endif
    }
	
	// Check whether sequence file is vaild
	isSequenceValid = 1;
    int sequenceLength = 0;
    numGet = fread(&sequenceLength, sizeof(int), 1, outFptr);
    if(numGet != 1) 
    {   
		isSequenceValid = 0;
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        free(nodes);
		fclose(inFptr);
		fclose(outFptr);
        return false;
	}
	int *sequence = malloc(sizeof(int) * sequenceLength);
    if(sequence == NULL) 
    {   
		isSequenceValid = 0;
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        free(nodes);
		fclose(inFptr);
		fclose(outFptr);
        return false;
	}

	short row, col;
	for(int i=0;i<sequenceLength;++i)
	{
		numGet = fread(&row, sizeof(short),1, outFptr);
	    if((numGet != 1) || (row <= 0) || (row>SHRT_MAX))
	    {   
			isSequenceValid = 0;
			free(nodes);
	        fclose(inFptr);
			fclose(outFptr);
	        return false;
		}
		numGet = fread(&col, sizeof(short),1, outFptr);
	    if((numGet != 1) || (col <= 0) || (col>SHRT_MAX))
	    {   
			isSequenceValid = 0;
			free(nodes);
	        fclose(inFptr);
			fclose(outFptr);
	        return false;
		}
		sequence[i] = (int) row*n+col;
	}
	printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);


	free(nodes);
	free(sequence);
	fclose(inFptr);
	fclose(outFptr);
	return true;
}
