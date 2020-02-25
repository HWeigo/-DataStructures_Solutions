#ifndef __COUNT_FREQUENCY_H__
#define __COUNT_FREQUENCY_H__

typedef struct{
	int character;	
	long freq;
}Freq;

int CountFrequency(char *filename, Freq *clist, int *totalNum, int *diffNum);
void SaveFreqToFile(char *filename, Freq *clist);

#endif  

