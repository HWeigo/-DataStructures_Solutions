#ifndef __TREE_CONSTRUCT_H__
#define __TREE_CONSTRUCT_H__

#include "count_frequency.h"

typedef struct _TreeNode{
	struct _TreeNode *left;
	struct _TreeNode *right;
	int charIdx;
	long freq;
}TreeNode;

//static typedef struct _ListNode{
//	struct _ListNode *next;
//	TreeNode *tptr;
//}ListNode;

TreeNode *ConstructTree(Freq *clist, int diffNum);

//// Linked List 
//static ListNode *ListNodeConstruct(TreeNode *tp);
//static void ListDestroy(ListNode *head);
//static void PrintLinkedList(ListNode *lptr);

// Binary Tree
TreeNode *TreeNodeConstruct(int idx, long freq);
void PrintTree(TreeNode *tptr);
void FreeTree(TreeNode *tptr);
int CalTreeHeight(TreeNode *tptr);
long SaveTreeToFileASCII(char *filename, TreeNode *root);
void SaveTreeToFileBinary(FILE *fptr, TreeNode *root);

#endif
