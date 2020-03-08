#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree_construct.h"
#include "packing_operation.h"

static void CalcDimensionHelper(TreeNode *root, int *width, int *height);
static int MAX(int a, int b);

void CalcDimension(TreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	int width, height;
	CalcDimensionHelper(root, &width, &height);
	printf("%d, %d\n", width, height);
}

static void CalcDimensionHelper(TreeNode *root, int *width, int *height)
{
	// Should not reach here 
	if(root == NULL)
	{
		fprintf(stderr, "Tree error.");
		return;
	}
	// Reach the leaf node 
	if(root->id >= 0)
	{
		printf("%d(%d,%d)\n", root->id, root->width, root->height);
		*width = root->width;
		*height = root->height;
		return;
	}
	int leftWidth, leftHeight;
	int rightWidth, rightHeight;
	CalcDimensionHelper(root->left, &leftWidth, &leftHeight);
	CalcDimensionHelper(root->right, &rightWidth, &rightHeight);

	// H node 
	if(root->id == -1)
	{
		*width = MAX(leftWidth, rightWidth);
		*height = leftHeight + rightHeight;
		root->width = *width;
		root->height = *height;
		return;
	}
	// V node
	if(root->id == -2)
	{
		*width = leftWidth + rightWidth;
		*height = MAX(leftHeight, rightHeight);
		root->width = *width;
		root->height = *height;
	}
}

static int MAX(int a, int b)
{
	return ((a>b)? a:b);
}
