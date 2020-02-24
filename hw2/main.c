#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "count_frequency.h"
#include "tree_construct.h"
#include "encode.h"
#include "compress.h"

//#define DEBUG_MAIN 

int main(int agrc, char **argv)
{
	Freq charFreq[256];
	
	// Count frequencies of all characters
	// diffNum: number of different character in original file 
	// totalNum: number of character in original file 
	int totalNum, diffNum;
	CountFrequency(argv[1], charFreq, &totalNum, &diffNum);

#ifdef DEBUG_MAIN  
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

	// Copy original character frequency before sorting
	int charFreqOri[256];
	for(int i=0; i<256; i++)
	{
		charFreqOri[i] = charFreq[i].freq;
	}

	// Construct Huffman tree 
	TreeNode *huffmanTree = ConstructTree(charFreq, diffNum);
	
	//Save huffmanTree into .tree file 
	long totalCharInTree = SaveTreeToFileASCII(argv[3], huffmanTree);

	// Construct encoding table
	// table: 
	// bitWidth: 
	int **table;
	int bitWidth[256];
	table = ConstructTable(huffmanTree, argv[4], bitWidth);
#ifdef DEBUG_MAIN 	
	printf("bitWidth and charFreq\n");
	for(int i = 0; i<256;i++)
	{
		printf("%c:%d, %d\n",i,bitWidth[i], charFreqOri[i]);
	}
//	for(int i=0; i<5;i++)
//	{
//		printf("%d ", table[114][i]);
//	}
#endif 
	
	long totalCharCompressed = 0;
	CalHeaderInformation(charFreqOri, bitWidth, &totalCharCompressed);
	Compress(argv[1],argv[5], table, huffmanTree, totalNum, totalCharCompressed, totalCharInTree);

	printf("%ld\n", totalCharCompressed);

	FreeTree(huffmanTree);
	FreeTable(table);

	return EXIT_SUCCESS;
}
