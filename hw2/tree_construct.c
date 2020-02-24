#include "stdlib.h"
#include "stdio.h"
#include "strings.h"
#include "tree_construct.h"
#include "count_frequency.h"

//#define DEBUG_TREE 

#define MAX(a,b) ((a) > (b))?(a):(b)

typedef struct _ListNode{
    struct _ListNode *next;
    TreeNode *tptr;
}ListNode;
// Linked List
static ListNode *ListNodeConstruct(TreeNode *tp);
static void ListDestroy(ListNode *head);
static void PrintLinkedList(ListNode *lptr);
static void SaveTreeToFileHelper(FILE *fptr, TreeNode *root);

static int qsortHelper(const void *a, const void *b);

static int qsortHelper(const void *a, const void *b)
{
	Freq *A = (Freq*) a;
	Freq *B = (Freq*) b;

	if((A->freq) == 0)
	{
		return 1;
	}
	if((B->freq) == 0)
	{
		return -1;
	}
	return (A->freq - B->freq);

}

static ListNode *ConstructLinkedList(Freq *clist, int *listNum)
{
	qsort(clist, 256, sizeof(Freq), qsortHelper);

#ifdef DEBUG_TREE 
	for(int i=0;i<256;i++)
	{
		printf("%c: %ld\n", clist[i].character, clist[i].freq);
	}
#endif 

	int i = 0;
	*listNum = 0;
	ListNode *lptr;
	ListNode *head;
	while((i != 256) && (clist[i].freq != 0))
	{
		TreeNode *tptr =  TreeNodeConstruct(clist[i].character, clist[i].freq);
		if(i == 0)
		{
			head = ListNodeConstruct(tptr);
			lptr = head;
			(*listNum)++;
			i++;
			continue;
		}
		lptr->next = ListNodeConstruct(tptr);

		lptr = lptr->next;
		(*listNum)++;
		i++;
	}
	return head;
}

static ListNode *CombineFirstTwoNodes(ListNode **head)
{
	ListNode *l = *head;
	ListNode *r = (*head)->next;
	*head = r->next;

	TreeNode *tptr = TreeNodeConstruct(-1, ((l->tptr)->freq+(r->tptr)->freq));
	tptr->left = l->tptr;
	tptr->right = r->tptr;

	ListNode *lptr = ListNodeConstruct(tptr);
	
	free(l);
	free(r);

	return lptr;
}

static ListNode *InsertListNode(ListNode *head, ListNode *new)
{
	long newNodeFreq = (new->tptr)->freq;
	
	if(head == NULL)
	{
		return new; 
	}

	if((head->tptr)->freq > newNodeFreq)
	{
		new->next = head;
		return new;
	}
	ListNode *p = head;
	ListNode *q = head->next;

	while((q != NULL) && ((q->tptr)->freq <= newNodeFreq))
	{
		p = p->next;
		q = q->next;
	}
	new->next = q;
	p->next = new;

	return head;
}

TreeNode *ConstructTree(Freq *clist, int diffNum)
{
	int listNum;
	ListNode *head;
	head = ConstructLinkedList(clist, &listNum);

#ifdef DEBUG_TREE 
	PrintLinkedList(head);
#endif 

	if(listNum != diffNum)
	{
		ListDestroy(head);
		fprintf(stderr, "diffNum not equal to listNum");
		return NULL;
	}

	while(head->next != NULL)
	{
		ListNode *newNode = CombineFirstTwoNodes(&head);
		head = InsertListNode(head, newNode);
		//PrintLinkedList(head);
	}
	TreeNode *huffmanTree = head->tptr;
	free(head);

#ifdef DEBUG_TREE 
	PrintTree(huffmanTree);
	printf("%d\n", CalTreeHeight(huffmanTree));
#endif 

	return huffmanTree;
}

static ListNode *ListNodeConstruct(TreeNode *tp)
{
	ListNode *p = malloc(sizeof(*p));
	p->next = NULL;
	p->tptr = tp;
	return p;
}

static void ListDestroy(ListNode *head)
{
	ListNode *p = NULL;
	while(head != NULL)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

TreeNode *TreeNodeConstruct(int idx, long freq)
{
	TreeNode *p = malloc(sizeof(*p));
	p->left = NULL;
	p->right = NULL;
	p->charIdx = idx;
	p->freq = freq;

	return p;
}

static void SaveTreeToFileHelper(FILE *fptr, TreeNode *root)
{
	if(root->charIdx != -1)
	{
		fprintf(fptr, "1%c", root->charIdx);
		return;
	}
	else
	{
		fprintf(fptr, "0");
	}
	SaveTreeToFileHelper(fptr, root->left);
	SaveTreeToFileHelper(fptr, root->right);
}

void SaveTreeToFile(char *filename, TreeNode *root)
{
	FILE *fptr;
	fptr = fopen(filename, "w+");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen fail.");
		return;
	}
	SaveTreeToFileHelper(fptr, root);

	fclose(fptr);
}

void PrintTree(TreeNode *tptr)
{
	if(tptr == NULL)
	{
		return;
	}
	printf("%c: %ld\n", tptr->charIdx, tptr->freq);
	PrintTree(tptr->left);
	PrintTree(tptr->right);
}

static void PrintLinkedList(ListNode *lptr)
{
	int cnt = 0;
	while(lptr != NULL)
	{
		cnt ++;
		printf("%c: %ld\n", (lptr->tptr)->charIdx, (lptr->tptr)->freq);
		lptr = lptr->next;
	}
	printf("%d\n\n", cnt);
}

void FreeTree(TreeNode *tptr)
{
	if(tptr == NULL)
	{
		return;
	}
	FreeTree(tptr->left);
	FreeTree(tptr->right);
	free(tptr);
}


int CalTreeHeight(TreeNode *tptr)
{
	if(tptr == NULL)
	{
		return 0;
	}
	int l = CalTreeHeight(tptr->left);
	int r = CalTreeHeight(tptr->right);
	//printf("l:%d, r:%d\n",l,r);
	int max = MAX(l, r);
	return (max + 1);
}
