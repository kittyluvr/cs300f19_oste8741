#include <stdio.h>
#include <stdlib.h>

#include "../include/list.h"


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

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void assert(bool bExpression, char *pTrue, char *pFalse) {
	if (bExpression) {
		success(pTrue);
	} else {
		failure(pFalse);
	}
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main(){
	int testInt = 23;
	int bufferInt = 0;
	//char testChar = 'a';
	//char bufferChar = 'a';
	int i = 0;

	lstLoadErrorMessages();

	List sTheList;
	lstCreate(&sTheList);
	assert(lstIsEmpty(&sTheList), "List is empty", "List has values for some reason?");

	lstInsertAfter(&sTheList, &testInt, sizeof(int));
	assert(!lstIsEmpty(&sTheList), "List is no longer empty", "List is still empty for some reason");
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == testInt, "Int stored correctly", "Error peeking");
	bufferInt = 0;

	lstDeleteCurrent(&sTheList, &bufferInt, sizeof(int));
	assert(lstIsEmpty(&sTheList), "Element deleted successfully", "Element not deleted");
	assert(bufferInt == testInt, "Copy from deletion correct", "Copy from deletion incorrect");

	for(i = 0; i < 10; i++){
		lstInsertAfter(&sTheList, &i, sizeof(int));
	}
	assert(lstSize(&sTheList) == 10, "Added 10 elements successfully", "Error adding elements");

	lstFirst(&sTheList);
	lstPeekNext(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == 1, "Peek next works", "Peek next doesn't work");
	bufferInt = 0;

	//has to be one less because of that first movement
	for(i = 0; i < 9; i++){
		lstPeek(&sTheList, &bufferInt, sizeof(int));
		printf("bufferInt is %d ", bufferInt);
		assert(bufferInt == i, "Correctly walking", "Walk failure");
		bufferInt = 0;
		lstNext(&sTheList);
	}
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	printf("bufferInt is %d ", bufferInt);
	assert(bufferInt == i, "Correctly walking", "Walk failure");
	bufferInt = 0;

	lstFirst(&sTheList);
	lstInsertBefore(&sTheList, &testInt, sizeof(int));
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == testInt, "Insert before successful", "Insert before failed");


	lstTerminate(&sTheList);
	assert(lstIsEmpty(&sTheList), "terminated", "list still has stuff");

	return EXIT_SUCCESS;
}
