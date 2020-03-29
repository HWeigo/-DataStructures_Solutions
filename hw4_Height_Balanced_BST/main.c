#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "evaluation.h"
#include "hbt.h"

int main(int argc, char **argv)
{
	bool isSuccess = true;
	//isSuccess = Txt2Binary(argv[1], argv[2]);
	//isSuccess = Binary2Txt(argv[1], argv[2]);
	isSuccess = Evaluation(argv[1]); 
	if(isSuccess == false)
	{
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
