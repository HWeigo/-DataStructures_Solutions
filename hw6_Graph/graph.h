#ifndef __GRAPH_H__
#define __GRAPH_H__


typedef struct _LinkList{
	short dest;
	struct _LinkList *next;
}LinkList;

LinkList **GraphConstruct(char *filename);
void DestroyGraph(LinkList **graph, int totalNodes);

#endif 
