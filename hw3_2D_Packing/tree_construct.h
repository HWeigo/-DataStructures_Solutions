#ifndef __TREE_CONSTRUCT_H__
#define __TREE_CONSTRUCT_H__

typedef struct _TreeNode{
	struct _TreeNode *left;
	struct _TreeNode *right;
	int id;
	int height;
	int width;
}TreeNode;

bool TreeConstruct(char *filename, TreeNode *root);

#endif
