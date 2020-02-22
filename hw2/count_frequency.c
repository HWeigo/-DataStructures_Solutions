#include "count_frequency.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int CountFrequency(char *filename, Freq *clist)
{
//	// Initialize 
//	for(int i=0; i<256; i++)
//	{
//		clist[i].freq = 0;
//	}
	
	fptr = fopen(filename, "r");
	
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return -1;
	}
	do 
	{
		int charInd = fgetc(fptr);
		if(feof(fptr))
		{
			break;
		}
		clist[charInd].character = (unsigned char) charInd;
		clist[charInd].Freq ++;
	}while(1)


	fclose(fptr);
	return cnt;
}
