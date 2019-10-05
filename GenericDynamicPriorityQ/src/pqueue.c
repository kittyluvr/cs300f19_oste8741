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

char gszPQErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

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


extern void pqueueTerminate (PriorityQueuePtr psQueue){
	if(psQueue == NULL){
		processError("pqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}

	PriorityQueueElementPtr psTemp = malloc(sizeof(PriorityQueueElement));

	while(!lstIsEmpty(&psQueue->sTheList)){
		lstFirst(&psQueue->sTheList);
		lstDeleteCurrent(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
		free(psTemp->pData);
	}
  
  lstTerminate(&psQueue->sTheList);
	return;
}
// results: If PQ can be terminated, then PQ no longer exists and is empty
//				   otherwise, ERROR_NO_PQ_TERMINATE

extern void pqueueLoadErrorMessages (){
	LOAD_PQ_ERRORS
	lstLoadErrorMessages();
}
// results:	Loads the error message strings for the error handler to use
//					No error conditions

//*************************************************************************
//									Checking number of elements in priority queue
//*************************************************************************

extern int pqueueSize (const PriorityQueuePtr psQueue){
	return lstSize(&psQueue->sTheList);
}
// results: Returns the number of elements in the PQ
// 					error code priority: ERROR_INVALID_PQ if PQ is NULL

extern bool pqueueIsEmpty (const PriorityQueuePtr psQueue){
	return lstIsEmpty(&psQueue->sTheList);
}
// results: If PQ is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_PQ


//*************************************************************************
//									Inserting and retrieving values
//*************************************************************************

extern void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority){
	if(psQueue == NULL){
		processError("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	if(pBuffer == NULL){
		processError("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}

	PriorityQueueElementPtr psTemp = malloc(sizeof(PriorityQueueElement));
	PriorityQueueElementPtr psNew = malloc(sizeof(PriorityQueueElement));
	psNew->priority = priority;
	psNew->pData = malloc(size);
	memcpy(psNew->pData, pBuffer, size);

	if(lstIsEmpty(&psQueue->sTheList)){
		lstInsertAfter(&psQueue->sTheList, psNew, sizeof(PriorityQueueElement));
	}

	else{
		//Check if lowest priority
		lstLast(&psQueue->sTheList);
		lstPeek(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
		if(psNew->priority >= psTemp->priority){
			lstInsertAfter(&psQueue->sTheList, psNew, sizeof(PriorityQueueElement));
		}

		else{
			//Check if highest priority
			lstFirst(&psQueue->sTheList);
			lstPeek(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
			if(psNew->priority < psTemp->priority){
				lstInsertBefore(&psQueue->sTheList, psNew, sizeof(PriorityQueueElement));
			}

			else{
				//Otherwise walk until next is lower priority
				lstPeekNext(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
				while(psNew->priority >= psTemp->priority){
					lstNext(&psQueue->sTheList);
					lstPeekNext(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
				}
				lstInsertAfter(&psQueue->sTheList, psNew, sizeof(PriorityQueueElement));
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

	PriorityQueueElementPtr psTemp = malloc(sizeof(PriorityQueueElement));

	lstFirst(&psQueue->sTheList);
	lstDeleteCurrent(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
	memcpy(pBuffer, psTemp->pData, size);
	*pPriority = psTemp->priority;

	return pBuffer;
}

// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_EMPTY_PQ

//*************************************************************************
//													Peek Operations
//*************************************************************************

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

	PriorityQueueElementPtr psTemp = malloc(sizeof(PriorityQueueElement));
	lstPeek(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
	*priority = psTemp->priority;
	memcpy(pBuffer, psTemp->pData, size);

	return pBuffer;
}
// requires: psQueue is not empty
// results: The priority and value of the first element is returned through
//					the argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//																 ERROR_EMPTY_PQ

extern void pqueueChangePriority (PriorityQueuePtr psQueue,
																	int change){
	if(psQueue == NULL){
		processError("pqueueChangePriority", ERROR_INVALID_PQ);
	}

	PriorityQueueElementPtr psTemp = malloc(sizeof(PriorityQueueElement));

	//if PQ is empty then do nothing
	if(!pqueueIsEmpty(psQueue)){
		lstFirst(&psQueue->sTheList);
		lstPeek(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
		psTemp->priority += change;
		lstUpdateCurrent(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
		while(lstHasNext(&psQueue->sTheList)){
			lstNext(&psQueue->sTheList);
			lstPeek(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
			psTemp->priority += change;
			lstUpdateCurrent(&psQueue->sTheList, psTemp, sizeof(PriorityQueueElement));
		}
	}
	return;
}
// results: The priority of all elements is increased by the amount in
//					change error code priority: ERROR_INVALID_PQ

