#ifndef __TREE_CONSTRUCT_H__
#define __TREE_CONSTRUCT_H__

typedef struct _TreeNode{
	struct _TreeNode *left;
	struct _TreeNode *right;
	int id;
	int height;
	int width;
}TreeNode;

typedef struct _LinkedList{
	struct _LinkedList *next;
	TreeNode *tptr;
}LinkedList;

bool TreeConstruct(char *filename, TreeNode **root);
void PreorderTraversal(TreeNode *root);
void TreeDestroy(TreeNode *root);

#endif
