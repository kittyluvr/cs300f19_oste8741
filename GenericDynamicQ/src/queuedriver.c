/**************************************************************************
 File name:		  pqueuedriver.c
 Author:        Frisk Oster
 Date:          10/04/19
 Class:         CS300
 Assignment:    Priority Queue Implementation Test
 Purpose:       This file implements the priority queue data structure.
 *************************************************************************/
#include "../include/queue.h"

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

 Description: main function for pqueuedriver. tests pqueue ADT

 Parameters:

 Returned:	 	none
 ****************************************************************************/
int main(){
	Queue sQueue;
	queueCreate(&sQueue);
	assert(queueIsEmpty(&sQueue), "Queue exists and is empty",
			"Error in create.");

	queueTerminate(&sQueue);
	assert(queueIsEmpty(&sQueue), "Queue terminate successful",
			"Error in terminate.");
	return EXIT_SUCCESS;
}
