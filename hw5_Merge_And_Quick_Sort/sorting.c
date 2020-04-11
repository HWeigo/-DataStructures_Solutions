#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

void Quick_Sort(long *Array, int Size)
{

}


static void QuickSortHelper(long *array, int lb, int ub)
{
	if(lb >= ub)
	{
		return;
	}
	int patitionIdx = Patition(array, lb, ub);
	QuickSortHelper(array, lb, patitionIdx-1);
	QuickSortHelper(array, patitionIdx +1, ub);
}

static int Patition(long *array, int lb, int ub)
{
	pivot = ;
	down = lb;
	up = ub;
	while(down < up)
	{
		while(array[down] > pivot)
		{
			down++;
		}
		while(array[up] > pivot)
		{
			up--;
		}
		if(down < up)
		{
			long tmp = array[down];
			array[down] = array[up];
			array[up] = tmp;
		}
	}
	return up;
}

void Merge Sort(long *Array, int Size)
{

}
