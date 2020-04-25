#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

//#define DEBUG_HW

static void PrintGraph(LinkList **graph, int totalNodes);
static LinkList *AddAdjacentyNode(int index);
static void TopoSortHelper(LinkList **graph, int index, int totalNodes, \
        short *color, int *parent, int *queue, int *queueNum);
static void Index2Coordinate(int ind, short *row, short *col, int n);
static int *OutputPath(char *filename, int *parent, int length, int end);


bool FindSequence(char *inputFile, char *outputFile)
{
	LinkList **graph = NULL;
	
	int totalNodes = 0;
	int n = 0;
	graph = GraphConstruct(inputFile, &totalNodes, &n);
	if((graph == NULL) || (totalNodes == 0))
	{
		fprintf(stderr, "graph construct failed.");
		return false;
	}
	int *queue = TopologicalSort(graph, totalNodes);
#ifdef DEBUG_HW 
	printf("TopologicalSort:\n");
	for(int i=0;i<totalNodes;++i)
	{
		printf("%hd ", queue[i]);
	}
#endif 
	
	int *sequence = NULL;
	int length = 0;
	sequence = FindLongestPath(outputFile, graph, queue, totalNodes, &length);

	FILE *fptr = NULL;
	fptr = fopen(outputFile, "w");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return NULL;
	}
	fwrite(&length, sizeof(int), 1, fptr);
	short row,col;
	for(int i=0;i<length;++i)
	{
		Index2Coordinate(sequence[i], &row, &col, n);
		fwrite(&row, sizeof(short),1,fptr);
		fwrite(&col, sizeof(short),1,fptr);
	}
	
	free(sequence);
	free(queue);
	DestroyGraph(graph, totalNodes);
	fclose(fptr);
	return true;
}


LinkList **GraphConstruct(char *filename, int *nodesNum, int *mapn)
{
	FILE *fptr = NULL;
	fptr = fopen(filename, "r");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return NULL;
	}

	size_t numGet = 0;
    short m;
    numGet = fread(&m, sizeof(short), 1, fptr);
    if((numGet != 1) || (m <= 0) || (m>SHRT_MAX))
    {
        fprintf(stderr, "wrong format");
        fclose(fptr);
        return NULL;
    }
    short n;
    numGet = fread(&n, sizeof(short), 1, fptr);
    if((numGet != 1) || (n <= 0) || (n>SHRT_MAX))
    {
        fprintf(stderr, "wrong format");
        fclose(fptr);
        return NULL;
    }
	*mapn = (int)n;
	
	// Store values into nodes 
	int totalNodes = (int) m*n;
	short *nodes = NULL;
	nodes = malloc(sizeof(short) * totalNodes);
	if(nodes == NULL)
	{
		fprintf(stderr, "malloc failed.");
		fclose(fptr);
		return NULL;
	}
	short value;
	for(int i=0;i<totalNodes;++i)
	{
		numGet = fread(&value, sizeof(short), 1 , fptr);
	    if((numGet != 1) || (value<SHRT_MIN) || (value>SHRT_MAX))
        {
            fprintf(stderr, "wrong format");
			free(nodes);
            fclose(fptr);
            return NULL;
        }
		nodes[i] = value;
#ifdef DEBUG_HW 
		printf("%d:%hd ",i, value);
#endif 
	}

	// Initial Graph 
	LinkList **graph = NULL;
	graph = malloc(sizeof(LinkList*) * totalNodes);
	for(int i=0;i<totalNodes;++i)
	{
		graph[i] = NULL;
	}
	
	//graph[2] = AddAdjacentyNode(1);
	
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
					free(nodes);
				    fclose(fptr);
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
					free(nodes);
				    fclose(fptr);
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
					free(nodes);
				    fclose(fptr);
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
					free(nodes);
				    fclose(fptr);
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
	PrintGraph(graph, totalNodes);
#endif 
	*nodesNum = totalNodes;

	free(nodes);
	fclose(fptr);
	return graph;
}

