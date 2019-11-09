
#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>

static void fillAndPrint(FILE* inFile);

int main(int argc, char* argv[]){
	FILE* inFile = NULL;
	if(argc != 2){
		printf("unexpected number of elements");
		return EXIT_FAILURE;
	}
	else{
		inFile = fopen(argv[1], "r");
		if(inFile == NULL){
			printf("error opening file");
			return EXIT_FAILURE;
		}
		fillAndPrint(inFile);
		fclose(inFile);
	}
	return EXIT_SUCCESS;
}

static void fillAndPrint(FILE* inFile){
	const int START = 1;
	char szInput[WORD_MAX];
	int count = 0;
	bool bSuccess;
	TreeNodePtr psTree;
	trCreate(&psTree);

	while(!feof(inFile)){
		fscanf(inFile, "%s", szInput);
		bSuccess = trInsert(&psTree, szInput, START);
		//If insert failed then already in tree
		if(!bSuccess){
			//Get current count
			bSuccess = trFind(psTree, szInput, &count);
			if(bSuccess){
				//Increment it by 1
				trUpdate(psTree, szInput, count + 1);
				if(!bSuccess){
					printf("Error when loading words (2)");
				}
			}
			else{
				printf("Error when loading words (1)");
			}
		}
	}
	trPrintInOrder(psTree);
	trTerminate(&psTree);
}
