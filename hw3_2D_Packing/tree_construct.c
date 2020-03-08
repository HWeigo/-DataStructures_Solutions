#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree_construct.h"

static LinkedList *Push(LinkedList *head, TreeNode *tptr);
static TreeNode *Pop(LinkedList **head);
static TreeNode *TreeNodeCreate(int id, int width, int height);
static TreeNode *TreeConstructHelper(LinkedList **head);

bool TreeConstruct(char *filename, TreeNode **root)
{
    FILE *fptr = NULL;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {   
        fprintf(stderr, "fopen failed.");
        return false;
    }   

    int leafId; 
    int width;
    int height;
    int numGet = 0;
    char internalId;
	LinkedList *stack = NULL;
    do  
    {   
        numGet = fscanf(fptr, "%d(%d,%d)\n", &leafId, &width, &height);
        
		// Meet non-leaf node 
		if(numGet == 0)
        {
            numGet = fscanf(fptr, "%c\n", &internalId);
			if(internalId == 'H')
			{
				TreeNode *tptr =  TreeNodeCreate(-1, 0, 0);
				stack = Push(stack, tptr);
			}
			else if(internalId == 'V')
			{
				TreeNode *tptr = TreeNodeCreate(-2, 0, 0);
				stack = Push(stack, tptr);
			}
			else
			{
				fprintf(stderr, "Write a wrong character.");
				return false;
			}
        }
		// This line is a leaf node
		else if(numGet == 3)
		{
			TreeNode *tptr = TreeNodeCreate(leafId, width, height);
			stack = Push(stack, tptr);
		}
		else
		{
			fprintf(stderr, "Incorrect input.");
		}
    }while(!feof(fptr));

	*root = TreeConstructHelper(&stack);

	fclose(fptr);
	return true;
}

static TreeNode *TreeConstructHelper(LinkedList **head)
{
	if(head == NULL)
	{
		return NULL;
	}
	TreeNode *node = Pop(head);
	if(node->id >= 0)
	{

		return node;
	}
	node->right = TreeConstructHelper(head);
	node->left = TreeConstructHelper(head);
	return node;
}

static TreeNode *TreeNodeCreate(int id, int width, int height)
{
	TreeNode *tptr = NULL;
	tptr = malloc(sizeof(*tptr));
	if(tptr == NULL)
	{
		fprintf(stderr, "TreeNode malloc failed.");
		return NULL;
	}

	tptr->left = NULL;
	tptr->right = NULL;
	tptr->id = id;
	tptr->width = width;
	tptr->height = height;
	tptr->x = 0;
	tptr->y = 0;
	return tptr;
}

static LinkedList *Push(LinkedList *head, TreeNode *tptr)
{
	LinkedList *lptr = NULL;
	lptr = malloc(sizeof(*lptr));
	if(lptr == NULL)
	{
		fprintf(stderr, "LinkedList malloc failed.");
		return NULL;
	}
	
	lptr->next = head;
	lptr->tptr = tptr;

	return lptr;
}

static TreeNode *Pop(LinkedList **head)
{
	LinkedList *lptr = *head;
	if(lptr == NULL)
	{
		return NULL;
	}
	*head = (*head)->next;
	TreeNode *tptr = lptr->tptr;
	free(lptr);

	return tptr;
}

void PreorderTraversal(TreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	if(root->id == -2)
	{
		printf("V\n");
	}
	else if(root->id == -1)
	{
		printf("H\n");
	}
	else
	{
		printf("%d(%d,%d)\n", root->id, root->width, root->height);
	}
	PreorderTraversal(root->left);
	PreorderTraversal(root->right);
}

void TreeDestroy(TreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	TreeDestroy(root->left);
	TreeDestroy(root->right);
	free(root);
}
