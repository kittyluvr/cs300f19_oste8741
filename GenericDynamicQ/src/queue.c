#include "../include/queue.h"
#include <stdbool.h>
#include "../../GenericDynamicPriorityQ/include/pqueue.h"

char gszQErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode){
	printf("Function: %s %s \n ", pszFunctionName,
					 gszQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/

/************************************************************************
 Function: 	 	queueCreate

 Description: create function for queue to make sure everything is set up
 	 	 	 	 	 	 	correctly

 Parameters:	psQueue - pointer to Queue

 Returned:	 	None
 ************************************************************************/
extern void queueCreate (QueuePtr psQueue){
	if(psQueue == NULL){
		processError("queueCreate", ERROR_NO_Q_CREATE);
	}
	pqueueCreate(&psQueue->sTheQueue);
	return;
}
// results: If Q can be created, then Q exists and is empty
//					otherwise, ERROR_NO_Q_CREATE

/*************************************************************************
 Function: 	 	queueTerminate

 Description: Terminate function for queue to make sure everything is
 	 	 	 	 	 	 	removed correctly

 Parameters:	psQueue - pointer to Queue

 Returned:	 	None
 *************************************************************************/
extern void queueTerminate (QueuePtr psQueue){
	if(psQueue == NULL){
		processError("queueTerminate", ERROR_NO_Q_TERMINATE);
	}
	pqueueTerminate(&psQueue->sTheQueue);
	return;
}
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_Q_TERMINATE

/**************************************************************************
 Function: 	 	queueLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_Q_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file. Also calls function to load
 	 	 	 	 	 	  pqueue errors

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
extern void queueLoadErrorMessages (){
	LOAD_Q_ERRORS
	pqueueLoadErrorMessages();
}
// results:	Loads the error message strings for the error handler to use
//					No error conditions

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/

/****************************************************************************
 Function: 	 	queueSize

 Description: Returns size of queue

 Parameters:	psQueue - pointer to Queue

 Returned:	 	Size
 ****************************************************************************/
extern int queueSize (const QueuePtr psQueue){
	if(psQueue == NULL){
		processError("queueSize", ERROR_INVALID_Q);
	}
	return pqueueSize(&psQueue->sTheQueue);
}
// results: Returns the number of elements in the Q
// 					error code priority: ERROR_INVALID_Q if Q is NULL

/****************************************************************************
 Function: 	 	queueIsEmpty

 Description: Returns whether queue is empty

 Parameters:	psQueue - pointer to Queue

 Returned:	 	Is queue empty
 ****************************************************************************/
extern bool queueIsEmpty (const QueuePtr psQueue){
	if(psQueue == NULL){
		processError("queueIsEmpty", ERROR_INVALID_Q);
	}
	return pqueueIsEmpty(&psQueue->sTheQueue);
}
// results: If Q is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_Q

/**************************************************************************
*									Inserting and retrieving values
**************************************************************************/

/****************************************************************************
 Function: 	 	queueEnqueue

 Description: Enqueues pbuffer in queue

 Parameters:	psQueue - pointer to Queue
 	 	 	 	 	 	 	pBuffer - pointer to data
 	 	 	 	 	 	 	size		- size of pbuffer

 Returned:	 	None
 ****************************************************************************/
extern void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size){
	if(psQueue == NULL){
		processError("queueEnqueue", ERROR_INVALID_Q);
	}
	if(pBuffer == NULL){
		processError("queueEnqueue", ERROR_NULL_Q_PTR);
	}
	const int NO_PRIORITY = 0;
	pqueueEnqueue(&psQueue->sTheQueue, pBuffer, size, NO_PRIORITY);
	return;
}
// requires: psQueue is not full
// results: Insert the element into the FIFO queue.
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR

/*************************************************************************
 Function: 	 	queueDequeue

 Description: Removes data from queue

 Parameters:	psQueue - pointer to Queue
 	 	 	 	 	 	 	pBuffer - pointer to fill with data
 	 	 	 	 	 	 	size 		- size of data type

 Returned:	 	None
 ************************************************************************/
extern void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size){
	if(psQueue == NULL){
		processError("queueDequeue", ERROR_INVALID_Q);
	}
	if(pBuffer == NULL){
		processError("queueDequeue", ERROR_NULL_Q_PTR);
	}
	if(queueIsEmpty(psQueue)){
		processError("queueDequeue", ERROR_EMPTY_Q);
	}
	int trash;
	pqueueDequeue(&psQueue->sTheQueue, pBuffer, size, &trash);
	return pBuffer;
}
// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//															 ERROR_EMPTY_Q

/***********************************************************************
*													Peek Operations
***********************************************************************/

/*************************************************************************
 Function: 	 	queuePeek

 Description: Looks at data in queue

 Parameters:	psQueue - pointer to Queue
 	 	 	 	 	 	 	pBuffer - pointer to fill with data
 	 	 	 	 	 	 	size 		- size of data type

 Returned:	 	None
 ************************************************************************/
extern void *queuePeek (QueuePtr psQueue, void *pBuffer, int size){
	if(psQueue == NULL){
		processError("queuePeek", ERROR_INVALID_Q);
	}
	if(pBuffer == NULL){
		processError("queuePeek", ERROR_NULL_Q_PTR);
	}
	if(queueIsEmpty(psQueue)){
		processError("queuePeek", ERROR_EMPTY_Q);
	}
	int trash;
	pqueuePeek(&psQueue->sTheQueue, pBuffer, size, &trash);
	return pBuffer;
}
// requires: psQueue is not empty
// results: The value of the first element is returned through the
//					argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//																 ERROR_EMPTY_Q
