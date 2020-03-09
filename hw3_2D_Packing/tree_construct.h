#ifndef __TREE_CONSTRUCT_H__
#define __TREE_CONSTRUCT_H__

typedef struct _TreeNode{
	struct _TreeNode *left;
	struct _TreeNode *right;
	int id;
	int height;
	int width;
	int x;
	int y;
}TreeNode;

typedef struct _LinkedList{
	struct _LinkedList *next;
	TreeNode *tptr;
}LinkedList;

bool TreeConstruct(char *filename, TreeNode **root);
void PreorderTraversal(TreeNode *root, FILE *fptr);
void TreeDestroy(TreeNode *root);

#endif
