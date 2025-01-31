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
	if(root == NULL)
	{
		return;
	}
	CalcCoordinatesHelper(root, 0, 0);
	return;
}

static void CalcDimensionHelper(TreeNode *root, int *width, int *height)
{
	// Should not reach here 
	if(root == NULL)
	{
		fprintf(stderr, "Tree error.\n");
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
	int leftWidth = 0;
	int leftHeight = 0;
	int rightWidth = 0;
	int rightHeight = 0;
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
		fprintf(stderr, "Tree error.\n");
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

	int leftX = 0;
	int leftY = 0;
	int rightX = 0;
	int rightY = 0;
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

void PrintDimension(TreeNode *root, FILE *fptr)
{
    if(root == NULL)
    {
        return;
    }
	PrintDimension(root->left, fptr);
    PrintDimension(root->right, fptr);

    if(root->id == -2)
    {
        fprintf(fptr, "V(%d,%d)\n", root->width, root->height);
		return;
	}
    if(root->id == -1)
    {
        fprintf(fptr, "H(%d,%d)\n", root->width, root->height);
		return;
	}
    fprintf(fptr, "%d(%d,%d)\n", root->id, root->width, root->height);

	return;
}

void PrintCoordinates(TreeNode *root, FILE *fptr)
{
    if(root == NULL)
    {   
        return;
    }   

	PrintCoordinates(root->left, fptr);
    PrintCoordinates(root->right, fptr);

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
    fprintf(fptr, "%d((%d,%d)(%d,%d))\n", root->id, root->width, root->height, root->x, root->y);
    return;
}

static int MAX(int a, int b)
{
	return ((a>b)? a:b);
}
