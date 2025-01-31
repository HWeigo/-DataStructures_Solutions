#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"
#include "tree_construct.h"
#include "count_frequency.h"

unsigned char SetBit(unsigned char num, int bit)
{
	num |= (1<<bit);
	return num;
}

unsigned char ClearBit(unsigned char num, int bit)
{
	num &= ~(1<<bit);
	return num;
}

void CalHeaderInformation(int *charFreq, int *charWidth, long *totalCharCompressed)
{
	int totalBitCompressed = 0;
	for(int i = 0;i<256;i++)
	{
		totalBitCompressed += charFreq[i] * charWidth[i];
	}
	//printf("bit:%d\n", totalBitCompressed);
	if((totalBitCompressed % 8) == 0)
	{
		*totalCharCompressed = (long) totalBitCompressed / 8;
	}
	else
	{
		*totalCharCompressed = (long) (totalBitCompressed / 8 + 1);
	}
}

int Compress(char *oriFilename, char *outFilename, int **table, TreeNode *root, long totalCharOri, long totalCharCompressed, long totalCharInTree)
{
	FILE *oriFptr;
	oriFptr = fopen(oriFilename, "r");
	if(oriFptr == NULL)
	{
		return -1;
	}

	FILE *outFptr;
	outFptr = fopen(outFilename, "w+");
	if(outFptr == NULL)
	{
		return -1;
	}
	

	long num1 = totalCharCompressed +3*8 + totalCharInTree;
	fwrite(&num1, sizeof(long), 1, outFptr);
	fwrite(&totalCharInTree, sizeof(long), 1, outFptr);
	fwrite(&totalCharOri, sizeof(long), 1, outFptr);		
	//printf("ori:%ld, tree%ld, compress:%ld", totalCharOri, totalCharInTree, num1);
	SaveTreeToFileBinary(outFptr, root);

	if(root == NULL)
	{
		fclose(oriFptr);
		fclose(outFptr);
		return 1;
	}
	
	unsigned char *compressCode = malloc(sizeof(unsigned char) * totalCharCompressed);
	int bitInd = 0;
	int byteInd = 0;
	do
	{
		int charInd = fgetc(oriFptr);
		if(feof(oriFptr))
		{
			break;
		}
		int j=0;
		while(table[charInd][j] != -1)
		{
			if(table[charInd][j] == 0)
			{
				compressCode[byteInd] = ClearBit(compressCode[byteInd], bitInd);
			}
			if(table[charInd][j] == 1)
			{
				compressCode[byteInd] = SetBit(compressCode[byteInd], bitInd);
			}
			bitInd++;
			if(bitInd == 8)
			{
				bitInd = 0;
				byteInd++;
			}
			j++;
		}
	}while(1);

	while(bitInd != 8)
	{
		compressCode[byteInd] = ClearBit(compressCode[byteInd], bitInd);
		bitInd ++;
	}

	fwrite(compressCode, sizeof(unsigned char), totalCharCompressed, outFptr);

	free(compressCode);
	fclose(oriFptr);
	fclose(outFptr);
	return 1;
}
