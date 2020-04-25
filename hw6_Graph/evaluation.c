#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

static LinkList **GraphConstructForEvaluate(short *nodes, short m, short n);
static int FindLongestPathForEvaluate(LinkList **graph, int *queue, int totalNodes);

bool Evaluation(char *inputFile, char *outputFile)
{
	int isBinaryValid = 0;
	int isSequenceValid = 0;
	int isIncreasing = 0;
	int isMaximal = 0;

	FILE *inFptr = fopen(inputFile, "r");
	if(inFptr == NULL)
	{
		isBinaryValid = -1;
	}
	
	FILE *outFptr = fopen(outputFile, "r");
	if(outFptr == NULL)
	{
		isSequenceValid = -1;
	}
	
	if((isBinaryValid == -1) || (isSequenceValid == -1))
	{
		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
		fclose(inFptr);
		fclose(outFptr);
		return false;
	}
	
	// Check whether binary file is valid 
	isBinaryValid = 1;
	size_t numGet = 0;
    short m;
    numGet = fread(&m, sizeof(short), 1, inFptr);
    if((numGet != 1) || (m <= 0) || (m>SHRT_MAX))
    {
		isBinaryValid = 0;
    	printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        fclose(inFptr);
		fclose(outFptr);
        return false;
	}   
    short n;
    numGet = fread(&n, sizeof(short), 1, inFptr);
    if((numGet != 1) || (n <= 0) || (n>SHRT_MAX))
    {   
		isBinaryValid = 0;
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        fclose(inFptr);
		fclose(outFptr);
        return false;
	}   
    
    // Store values into nodes 
    int totalNodes = (int) m*n;
    short *nodes = NULL;
    nodes = malloc(sizeof(short) * totalNodes);
    if(nodes == NULL)
    { 
		isBinaryValid = 0;
		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        fclose(inFptr);
		fclose(outFptr);
        return false;
    }   
    short value;
    for(int i=0;i<totalNodes;++i)
    {   
        numGet = fread(&value, sizeof(short), 1 , inFptr);
        if((numGet != 1) || (value<SHRT_MIN) || (value>SHRT_MAX))
        {
			isBinaryValid = 0;
			printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,\
					isIncreasing,isMaximal);
			fclose(inFptr);
			fclose(outFptr);
            free(nodes);
            return NULL;
        }
        nodes[i] = value;
#ifdef DEBUG_HW 
        printf("%d:%hd ",i, value);
#endif
    }
	
	// Check whether sequence file is vaild
	isSequenceValid = 1;
    int sequenceLength = 0;
    numGet = fread(&sequenceLength, sizeof(int), 1, outFptr);
    if(numGet != 1) 
    {   
		isSequenceValid = 0;
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        free(nodes);
		fclose(inFptr);
		fclose(outFptr);
        return false;
	}
	int *sequence = malloc(sizeof(int) * sequenceLength);
    if(sequence == NULL) 
    {   
		isSequenceValid = 0;
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        free(nodes);
		fclose(inFptr);
		fclose(outFptr);
        return false;
	}

	short row, col;
	for(int i=0;i<sequenceLength;++i)
	{
		numGet = fread(&row, sizeof(short),1, outFptr);
	    if(numGet != 1)
	    {   
			isSequenceValid = 0;
			free(nodes);
			free(sequence);
	        fclose(inFptr);
			fclose(outFptr);
	        return false;
		}
		numGet = fread(&col, sizeof(short),1, outFptr);
	    if(numGet != 1)
	    {   
			isSequenceValid = 0;
			free(nodes);
			free(sequence);
	        fclose(inFptr);
			fclose(outFptr);
	        return false;
		}
		sequence[i] = (int) row*n+col;
	}

	// Check whether sequence is increasing
	int index = sequence[0];
	if(index >= totalNodes)
	{
   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
        free(nodes);
		free(sequence);
		fclose(inFptr);
		fclose(outFptr);
        return true;
	}
	short prevValue = nodes[index];
	for(int i=1;i<sequenceLength;++i)
	{
		index = sequence[i];	
		int parentIndex = sequence[i-1];
		printf("%d ", index);
		int isAdjacent = 0;
		int gap = parentIndex - index;
		if((gap==1)||(gap==-1)||(gap==n)||(gap==-n)) 
		{
			isAdjacent = 1;
		}
		if((index>=totalNodes) || (prevValue>=nodes[index]) || (isAdjacent==0) )
		{
	   		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
		    free(nodes);
			free(sequence);
			fclose(inFptr);
			fclose(outFptr);
			return true;
		}
		prevValue=nodes[index];
	}
	isIncreasing = 1;
	
	// Check whether it's longest path
	LinkList **graph = NULL;
	graph = GraphConstructForEvaluate(nodes, m, n);
	if(graph == NULL)
	{
		printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
	    free(nodes);
		free(sequence);
		fclose(inFptr);
		fclose(outFptr);
		return true;
	}
	int *queue = TopologicalSort(graph, totalNodes);
	int longestLength = 0;
	longestLength = FindLongestPathForEvaluate(graph, queue, totalNodes);
	if(longestLength == sequenceLength)
	{
		isMaximal = 1;
	}
	
	printf("%d,%d,%d,%d\n",isBinaryValid,isSequenceValid,isIncreasing,isMaximal);
	
	DestroyGraph(graph, totalNodes);
	free(queue);
	free(nodes);
	free(sequence);
	fclose(inFptr);
	fclose(outFptr);
	return true;
}

