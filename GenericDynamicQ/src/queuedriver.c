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
	const int LOOP_SIZE  = 1000000;
	const int LOOP_START = 0;
	const int TEST_INT = 23;
	const int STRING_MAX = 128;

	int i;
	int buffer;
	bool loopCheck = true;

	char szMsg[STRING_MAX];

	Queue sQueue;
	queueCreate(&sQueue);
	assert(queueIsEmpty(&sQueue), "Queue exists and is empty",
			"Error in create.");

	queueEnqueue(&sQueue, &TEST_INT, sizeof(int));
	queuePeek(&sQueue, &buffer, sizeof(int));
	assert(buffer == TEST_INT, "Peek works correctly", "Peek error");
	queueDequeue(&sQueue, &buffer, sizeof(int));
	assert(buffer == TEST_INT && queueIsEmpty(&sQueue), "Dequeue successful",
			"Error in dequeue");

	for(i = 0; i < LOOP_SIZE; i++){
		queueEnqueue(&sQueue, &i, sizeof(int));
	}
	assert(queueSize(&sQueue) == LOOP_SIZE, "Enqueued large test", "Enqueue error");
	for(i = 0; loopCheck && i < LOOP_SIZE; i++){
		queueDequeue(&sQueue, &buffer, sizeof(int));
		if(buffer != i){
			loopCheck = false;
			sprintf(szMsg,"Error in big test. Expected %d, received %d", i, buffer);
		}
	}
	assert(loopCheck, "Large test success.", szMsg);
	assert(queueIsEmpty(&sQueue), "Queue where expected",
			"queue still has elements");

	queueTerminate(&sQueue);
	assert(queueIsEmpty(&sQueue), "Queue terminate successful",
			"Error in terminate.");
	return EXIT_SUCCESS;
}
