#ifndef __ENCODE_H_
#define __ENCODE_H_

#include "tree_construct.h"

typedef struct _ListNode{
    struct _ListNode *next;
    int value;
}ListNode;

typedef struct {
	ListNode *head;
	ListNode *tail;
}Queue;

int **ConstructTable(TreeNode *root);
void FreeTable(int **table);

#endif