// queue stores the index in queue, while index might > SHRT_MAX, thus needs to change form queue to int 
enum Color{BLACK, GRAY, WHITE};
int *TopologicalSort(LinkList **graph, int totalNodes)
{
	short *color = malloc(sizeof(short) * totalNodes);
	int *parent = malloc(sizeof(int) * totalNodes);
	int *queue = malloc(sizeof(int) * totalNodes);
	if((color == NULL) || (parent == NULL) || (queue == NULL))
	{
		free(color);
		free(parent);
		free(queue);
		fprintf(stderr, "malloc failed.");
		return NULL;
	}

	for(int i=0;i<totalNodes;++i)
	{
		color[i] = WHITE;
		parent[i] = -1;
	}
	int queueNum = 0;
	for(int i=0;i<totalNodes;++i)
	{
		if(color[i] == WHITE)
		{
			TopoSortHelper(graph, i, totalNodes, color, parent, queue, &queueNum);
		}
	}

	free(color);
	free(parent);
	return queue;
}

static void TopoSortHelper(LinkList **graph, int index, int totalNodes, \
		short *color, int *parent, int *queue, int *queueNum)
{
	color[index] = GRAY;
	LinkList *p = NULL;
	p = graph[index];
	while(p != NULL)
	{
		int destIndex = p->dest;
		if(color[destIndex] == WHITE)
		{
			parent[destIndex] = index;
			TopoSortHelper(graph, destIndex, totalNodes, color, parent, \
					queue, queueNum);
		}
		p = p->next;
	}
	color[index] = BLACK;
	queue[totalNodes-1-(*queueNum)] = index;
	(*queueNum)++;
}

int *FindLongestPath(char *filename, LinkList **graph, int *queue, int totalNodes, int *longestLength)
{
	int *length = malloc(sizeof(int) * totalNodes);
	int *parent = malloc(sizeof(int) * totalNodes);
	for(int i=0;i<totalNodes;++i)
	{
		length[i] = 1;
		parent[i] = -1;
	}

//	int longestLength = 1;
	int longestIndex = 0;
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
				parent[destIndex] = index;
			}
			p = p->next;
		}
		if(length[index] > *longestLength)
		{
			*longestLength = length[index];
			longestIndex = index;
		}
	}
#ifdef DEBUG_HW 
	printf("\nlongest length: %d, index: %d\n", *longestLength, longestIndex);
#endif 
	int *sequence = NULL;
	sequence = OutputPath(filename, parent, *longestLength, longestIndex);
	
	free(length);
	free(parent);
	return sequence;
}

static LinkList *AddAdjacentyNode(int index)
{
	LinkList *node = NULL;
	node = malloc(sizeof(LinkList));
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	node->dest = index;
	node->next = NULL;
	return node;
}

void DestroyGraph(LinkList **graph, int totalNodes)
{
	LinkList *head = NULL;
	LinkList *p = NULL;
	for(int i=0;i<totalNodes;++i)
	{
		head = graph[i];
		while(head != NULL)
		{
			p = head->next;
			free(head);
			head = p;
		}
	}
	free(graph);
}

static void Index2Coordinate(int ind, short *row, short *col, int n)
{
	*row = (short)ind/n;
	*col = (short)ind - (*row)*n;
}
static int *OutputPath(char *filename, int *parent, int length, int end)
{
	int *sequence = malloc(sizeof(int) * length);
	if(sequence == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}

	sequence[length-1] = end;
	for(int i=length-2;i>=0;--i)
	{
		sequence[i] = parent[sequence[i+1]];
	}
#ifdef DEBUG_HW
	printf("print path\n");

	for(int i=0;i<length;++i)
	{
		printf("%d ", sequence[i]);
	}
#endif
	return sequence;
}

static void PrintGraph(LinkList **graph, int totalNodes)
{
	LinkList *head = NULL;
	for(int i=0;i<totalNodes;++i)
	{
		printf("%d: ", i);
		head = graph[i];
		while(head != NULL)
		{
			printf("%d ", head->dest);
			head = head->next;
		}
		printf("\n");
	}
}

