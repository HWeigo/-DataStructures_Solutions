#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree_construct.h"
#include "packing_operation.h"

static void CalcDimensionHelper(TreeNode *root, int *width, int *height);
static void CalcCoordinatesHelper(TreeNode *root, int originX, int originY);
static int MAX(int a, int b);

void CalcDimension(TreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	int width, height;
	CalcDimensionHelper(root, &width, &height);
	//printf("%d, %d\n", width, height);
}

void CalcCoordinates(TreeNode *root)
{
	CalcCoordinatesHelper(root, 0, 0);
	return;
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
		//printf("%d(%d,%d)\n", root->id, root->width, root->height);
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

void CalcCoordinatesHelper(TreeNode *root, int originX, int originY)
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
		root->x = originX;
		root->y = originY;
		return;
	}

	root->x = originX;
	root->y = originY;

	int leftX, leftY;
	int rightX, rightY;
	// H node 
	if(root->id == -1)
	{
		rightX = originX;
		rightY = originY;
		leftX = originX;
		leftY = (root->right)->height + originY;
	}
	// V node 
	if(root->id == -2)
	{
		leftX = originX;
		leftY = originY;
		rightX = (root->left)->width + originX;
		rightY = originY;
	}
	CalcCoordinatesHelper(root->left, leftX, leftY);
	CalcCoordinatesHelper(root->right, rightX, rightY);
}

void PrintDimension(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
	PrintDimension(root->left);
    PrintDimension(root->right);

    if(root->id == -2)
    {
        printf("V(%d,%d)\n", root->width, root->height);
		return;
	}
    if(root->id == -1)
    {
        printf("H(%d,%d)\n", root->width, root->height);
		return;
	}
    printf("%d(%d,%d)\n", root->id, root->width, root->height);
	return;
}

void PrintCoordinates(TreeNode *root)
{
    if(root == NULL)
    {   
        return;
    }   
    PrintCoordinates(root->left);
    PrintCoordinates(root->right);

    if(root->id == -2) 
    {   
        //printf("V((%d,%d)(%d,%d))\n", root->width, root->height, root->x, root->y);
        return;
    }   
    if(root->id == -1) 
    {   
        //printf("H((%d,%d)(%d,%d))\n", root->width, root->height, root->x, root->y);
        return;
    }   
    printf("%d((%d,%d)(%d,%d))\n", root->id, root->width, root->height, root->x, root->y);
    return;
}

static int MAX(int a, int b)
{
	return ((a>b)? a:b);
}