static LinkList **GraphConstructForEvaluate(short *nodes, short m, short n)
{
    // Initial Graph 
    int totalNodes = (int)m*n;
	LinkList **graph = NULL;
    graph = malloc(sizeof(LinkList*) * totalNodes);
	if(graph == NULL)
	{
		return NULL;
	}
    for(int i=0;i<totalNodes;++i)
    {
        graph[i] = NULL;
    }

	// find edges's adjacency
	int index = 0; 
	LinkList *head = NULL;
	LinkList *p = NULL;
	LinkList *tmp = NULL;
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<n;++j)
		{
			head = NULL;
			p = NULL;
			// check if this node have left adjacent node 
			if((index%n != 0) && (nodes[index] < nodes[index-1]))
			{
				tmp = AddAdjacentyNode(index-1);
				if(tmp == NULL)
				{
					fprintf(stderr, "fail to add node.");
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				if(head == NULL)
				{
					head = tmp;
					p = head;
				}
				else
				{
					p->next = tmp;
					p = p->next;
				}
			}
			// check if this node have upper adjacent node 
			if((index >= n) && (nodes[index] < nodes[index-n]))
			{

				tmp = AddAdjacentyNode(index-n);
				if(tmp == NULL)
				{
					fprintf(stderr, "fail to add node.");
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				if(head == NULL)
				{
					head = tmp;
					p = head;
				}
				else
				{
					p->next = tmp;
					p = p->next;
				}
			}		
			// check if this node have right adjacent node 
			if(((index+1)%n != 0) && (nodes[index] < nodes[index+1]))
			{
				tmp = AddAdjacentyNode(index+1);
				if(tmp == NULL)
				{
					fprintf(stderr, "fail to add node.");
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				if(head == NULL)
				{
					head = tmp;
					p = head;
				}
				else
				{
					p->next = tmp;
					p = p->next;
				}
			}
			// check if this node have lower adjacent node 
			if((index < (totalNodes-n)) && (nodes[index] < nodes[index+n]))
			{
				tmp = AddAdjacentyNode(index+n);
				if(tmp == NULL)
				{
					fprintf(stderr, "fail to add node.");
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				if(head == NULL)
				{
					head = tmp;
					p = head;
				}
				else
				{
					p->next = tmp;
					p = p->next;
				}
			}
			graph[index] = head;
			index++;
		}
	}
#ifdef DEBUG_HW 
	//PrintGraph(graph, totalNodes);
#endif 
	return graph;
}

static int FindLongestPathForEvaluate(LinkList **graph, int *queue, int totalNodes)
{
	int *length = malloc(sizeof(int) * totalNodes);
	for(int i=0;i<totalNodes;++i)
	{
		length[i] = 1;
	}

	int longestLength = 0;
	for(int i=0;i<totalNodes;++i)
	{
		int index = queue[i];
		int destLength = length[index] + 1;
		LinkList *p = graph[index];
		while(p != NULL)
		{
			int destIndex = p->dest;
			if(length[destIndex] < destLength)
			{
				length[destIndex] = destLength;
			}
			p = p->next;
		}
		if(length[index] > longestLength)
		{
			longestLength = length[index];
		}
	}

	free(length);
	return longestLength;
}
