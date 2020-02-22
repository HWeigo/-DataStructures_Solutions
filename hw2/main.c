#include "count_frequency.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEBUG_HW_H

int main(int agrc, char **argv)
{
	Freq charFreq[256];
	int charNum;

	charNum = CountFrequency(argv[1], charFreq);

#ifdef DEBUG_HW_H 
	printf("charNum: %d", charNum);
	for(int i=0; i< 256; i++)
	{
		printf("%c: %d\n", charFreq[i].character, charFreq[i].freq);
	}
#endif
	
	return EXIT_SUCCESS;
}
