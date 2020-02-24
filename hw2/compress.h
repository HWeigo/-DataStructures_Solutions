#ifndef __COMPRESS_H__
#define __COMPRESS_H__

void CalHeaderInformation(int *charFreq, int *charWidth, long *totalCharCompressed);
void Compress(char *oriFilename, char *outFilename, int **table, long totalCharCompressed);

#endif
