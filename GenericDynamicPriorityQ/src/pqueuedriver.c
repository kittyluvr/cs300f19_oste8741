/*
 * pqueuetester.c
 *
 *  Created on: Oct 4, 2019
 *      Author: oste8741
 */
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

int main(){
	const int STRING_MAX = 256;
	const int TOP_PRIORITY = 0;
	const int LOOP_START = 0;
	const int TEN = 10;
	const int TEST_SIZE = TEN * TEN;
	const int TEST_SIZE_2 = 20;
	const int PRIORITY_INCREASE = 3;

	char szMsg[STRING_MAX];

	bool loopCheck = true;

	int testInt = 23;
	int bufferInt = 0;
	int bufferPriority = 1;
	int i = 0;
	int fancyTestLocation = 0;

	pqueueLoadErrorMessages();

	PriorityQueue sQueue;
	pqueueCreate(&sQueue);
	assert(pqueueIsEmpty(&sQueue)&&pqueueSize(&sQueue) == 0, "Queue is empty", "Why does queue have data or size does not match empty?");

	pqueueEnqueue(&sQueue, &testInt, sizeof(int), TOP_PRIORITY);
	assert(pqueueSize(&sQueue) == 1, "Queue has an element", "Enqueue error");
	pqueuePeek(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
	assert(bufferInt == testInt, "Peek correct", "Peek error");
	assert(bufferPriority == TOP_PRIORITY, "Priority check correct", "Priority changed somehow?");
	bufferInt = 0;
	bufferPriority = 1;
	pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
	assert(bufferInt == testInt, "Dequeue correct", "Dequeue error");
	assert(bufferPriority == TOP_PRIORITY, "Priority check correct",
			"Priority changed somehow?");
	assert(pqueueIsEmpty(&sQueue), "Queue is empty again",
			"Queue element still there?");

	for(i = LOOP_START; i < TEST_SIZE; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), i % 10);
	}
	assert(pqueueSize(&sQueue) == TEST_SIZE - LOOP_START,
			"Queue is the correct size", "Weird number of queue elements");
	pqueueChangePriority(&sQueue, PRIORITY_INCREASE);
	for(i = LOOP_START; i < TEST_SIZE_2; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), i/10);
	}
	assert(pqueueSize(&sQueue) == (TEST_SIZE - LOOP_START + TEST_SIZE_2 - LOOP_START), "Queue is the correct size", "Weird number of queue elements");
	pqueuePeek(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
	assert(bufferInt == LOOP_START, "Loop order seems correct, will confirm", "unexpected first number");

	for(i = LOOP_START; loopCheck && i < TEST_SIZE_2; i++){
		pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
		if(i != bufferInt || i/10 != bufferPriority){
			loopCheck = false;
			sprintf(szMsg, "Error in second set added. Value is %d, expected %d, priority is %d, expected %d", bufferInt, i, bufferPriority, i/10);
		}
		bufferInt = 0;
		bufferPriority = 0;
	}
	assert(loopCheck, "Change Priority and second set adding at start successful", szMsg);

	loopCheck = true;
	for(fancyTestLocation = LOOP_START; loopCheck && fancyTestLocation < TEN; fancyTestLocation++){
		for(i = LOOP_START; loopCheck && i < TEN; i++){
			pqueueDequeue(&sQueue, &bufferInt, sizeof(int), &bufferPriority);
			if(bufferInt != i * TEN + fancyTestLocation || bufferPriority != PRIORITY_INCREASE + fancyTestLocation){
				loopCheck = false;
				sprintf(szMsg, "Value is %d, expected %d, priority is %d, expected %d", bufferInt, i * TEN + fancyTestLocation, bufferPriority, fancyTestLocation);
			}
			bufferInt = 0;
			bufferPriority = 0;
		}
		assert(loopCheck, "this check successful", szMsg);
	}

	pqueueTerminate(&sQueue);
	assert(pqueueIsEmpty(&sQueue), "Terminate Successful", "Terminate Error");

	for(i = LOOP_START; i < TEN; i++){
		pqueueEnqueue(&sQueue, &i, sizeof(int), i);
	}
	pqueueTerminate(&sQueue);
	assert(pqueueIsEmpty(&sQueue), "Terminate Successful", "Terminate Error");

	return EXIT_SUCCESS;
}
