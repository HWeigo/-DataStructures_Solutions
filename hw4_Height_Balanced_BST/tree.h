#ifndef __TREE_H__
#define __TREE_H__

#include "hbt.h"

Tnode *PreorderBSTConstruct(int *arr, int *idx, int size, int ub);
Tnode *CreateTreeNode(int key);
void PrintTreePreorder(Tnode *root);

#endif 
