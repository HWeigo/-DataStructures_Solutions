#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "evaluation.h"
#include "tree.h"
#include "hbt.h"


static Tnode *RightRotate(Tnode *Tn)
{
	Tnode *leftTn = Tn->left;
	Tnode *tmp = leftTn->right;

	leftTn->right = Tn;
	Tn->left = tmp;

//	if(Tn->balance == -2)
//	{
//		Tn->balance = 0;
//		leftTn->balance = 0;
//	}
//	if(Tn->balance == -1)
//	{
//		if()
//	}
//
	return leftTn;
}

static Tnode *LeftRotate(Tnode *Tn)
{
	Tnode *rightTn = Tn->right;
	Tnode *tmp = rightTn->left;

	rightTn->left = Tn;
	Tn->right = tmp;

	return rightTn;
//	if(Tn->balance == -2)
//	{
//		Tn->balance = 0;
//		rightTn->balance = 0;
//	}
//	if(Tn->balance == -1)
//	{
//		if(rightTn->balance == 1)
//		{
//			Tn->balance = 0;
//			rightTn->balance = 2;
//		}
//		if(rightTn->balance == -1)
//		{
//			Tn->balance = 1;
//			rightTn->balance = 0;
//		}
//		if(rightTn->balance == 0)
//		{
//			Tn->balance = 0;
//			rightTn->balance = 1;
//		}
//	}

}

Tnode *Insert(Tnode *root, int key, int *isUnbalanced)
{
	if(root == NULL)
	{
		*isUnbalanced = 1;
		return CreateTreeNode(key);
	}
	
	*isUnbalanced = 0;
	if(key <= root->key)
	{
		root->left = Insert(root->left, key, isUnbalanced);
		if(*isUnbalanced)
		{
			root->balance ++;
		}
	}
	else
	{
		root->right = Insert(root->right, key, isUnbalanced);
		if(*isUnbalanced)
		{
			root->balance --;
		}
	}

	if(root->balance == 2)
	{
		Tnode *leftNode = root->left;
		if(leftNode->balance == 1)
		{
			root = RightRotate(root);
			root->balance = 0;
			(root->right)->balance = 0;
		}
		if(leftNode->balance == -1)
		{
			root->left = LeftRotate(root->left);
			root = RightRotate(root);
			if(leftNode->left == NULL)
			{
				(root->left)->balance = 0;
				(root->right)->balance = 0;
			}
			if((leftNode->right)->balance == 1)
			{
				root->balance = 0;
				(root->left)->balance = 0;
				(root->right)->balance = -1;
			}
			if((leftNode->left)->balance == -1)
			{
				root->balance = 0;
				(root->left)->balance = 1;
				(root->right)->balance = 0;
			}
		}
		*isUnbalanced = 0;		
	}
	if(root->balance == -2)
	{
		Tnode *rightNode = root->right;
		if(rightNode->balance == -1)
		{
			root = LeftRotate(root);
			root->balance = 0;
			(root->left)->balance = 0;
		}
		if(rightNode->balance == 1)
		{
			root->right = RightRotate(root->right);
			root = LeftRotate(root);
			if(rightNode->right == NULL)
			{
				(root->left)->balance = 0;
				(root->right)->balance = 0;
			}
			if((rightNode->left)->balance == 1)
			{
				root->balance = 0;
				(root->left)->balance = 0;
				(root->right)->balance = -1;
			}
			if((rightNode->left)->balance == -1)
			{
				root->balance = 0;
				(root->left)->balance = 1;
				(root->right)->balance = 0;
			}
		}
		*isUnbalanced = 0;
	}

	return root;
}



