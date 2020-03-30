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
			if((root->left)->left == NULL)
			{
				(root->left)->balance = 0;
				(root->right)->balance = 0;
			}
			if(root->balance == 1)
			{
				root->balance = 0;
				(root->left)->balance = 0;
				(root->right)->balance = -1;
			}
			if(root->balance == -1)
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
			if((root->right)->right == NULL)
			{
				(root->left)->balance = 0;
				(root->right)->balance = 0;
			}
			if(root->balance == 1)
			{
				root->balance = 0;
				(root->left)->balance = 0;
				(root->right)->balance = -1;
			}
			if(root->balance == -1)
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

Tnode *Delete(Tnode *root, int key, int *isUnbalanced)
{
	if(root == NULL)
	{
		return root;
	}

	*isUnbalanced = 0;
	if(key > root->key)
	{
		root->right = Delete(root->right, key, isUnbalanced);
		if(*isUnbalanced)
		{
			root->balance ++;
		}
		if(root->balance == 1)
		{
			*isUnbalanced = 0;
		}
	}
	else if(key < root->key)
	{
		root->left = Delete(root->left, key, isUnbalanced);
		if(*isUnbalanced)
		{
			root->balance --;
		}
		if(root->balance == -1)
		{
			*isUnbalanced = 0;
		}
	}
	// root is the node needed to be deleted
	else
	{
		// root has no chid
		if((root->left == NULL) && (root->right == NULL))
		{
			free(root);
			*isUnbalanced = 1;
			return NULL;
		}
		// root has only right child
		if(root->left == NULL)
		{
			Tnode *tmp = root->right;
			free(root);
			*isUnbalanced = 1;
			return tmp;
		}
		// root has only left child
		if(root->right == NULL)
		{
			Tnode *tmp = root->left;
			free(root);
			*isUnbalanced = 1;
			return tmp;
		}
		Tnode *predecessor = root->left;
		while((predecessor->right != NULL))
		{
			predecessor = predecessor->right;
		}
		root->key = predecessor->key;
		predecessor->key = key + 1;
		root->left = Delete(root->left, key + 1, isUnbalanced);
		if(*isUnbalanced)
		{
			root->balance --;
		}
		if(root->balance == -1)
		{
			*isUnbalanced = 0;
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
			if((root->left)->left == NULL)
			{
				(root->left)->balance = 0;
				(root->right)->balance = 0;
			}
			if(root->balance == 1)
			{
				root->balance = 0;
				(root->left)->balance = 0;
				(root->right)->balance = -1;
			}
			if(root->balance == -1)
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
			if((root->right)->right == NULL)
			{
				(root->left)->balance = 0;
				(root->right)->balance = 0;
			}
			if(root->balance == 1)
			{
				root->balance = 0;
				(root->left)->balance = 0;
				(root->right)->balance = -1;
			}
			if(root->balance == -1)
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
