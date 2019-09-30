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
	const int TEST_INT = 23;
	const int LOOP_START = 0;
	const int LOOP_SIZE = 10 - LOOP_START;
	const int STRING_MAX = 128;

	char szMsg[STRING_MAX];

	int bufferInt = 0;
	int i = 0;

	lstLoadErrorMessages();

	List sTheList;
	lstCreate(&sTheList);
	assert(lstIsEmpty(&sTheList), "List is empty",
			"List has values for some reason?");
	assert(!lstHasCurrent(&sTheList), "Creation appears correct",
			"Current exists upon creation for some reason");

	lstInsertAfter(&sTheList, &TEST_INT, sizeof(int));
	assert(!lstIsEmpty(&sTheList), "List is no longer empty",
			"List is still empty for some reason");
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == TEST_INT, "Int stored correctly", "Error peeking");
	bufferInt = 0;

	lstDeleteCurrent(&sTheList, &bufferInt, sizeof(int));
	assert(lstIsEmpty(&sTheList), "Element deleted successfully",
			"Element not deleted");
	assert(bufferInt == TEST_INT, "Copy from deletion correct",
			"Copy from deletion incorrect");

	for(i = LOOP_START; i < LOOP_SIZE; i++){
		lstInsertAfter(&sTheList, &i, sizeof(int));
	}
	assert(lstSize(&sTheList) == LOOP_SIZE, "Added 10 elements successfully",
			"Error adding elements");

	lstFirst(&sTheList);
	lstPeekNext(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == LOOP_START + 1, "Peek next works",
			"Peek next doesn't work");
	bufferInt = 0;

	for(i = LOOP_START; i < LOOP_SIZE; i++){
		lstPeek(&sTheList, &bufferInt, sizeof(int));
		sprintf(szMsg, "Expected peek value is %d, Actual is %d", i, bufferInt);
		assert(bufferInt == i, szMsg, szMsg);
		bufferInt = 0;
		lstNext(&sTheList);
	}
	bufferInt = 0;

	lstLast(&sTheList);
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == LOOP_SIZE - 1, "List moved to last", "lstLast failed");

	lstFirst(&sTheList);
	lstNext(&sTheList);
	lstNext(&sTheList);
	lstNext(&sTheList);
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == LOOP_START + 3, "Moved to expected location", "Not where expected");

	lstDeleteCurrent(&sTheList, &bufferInt, sizeof(int));
	assert(lstSize(&sTheList) == LOOP_SIZE - 1, "Deleted one correctly",
			"Did Not delete correctly");
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == LOOP_START + 2, "Where expected after delete",
			"Not where expected after delete");

	lstUpdateCurrent(&sTheList, &TEST_INT, sizeof(int));
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == TEST_INT, "Updated correctly", "Updated incorrectly");

	lstFirst(&sTheList);
	lstInsertBefore(&sTheList, &TEST_INT, sizeof(int));
	lstPeek(&sTheList, &bufferInt, sizeof(int));
	assert(bufferInt == TEST_INT, "Insert before successful",
			"Insert before failed");

	lstTerminate(&sTheList);
	assert(lstIsEmpty(&sTheList), "Terminated list", "list still has stuff");

	return EXIT_SUCCESS;
}
