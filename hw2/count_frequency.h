#ifdef COUNT_FREQUENCY_H
#define COUNT_FREQUENCY_H

typedef struct{
	unsigned char charecter;	
	int freq = 0;
}Freq;

int CountFrequency(char *filename, Freq *clist);

#endif  

