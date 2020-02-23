#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "count_frequency.h"

void CountFrequency(char *filename, Freq *clist, int *totalNum, int*diffNum)
{
	// Initialization
	*totalNum = 0;
	*diffNum = 0;
	for(int i=0; i<256; i++)
	{
		clist[i].freq = 0;
		clist[i].character = -1;
	}

	FILE *fptr;
	fptr = fopen(filename, "r");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return;
	}
	
	do 
	{
		int charInd = fgetc(fptr);
		if(feof(fptr))
		{
			break;
		}
		(*totalNum) ++;
		clist[charInd].character = charInd;
		if(clist[charInd].freq == 0)
		{
			(*diffNum) ++;
		}
		clist[charInd].freq ++;
	}while(1);


	fclose(fptr);
}

void SaveFreqToFile(char *filename, Freq *clist)
{
	FILE *fptr;
	fptr = fopen(filename, "w+");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return;
	}

	for(int i=0; i<256; i++)
	{
		//fprintf(fptr,"%d", clist[i].freq);
		fwrite(&clist[i].freq, sizeof(long), 1, fptr);
	}

	fclose(fptr);
}
