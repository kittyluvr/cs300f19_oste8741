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
extern void queueCreate (QueuePtr psQueue){
	if(psQueue == NULL){
		processError("queueCreate", ERROR_NO_Q_CREATE);
	}
	pqueueCreate(&psQueue->sTheQueue);
	return;
}
// results: If Q can be created, then Q exists and is empty
//					otherwise, ERROR_NO_Q_CREATE


extern void queueTerminate (QueuePtr psQueue){
	if(psQueue == NULL){
		processError("queueTerminate", ERROR_NO_Q_TERMINATE);
	}
	pqueueTerminate(&psQueue->sTheQueue);
	return;
}
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_Q_TERMINATE

extern void queueLoadErrorMessages (){
	LOAD_Q_ERRORS
}
// results:	Loads the error message strings for the error handler to use
//					No error conditions

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/
extern int queueSize (const QueuePtr psQueue){
	return pqueueSize(&psQueue->sTheQueue);
}
// results: Returns the number of elements in the Q
// 					error code priority: ERROR_INVALID_Q if Q is NULL

extern bool queueIsEmpty (const QueuePtr psQueue){
	return pqueueIsEmpty(&psQueue->sTheQueue);
}
// results: If Q is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_Q



/**************************************************************************
*									Inserting and retrieving values
**************************************************************************/
extern void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size);
// requires: psQueue is not full
// results: Insert the element into the FIFO queue.
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR

extern void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size);
// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//															 ERROR_EMPTY_Q

/**************************************************************************
*													Peek Operations
**************************************************************************/
extern void *queuePeek (QueuePtr psQueue, void *pBuffer, int size);
// requires: psQueue is not empty
// results: The value of the first element is returned through the
//					argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//																 ERROR_EMPTY_Q
