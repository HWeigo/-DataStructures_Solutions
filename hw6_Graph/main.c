#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "graph.h"

int main(int argc, char **argv)
{
	if(argc > 5)
	{
		fprintf(stderr, "incorrect input.");
		return EXIT_FAILURE;
	}

	bool isSuccess = true;
	if(!strcmp(argv[1], "-s"))
	{
		LinkList **graph = NULL;
		graph = GraphConstruct(argv[2]);
		//Destroy(graph,16);
	}

	if(!strcmp(argv[1], "-e"))
	{
	}
	
	if(!strcmp(argv[1], "-c"))
	{
		isSuccess = Binary2Txt(argv[2],argv[3]);	
	}
	if(!isSuccess)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
