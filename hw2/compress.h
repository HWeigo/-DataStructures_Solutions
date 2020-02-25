#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#include "tree_construct.h"

void CalHeaderInformation(int *charFreq, int *charWidth, long *totalCharCompressed);
int Compress(char *oriFilename, char *outFilename, int **table, TreeNode *root, long totalCharOri, long totalCharCompressed, long totalCharInTree);
unsigned char SetBit(unsigned char num, int bit);
unsigned char ClearBit(unsigned char num, int bit);
#endif
