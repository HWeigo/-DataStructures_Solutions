#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "graph.h"
#include "evaluation.h"

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
		isSuccess = Binary2Txt(argv[2], argv[3]);
		if(!isSuccess)
		{
			return EXIT_FAILURE;
		}
		isSuccess = FindSequence(argv[2], argv[4]);
		if(!isSuccess)
		{
			return EXIT_FAILURE;
		}
	}

	if(!strcmp(argv[1], "-e"))
	{
		isSuccess = Evaluation(argv[2], argv[3]);
		if(!isSuccess)
		{
			return EXIT_FAILURE;
		}
	}
	
//	if(!strcmp(argv[1], "-c"))
//	{
//		//isSuccess = Binary2Txt(argv[2],argv[3]);	
//		TableConstruct(argv[2]);
//		SequenceConstruct(argv[3]);
//	}

	return EXIT_SUCCESS;
}
