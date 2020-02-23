#include "stdlib.h"
#include "stdio.h"
#include "strings.h"
#include "tree_construct.h"
#include "count_frequency.h"

static int qsortHelper(const void *a, const void *b)
{
	Freq *A = (Freq*) a;
	Freq *B = (Freq*) b;

	if((A->freq) == 0)
	{
		return 1;
	}
	if((B->freq) == 0)
	{
		return -1;
	}
	return (A->freq - B->freq);

}

static void ConstructLinkedList(Freq *clist)
{
	qsort(clist, 256, sizeof(Freq), qsortHelper);
}

void ConstructTree(Freq *clist)
{
	ConstructLinkedList(clist);
}

