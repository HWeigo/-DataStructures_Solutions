#ifndef __GRAPH_H__
#define __GRAPH_H__


typedef struct _LinkList{
	int dest;
	struct _LinkList *next;
}LinkList;

LinkList **GraphConstruct(char *filename, int *nodesNum, int *mapn);
void DestroyGraph(LinkList **graph, int totalNodes);
int *TopologicalSort(LinkList **graph, int totalNodes);
int *FindLongestPath(char *filename, LinkList **graph, int *queue, int totalNodes, int *longestLength);
bool FindSequence(char *inputFile, char *outputFile);
LinkList *AddAdjacentyNode(int index);

#endif 
