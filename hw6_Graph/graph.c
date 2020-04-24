#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

static void PrintGraph(LinkList **graph, int totalNodes);
static LinkList *AddAdjacentyNode(short index);
static void TopoSortHelper(LinkList **graph, short index, int totalNodes, \
        short *color, short *parent, short *queue, int *queueNum);

LinkList **GraphConstruct(char *filename)
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
		printf("%d:%hd ",i, value);
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
	short index = 0; 
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
	
	PrintGraph(graph, totalNodes);

	short *queue = TopologicalSort(graph, totalNodes);
	printf("TopologicalSort:\n");
	for(int i=0;i<totalNodes;++i)
	{
		printf("%hd ", queue[i]);
	}
	free(queue);
	
	DestroyGraph(graph, totalNodes);


	free(nodes);
	fclose(fptr);
	return graph;

}

// queue stores the index in queue, while index might > SHRT_MAX, thus needs to change form queue to int 
enum Color{BLACK, GRAY, WHITE};
short *TopologicalSort(LinkList **graph, int totalNodes)
{
	short *color = malloc(sizeof(short) * totalNodes);
	short *parent = malloc(sizeof(short) * totalNodes);
	short *queue = malloc(sizeof(short) * totalNodes);
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

static void TopoSortHelper(LinkList **graph, short index, int totalNodes, \
		short *color, short *parent, short *queue, int *queueNum)
{
	color[index] = GRAY;
	LinkList *p = NULL;
	p = graph[index];
	while(p != NULL)
	{
		short destIndex = p->dest;
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

//void FindLongestPath(LinkList **graph, short *queue, int totalNodes)
//{
//	int *length = malloc(sizeof(int) * totalNodes);
//	int *parent = malloc(sizeof(int) * totalNodes);
//	for(int i=0;i<totalNodes;++i)
//	{
//		length[i] = 0;
//		parent[i] = ;
//	}
//	for(int i=0;i<totalNodes;++i)
//	{
//		short index = queue[i];
//		int destLength = length[i] + 1;
//		LinkList *p = graph[index];
//		while(p != NULL)
//		{
//			short destIndex = p->dest;
//			if(length[destIndex] < destLength)
//			{
//				
//			}
//		}
//
//	}
//}

static LinkList *AddAdjacentyNode(short index)
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

static void PrintGraph(LinkList **graph, int totalNodes)
{
	LinkList *head = NULL;
	for(int i=0;i<totalNodes;++i)
	{
		printf("%d: ", i);
		head = graph[i];
		while(head != NULL)
		{
			printf("%hd ", head->dest);
			head = head->next;
		}
		printf("\n");
	}
}
