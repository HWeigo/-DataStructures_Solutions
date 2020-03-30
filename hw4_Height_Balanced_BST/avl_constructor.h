#ifndef __AVL_CONSTRUCTOR_H__
#define __AVL_CONSTRUCTOR_H__

#include "hbt.h"

Tnode *Insert(Tnode *root, int key, int *isUnbalanced, int *isMemoryAllocated);
Tnode *Delete(Tnode *root, int key, int *isUnbalanced);
bool AVLConstruct(char *opsFile, char *treeFile);
#endif
