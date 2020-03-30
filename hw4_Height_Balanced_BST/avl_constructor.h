#ifndef __AVL_CONSTRUCTOR_H__
#define __AVL_CONSTRUCTOR_H__

#include "hbt.h"

Tnode *Insert(Tnode *root, int key, int *isUnbalanced);
Tnode *Delete(Tnode *root, int key, int *isUnbalanced);

#endif
