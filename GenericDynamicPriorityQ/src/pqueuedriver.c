/**************************************************************************
 File name:		  pqueuedriver.c
 Author:        Frisk Oster
 Date:          10/04/19
 Class:         CS300
 Assignment:    Priority Queue Implementation Test
 Purpose:       This file implements the priority queue data structure.
 *************************************************************************/
#include "../include/pqueue.h"

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
	//Make constants for testing (change these to test different cases
	//Loop test case related
	const int LOOP_START = 0;
	const int PRIORITY_DIVISION = 50;
	const int NUM_TEST_DIVISIONS = 200;
	const int TEST_SIZE = PRIORITY_DIVISION * NUM_TEST_DIVISIONS;
	//Other consts
	const int STRING_MAX = 256;
	const int TOP_PRIORITY = 0;
	const int PRIORITY_INCREASE = 10;
	const int TEST_SIZE_2 = 250;
	const int MASSIVE_TEST_SIZE = 1000000;
	const int BIG_TEST_PRIORITY = PRIORITY_DIVISION * 2;
	//Don't change these constants
	const int QUEUE_EMPTY = 0;

	//Error message string
	char szMsg[STRING_MAX];

	//Bool for checking loop
	bool loopCheck = true;

	int testInt = 23;
	int bufferInt = 0;
	int bufferPriority = 1;
	int i = 0;
	int loopTestLocation = 0;

	//Load errors
	pqueueLoadErrorMessages();

	//Make pqueue and check it's correct
	PriorityQueue sQueue;
	pqueueCreate(&sQueue);
	assert(pqueueIsEmpty(&sQueue)&&pqueueSize(&sQueue) == QUEUE_EMPTY,
			"Queue is empty",
			"Why does queue have data or size does not match empty?");

	//Simple enqueue testassert(loopCheck, "this check successful", szMsg);
	pqueueEnqueue(&sQueue, &testInt, sizeof(int), TOP_PRIORITY);
	assert(pqueueSize(&sQueue) == 1, "Queue has an element", "Enqueue error");

	//Simple peek test
	pqueuePeek(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
	assert(bufferInt == testInt, "Peek correct", "Peek error");
	assert(bufferPriority == TOP_PRIORITY, "Priority check correct",
			"Priority changed somehow?");
	bufferInt = 0;
	bufferPriority = 1;

	//Simple dequeue test
	pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
	assert(bufferInt == testInt, "Dequeue correct", "Dequeue error");
	assert(bufferPriority == TOP_PRIORITY, "Priority check correct",
			"Priority changed somehow?");
	assert(pqueueIsEmpty(&sQueue), "Queue is empty again",
			"Queue element still there?");

	//Fill with items
	for(i = LOOP_START; i < TEST_SIZE; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), i % PRIORITY_DIVISION);
	}
	assert(pqueueSize(&sQueue) == TEST_SIZE - LOOP_START,
			"Queue is the correct size", "Weird number of queue elements");

	//Change priority test (Check in later loop)
	pqueueChangePriority(&sQueue, PRIORITY_INCREASE);

	//Add more items of a higher priority
	for(i = LOOP_START; i < TEST_SIZE_2; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), i/PRIORITY_DIVISION);
	}
	assert(pqueueSize(&sQueue) == (TEST_SIZE - LOOP_START +
			TEST_SIZE_2 - LOOP_START), "Queue is the correct size",
			"Weird number of queue elements");
	pqueuePeek(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
	assert(bufferInt == LOOP_START, "Loop order seems correct, will confirm",
			"unexpected first number");

	//Check added info in above loop
	for(i = LOOP_START; loopCheck && i < TEST_SIZE_2; i++){
		pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
		if(i != bufferInt || i/PRIORITY_DIVISION != bufferPriority){
			loopCheck = false;
			sprintf(szMsg,
					"Error in second set added. Received %d, %d, expected %d %d",
					bufferInt, bufferPriority, i, i/PRIORITY_DIVISION);
		}
		bufferInt = 0;
		bufferPriority = 0;
	}
	assert(loopCheck,
			"Change Priority and second set adding at start successful", szMsg);

	//Loop to check first set of nums added and priority increase
	loopCheck = true;
	for(loopTestLocation = LOOP_START; loopCheck &&
		loopTestLocation < PRIORITY_DIVISION; loopTestLocation++){
		//loop to check each priority
		for(i = LOOP_START; loopCheck && i < NUM_TEST_DIVISIONS; i++){
			pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
			if(bufferInt != i * PRIORITY_DIVISION + loopTestLocation
					|| bufferPriority != PRIORITY_INCREASE + loopTestLocation){
				loopCheck = false;
				sprintf(szMsg,
					"Received %d, %d, expected %d, %d (loop numbers: %d, %d)",
					bufferInt, bufferPriority, i * PRIORITY_DIVISION + loopTestLocation,
					loopTestLocation, loopTestLocation, i);
			}
			bufferInt = 0;
			bufferPriority = 0;
		}
		if(!loopCheck){
			failure(szMsg);
		}
	}
	if(loopCheck){
		success("Loop to check confirms all items added successfully");
	}
	assert(pqueueIsEmpty(&sQueue),"All items dequeued successfully",
			"items still enqueued");

	//terminate check (list should be empty at this point)
	pqueueTerminate(&sQueue);
	assert(pqueueIsEmpty(&sQueue), "Terminate Successful", "Terminate Error");

	//check for terminate with items in the queue + check many items
	for(i = LOOP_START; i < MASSIVE_TEST_SIZE; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), BIG_TEST_PRIORITY);
	}
	assert(pqueueSize(&sQueue) == MASSIVE_TEST_SIZE - LOOP_START,
			"Large test case elements added", "Error adding many items");
	for(i = LOOP_START; i < TEST_SIZE_2; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), i/PRIORITY_DIVISION);
	}
	assert(pqueueSize(&sQueue) == (MASSIVE_TEST_SIZE - LOOP_START +
			TEST_SIZE_2 - LOOP_START), "Queue is the correct size",
			"Weird number of queue elements");
	for(i = LOOP_START; loopCheck && i < TEST_SIZE_2; i++){
		pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
		if(i != bufferInt || i/PRIORITY_DIVISION != bufferPriority){
			loopCheck = false;
			sprintf(szMsg,
					"Error in adding to large queue. Received %d, %d, expected %d, %d",
					bufferInt, bufferPriority, i, i/PRIORITY_DIVISION);
		}
		bufferInt = 0;
		bufferPriority = 0;
	}
	assert(loopCheck, "When queue has many items queue/enqueue still works",
			szMsg);
	pqueueTerminate(&sQueue);
	assert(pqueueIsEmpty(&sQueue), "Terminate Successful", "Terminate Error");

	return EXIT_SUCCESS;
}
