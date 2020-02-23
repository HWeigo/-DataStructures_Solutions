#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "count_frequency.h"
#include "tree_construct.h"
#include "encode.h"

//#define DEBUG_MAIN_H

int main(int agrc, char **argv)
{
	Freq charFreq[256];
	
	// Count frequencies of all characters
	// diffNum: number of different character in original file 
	// totalNum: number of character in original file 
	int totalNum, diffNum;
	CountFrequency(argv[1], charFreq, &totalNum, &diffNum);

#ifdef DEBUG_MAIN_H 
	printf("diffNum: %d\n", diffNum);
	printf("totalNum: %d\n", totalNum);
	int i= 0;
	while(i<256)
	{
		if(charFreq[i].character != -1)
		{
			printf("%c: %ld\n", charFreq[i].character, charFreq[i].freq);
		}
		i++;
	}
#endif

	// Save frequncies of all 256 character into .count file
	SaveFreqToFile(argv[2], charFreq);
	
	// Construct Huffman tree 
	TreeNode *huffmanTree = ConstructTree(charFreq, diffNum);
	
	// Construct encoding table
	int **table;
	table = ConstructTable(huffmanTree);

	FreeTree(huffmanTree);
	FreeTable(table);

	return EXIT_SUCCESS;
}
