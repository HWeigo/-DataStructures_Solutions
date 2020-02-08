#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_array.h"

static addNode(List *
Node *List_Load_From_File(char *filename)
{
	FILE *fptr;
    fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "fopen failed.");
        return -1;
    }
}

int List_Save_To_File(char *filename, Node *list)
{
}

