/**************************************************************************
 File name:		  pqueue.c
 Author:        Frisk Oster
 Date:          10/04/19
 Class:         CS300
 Assignment:    Priority Queue Implementation
 Purpose:       This file implements the priority queue data structure.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../GenericDynamicList/include/list.h"
#include "../include/pqueue.h"

char gszPQErrors[NUMBER_OF_PQ_ERRORS][MAX_ERROR_PQ_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode){
	printf("Function: %s %s \n ", pszFunctionName,
					 gszPQErrors[errorCode]);
	exit (EXIT_FAILURE);
} //This is just copied from stk.c

//*************************************************************************
//										Allocation and Deallocation
//*************************************************************************

/**************************************************************************
 Function: 	 	pqueueCreate

 Description: Initialize psQueue immediately after creating it to ensure
 	 	 	 	 	 	 	that it has correct values

 Parameters:	psQueue - pointer to queue to initialize

 Returned:	 	None
 *************************************************************************/
extern void pqueueCreate (PriorityQueuePtr psQueue
													/*, 	cmpFunction cmpFunct */){
	if(psQueue == NULL){
		processError("pqueueCreate", ERROR_NO_PQ_CREATE);
	}
	lstCreate(&psQueue->sTheList);
	return;
}
// results: If PQ can be created, then PQ exists and is empty
//					otherwise, ERROR_NO_PQ_CREATE

/**************************************************************************
 Function: 	 	pqueueTerminate

 Description: Empty all of pqueue safely (without memory leaks)

 Parameters:	psQueue - pointer to queue to terminate

 Returned:	 	None
 *************************************************************************/
