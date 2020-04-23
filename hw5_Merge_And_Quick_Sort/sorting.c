#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

//#define DEBUG_HW

static long MedianOfThree(long *array, int lb, int mid, int ub);
static void Swap(long *array, int idx1, int idx2);
static void QuickSortHelper(long *array, int lb, int ub);
static void InsertionSort(long *array, int lb, int ub);
static void Merge(long *array, long *tmp, int lb, int mid, int ub);
static int MIN(int a, int b);
#ifdef DEBUG_HW 
static void printArray(long *array, int size)
{
    for(int i=0; i<size;++i)
    {   
        printf("%ld ", array[i]);
    }   
    printf("\n");
}
#endif 

// BUG: Memory Leak If Same Number Appears!
void Quick_Sort(long *Array, int Size)
{
	QuickSortHelper(Array, 0, Size-1);
}

void Merge_Sort(long *Array, int Size)
{
	int idx = 0;
	int n = 16;
	while(idx < (Size-n))
	{
		InsertionSort(Array, idx, idx+n-1);
		idx += n;
	}
	InsertionSort(Array, idx, Size-1);

	long *sorted = Array;
	long *merged = malloc(sizeof(long) * Size);

	long *tmp;
	if(merged == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return;
	}
	memcpy(merged, sorted, sizeof(long)*Size);
#ifdef DEBUG_HW 
	printf("before.\n");
	printArray(sorted, Size);
	printArray(merged, Size);
#endif 
	while(n < Size)
	{
		idx = 0;
		while(idx < (Size - n))
		{
			Merge(merged, sorted, idx, idx+n-1, MIN(idx+2*n-1, Size-1));
			idx = idx + 2 * n;
		}
		if(idx < Size)
		{
			memcpy(&merged[idx],&sorted[idx], sizeof(long) * (Size-idx));
		}

		tmp = sorted;
		sorted = merged;
		merged = tmp;
		n = n * 2;
#ifdef DEBUG_HW 
		printf("after.\n");
		printArray(sorted, Size);
		printArray(merged, Size);
#endif 
	}
	if(merged == Array)
	{
		memcpy(Array, sorted, sizeof(long)*Size);
		free(sorted);
	}
	else
	{
		free(merged);
	}
#ifdef DEBUG_HW 
	printf("after.\n");
	printArray(sorted, Size);
	printArray(merged, Size);
	printArray(Array, Size);
#endif 
}

static void Merge(long *array, long *tmp, int lb, int mid, int ub)
{
	int i = lb;
	int j = mid + 1;
	for(int k=lb; k<=ub; k++)
	{
		if(i > mid)
		{
			array[k] = tmp[j++];
		}
		else if(j > ub)
		{
			array[k] = tmp[i++];
		}
		else if(tmp[i] > tmp[j])
		{
			array[k] = tmp[j++];
		}
		else
		{
			array[k] = tmp[i++];
		}
	}
}


static void InsertionSort(long *array, int lb, int ub)
{
	for(int i=lb+1; i<=ub; i++)
	{
		long tmp = array[i];
		int j = i;
		while(((j-1) >= lb) && (array[j-1] > tmp))
		{
			array[j] = array[j-1];
			j--;
		}
		array[j] = tmp;
		//printArray(array, ub-lb+1);
	}
}

static void QuickSortHelper(long *array, int lb, int ub)
{
	if(lb >= ub)
	{
		return;
	}
	
	int mid = (lb + ub)/2;
	long pivot = MedianOfThree(array, lb, mid, ub);
	int down = lb;
	int up = ub;
	int left = lb;
	int right = ub;
	int leftLength = 0, rightLength = 0;

	while(down < up)
	{
		while((array[down] <= pivot) && (down <= up))
		{
			if(array[down] == pivot)
			{
				Swap(array, down, left);
				left++;
				leftLength++;
			}
			down++;
		}
		while((array[up] >= pivot) && (down <= up))
		{
			if(array[up] == pivot)
			{
				Swap(array, up, right);
				right--;
				rightLength++;
			}
			up--;
		}

		if(down < up)
		{
			Swap(array, down, up);
		}
	}
	
	int i = up;
	int j = lb;
	while(j < left)
	{
		Swap(array, i, j);
		i--;
		j++;
	}

	i = down;
	j = ub;
	while(j > right)
	{
		Swap(array, i, j);
		i++;
		j--;
	}
#ifdef DEBUG_HW
	printf("pivot: %ld\n down: %d, up: %d\n", pivot, down, up);	
	printArray(array, 25);
#endif
	QuickSortHelper(array, lb, up-leftLength);
	QuickSortHelper(array, down+rightLength, ub);
}

static long MedianOfThree(long *array, int lb, int mid, int ub)
{
	if(array[mid] > array[ub])
	{
		Swap(array, mid, ub);
	}
	if(array[lb] > array[ub])
	{
		Swap(array, lb, ub);
	}
	if(array[lb] > array[mid])
	{
		Swap(array, lb, mid);
	}
	// Now array[lb]<=array[mid]<=array[ub]
	return array[mid];
}

static void Swap(long *array, int idx1, int idx2)
{
	if(array == NULL)
	{
		fprintf(stderr, "empty array");
		return;
	}
	long tmp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = tmp;
}

static int MIN(int a, int b)
{
	return (a>b)?(b):(a);
}

