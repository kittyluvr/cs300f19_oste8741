/**************************************************************************
 File name:		  treedriver.c
 Author:        Frisk Oster
 Date:          10/04/19
 Class:         CS300
 Assignment:   	Tree Implementation Test
 Purpose:       This file implements the BST data structure.
 *************************************************************************/
#include "../include/tree.h"
#include <stdio.h>

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success(char *pszStr) {
	printf("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void failure(char *pszStr) {
	printf("FAILURE: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 failure

 Parameters:	bExpression - Expression being asserted as true
 	 	 	 	 	 	 	pTrue				- String to print if successful
 	 	 	 	 	 	 	pFalse			- String to print if failure

 Returned:	 	none
 ****************************************************************************/
static void assert(bool bExpression, char *pTrue, char *pFalse) {
	if (bExpression) {
		success(pTrue);
	} else {
		failure(pFalse);
	}
}

/****************************************************************************
 Function: 	 	main

 Description: main function for treedriver. tests tree ADT

 Parameters:

 Returned:	 	none
 ****************************************************************************/
int main(){
	bool bFound = true;
	int dump;
	char szTest[WORD_MAX];
	TreeNodePtr psTree;
	trLoadErrorMessages();

	//Check create
	trCreate(&psTree);
	assert(trIsEmpty(psTree), "tree creation as expected", "new tree weird");

	//Insert some values
	trInsert(&psTree, "D", 1);
	trInsert(&psTree, "E", 2);
	trInsert(&psTree, "A", 3);
	trInsert(&psTree, "B", 4);
	trInsert(&psTree, "C", 5);
	trInsert(&psTree, "F", 6);
	trInsert(&psTree, "G", 7);
	trInsert(&psTree, "J", 8);
	trInsert(&psTree, "H", 9);
	trInsert(&psTree, "I", 10);

	//Cursory check
	assert(psTree->count == 1, "Root as expected", "weird root?");
	assert(psTree->psLeft->count == 3 && psTree->psLeft->psLeft == NULL,
			"Leftmost as expected", "weird tree");
	assert(psTree->psRight->psRight->psRight->psRight->count == 8 &&
			psTree->psRight->psRight->psRight->psRight->psRight == NULL,
			"Rightmost as expected", "weird tree");

	//Check order
	for(szTest[0] = 'A'; bFound && szTest[0] <= 'J'; szTest[0]++){
		bFound = trFind(psTree, szTest, &dump);
		if(bFound){
			switch (szTest[0]){
				case 'A':
					bFound = dump == 3;
					break;
				case 'B':
					bFound = dump == 4;
					break;
				case 'C':
					bFound = dump == 5;
					break;
				case 'D':
					bFound = dump == 1;
					break;
				case 'E':
					bFound = dump == 2;
					break;
				case 'F':
					bFound = dump == 6;
					break;
				case 'G':
					bFound = dump == 7;
					break;
				case 'H':
					bFound = dump == 9;
					break;
				case 'I':
					bFound = dump == 10;
					break;
				case 'J':
					bFound = dump == 8;
					break;
				default:
					bFound = false;
					break;
			}
		}
	}
	assert(bFound, "Tree ordered successfully", "Tree out of order");

	//Update all to 0
	for(szTest[0] = 'A'; bFound && szTest[0] <= 'J'; szTest[0]++){
		bFound = trUpdate(psTree, szTest, 0);
	}
	assert(bFound, "could find all to update", "update error");

	//Check
	for(szTest[0] = 'A'; bFound && szTest[0] <= 'J'; szTest[0]++){
		bFound = trFind(psTree, szTest, &dump);
		if(bFound){
			bFound = dump == 0;
		}
	}
	assert(bFound, "update correct", "update error");

	//Try finding something not present
	bFound = trFind(psTree, "Z", &dump);
	assert(!bFound, "Find correct", "claims found item not present");

	//Try updating something not present
	bFound = true;
	bFound = trUpdate(psTree, "Z", 3);
	assert(!bFound, "update exited correctly", "update weirdness");

	//Try inserting something already present
	bFound = true;
	bFound = trInsert(&psTree, "A", 100);
	assert(!bFound, "insert check correct", "insert weirdness");

	trTerminate(&psTree);
	assert(trIsEmpty(psTree), "Terminate successful", "Terminate error");

	return EXIT_SUCCESS;
}
