#ifndef __GRAPH_H__
#define __GRAPH_H__


typedef struct _LinkList{
	int dest;
	struct _LinkList *next;
}LinkList;

LinkList **GraphConstruct(char *filename, int *nodesNum);
void DestroyGraph(LinkList **graph, int totalNodes);
int *TopologicalSort(LinkList **graph, int totalNodes);
void FindLongestPath(char *filename, LinkList **graph, int *queue, int totalNodes);
bool FindSequence(char *inputFile, char *outputFile);

#endif 