extern void pqueueTerminate (PriorityQueuePtr psQueue){
	if(psQueue == NULL){
		processError("pqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}

	PriorityQueueElement sTemp;

	if(!lstIsEmpty(&psQueue->sTheList)){
		lstFirst(&psQueue->sTheList);
	}
	while(!lstIsEmpty(&psQueue->sTheList)){
		lstDeleteCurrent(&psQueue->sTheList, &sTemp,
				sizeof(PriorityQueueElement));
		free(sTemp.pData);
	}

  lstTerminate(&psQueue->sTheList);
	return;
}
// results: If PQ can be terminated, then PQ no longer exists and is empty
//				   otherwise, ERROR_NO_PQ_TERMINATE

/**************************************************************************
 Function: 	 	pqueueLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_PQ_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file. Also calls function to load
 	 	 	 	 	 	  list errors

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
extern void pqueueLoadErrorMessages (){
	LOAD_PQ_ERRORS
	lstLoadErrorMessages();
}
// results:	Loads the error message strings for the error handler to use
//					No error conditions

//*************************************************************************
//									Checking number of elements in priority queue
//*************************************************************************

/**************************************************************************
 Function: 	 	pqueueSize

 Description: Find size of pqueue

 Parameters:	psQueue - pointer to queue to find size of

 Returned:	 	num elements in psQueue
 *************************************************************************/
extern int pqueueSize (const PriorityQueuePtr psQueue){
	return lstSize(&psQueue->sTheList);
}
// results: Returns the number of elements in the PQ
// 					error code priority: ERROR_INVALID_PQ if PQ is NULL

/**************************************************************************
 Function: 	 	pqueueIsEmpty

 Description: Return whether or not the pqueueIsEmpty

 Parameters:	psQueue - pointer to queue to check

 Returned:	 	empty or not
 *************************************************************************/
extern bool pqueueIsEmpty (const PriorityQueuePtr psQueue){
	return lstIsEmpty(&psQueue->sTheList);
}
// results: If PQ is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_PQ


//*************************************************************************
//									Inserting and retrieving values
//*************************************************************************

/**************************************************************************
 Function: 	 	pqueueEnqueue

 Description: Add an element to pqueue based on priority

 Parameters:	psQueue  - pointer to queue
 	 	 	 	 	 	  pBuffer  - pointer to data to copy into queue
 	 	 	 	 	 	  size		 - size of pbuffer data type
 	 	 	 	 	 	  priority - priority for placing in queue. Lower number =
 	 	 	 	 	 	  					 higher priority

 Returned:	 	None
 *************************************************************************/
extern void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority){
	if(psQueue == NULL){
		processError("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	if(pBuffer == NULL){
		processError("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}

	//Temp to look at stuff currently in queue
	PriorityQueueElement sTemp;
	//The element to be added to the list backing the queue
	PriorityQueueElement sNew;
	sNew.priority = priority;
	sNew.pData = malloc(size);
	memcpy(sNew.pData, pBuffer, size);

	if(lstIsEmpty(&psQueue->sTheList)){
		lstInsertAfter(&psQueue->sTheList, &sNew, sizeof(PriorityQueueElement));
	}

	else{
		//Check if lowest priority
		lstLast(&psQueue->sTheList);
		lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
		if(sNew.priority >= sTemp.priority){
			lstInsertAfter(&psQueue->sTheList, &sNew, sizeof(PriorityQueueElement));
		}

		else{
			//Check if highest priority
			lstFirst(&psQueue->sTheList);
			lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
			if(sNew.priority < sTemp.priority){
				lstInsertBefore(&psQueue->sTheList, &sNew,
						sizeof(PriorityQueueElement));
			}

			else{
				//Otherwise walk until next is lower priority
				lstPeekNext(&psQueue->sTheList, &sTemp,
						sizeof(PriorityQueueElement));
				while(sNew.priority >= sTemp.priority){
					lstNext(&psQueue->sTheList);
					lstPeekNext(&psQueue->sTheList, &sTemp,
							sizeof(PriorityQueueElement));
				}
				lstInsertAfter(&psQueue->sTheList, &sNew,
						sizeof(PriorityQueueElement));
			}
		}
	}
	return;
}
// requires: psQueue is not full
// results: Insert the element into the priority queue based on the
//          priority of the element.
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_FULL_PQ


/**************************************************************************
 Function: 	 	pqueueDequeue

 Description: Remove first element from queue

 Parameters:	psQueue  - pointer to queue
 	 	 	 	 	 	  pBuffer  - pointer to copy queue data into
 	 	 	 	 	 	  size		 - size of pbuffer data type
 	 	 	 	 	 	  priority - priority of element in queue.

 Returned:	 	pBuffer (pointer to data copied from queue element)
 *************************************************************************/
extern void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int  *pPriority){
	if(psQueue == NULL){
		processError("pqueueDequeue", ERROR_INVALID_PQ);
	}
	if(pBuffer == NULL){
		processError("pqueueDequeue", ERROR_NULL_PQ_PTR);
	}
	if(pqueueIsEmpty(psQueue)){
		processError("pqueueDequeue", ERROR_EMPTY_PQ);
	}

	PriorityQueueElement sTemp;

	lstFirst(&psQueue->sTheList);
	lstDeleteCurrent(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
	memcpy(pBuffer, sTemp.pData, size);
	*pPriority = sTemp.priority;

	free(sTemp.pData);

	return pBuffer;
}
// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_EMPTY_PQ

//*************************************************************************
//													Peek Operations
//*************************************************************************

/**************************************************************************
 Function: 	 	pqueuePeek

 Description: Copy data from first element from queue

 Parameters:	psQueue  - pointer to queue
 	 	 	 	 	 	  pBuffer  - pointer to copy queue data into
 	 	 	 	 	 	  size		 - size of pbuffer data type
 	 	 	 	 	 	  priority - priority of element in queue.

 Returned:	 	pBuffer (pointer to data copied from queue element)
 *************************************************************************/
extern void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								 int *priority){
	if(psQueue == NULL){
		processError("pqueuePeek", ERROR_INVALID_PQ);
	}
	if(pBuffer == NULL){
		processError("pqueuePeek", ERROR_NULL_PQ_PTR);
	}
	if(pqueueIsEmpty(psQueue)){
		processError("pqueuePeek", ERROR_EMPTY_PQ);
	}

	PriorityQueueElement sTemp;
	lstFirst(&psQueue->sTheList);
	lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
	*priority =sTemp.priority;
	memcpy(pBuffer, sTemp.pData, size);

	return pBuffer;
}
// requires: psQueue is not empty
// results: The priority and value of the first element is returned through
//					the argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//																 ERROR_EMPTY_PQ

/**************************************************************************
 Function: 	 	pqueueChangePriority

 Description: Increase/decrease priority of all elements in queue

 Parameters:	psQueue - pointer to queue
 	 	 	 	 	 	  change  - amount to change priority by

 Returned:	 	none
 *************************************************************************/
extern void pqueueChangePriority (PriorityQueuePtr psQueue,
																	int change){
	if(psQueue == NULL){
		processError("pqueueChangePriority", ERROR_INVALID_PQ);
	}

	PriorityQueueElement sTemp;

	//if PQ is empty then do nothing
	if(!pqueueIsEmpty(psQueue)){
		lstFirst(&psQueue->sTheList);
		lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
		sTemp.priority += change;
		lstUpdateCurrent(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
		while(lstHasNext(&psQueue->sTheList)){
			lstNext(&psQueue->sTheList);
			lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
			sTemp.priority += change;
			lstUpdateCurrent(&psQueue->sTheList, &sTemp,
					sizeof(PriorityQueueElement));
		}
	}
	return;
}
// results: The priority of all elements is increased by the amount in
//					change error code priority: ERROR_INVALID_PQ

