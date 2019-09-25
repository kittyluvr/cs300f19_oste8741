/**************************************************************************
 File name:  list.c
 Author:     Frisk Oster
 Date:			 9.18.2019
 Class:			 CS300
 Assignment: GenericDynamicList
 Purpose:    Implementation for a generic dynamic list
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

static ListElementPtr makeNewEmpty(ListElementPtr);
static ListElementPtr makeNewFilled(ListElementPtr, const void *, int);
static ListElementPtr findPrev(ListPtr);
static void assign(ListElementPtr, const void*, int);
static void updateLast(ListPtr);
static void noSaveDelete(ListPtr);

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode){
	printf ("Function: %s %s \n ", pszFunctionName,
					 gszListErrors [errorCode]);
	exit (EXIT_FAILURE);
} //This is just copied from stk.c

/**************************************************************************
 Function: 	 	lstCreate

 Description: Sets up a list to be used.

 Parameters:	psList - pointer to the list to be initialized

 Returned:	 	None
 *************************************************************************/
extern void lstCreate (ListPtr psList){
	if(psList == NULL){
		processError("lstCreate", ERROR_NO_LIST_CREATE);
	}
	psList->numElements = 0;
	psList->psCurrent = NULL;
	psList->psFirst = NULL;
	psList->psLast = NULL;
	return;
}

extern void lstTerminate (ListPtr psList){
	if(psList == NULL){
		processError("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}
	lstFirst(psList);
	while(!lstIsEmpty(psList)){
		noSaveDelete(psList);
	}
	return;
}

/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_LIST_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
extern void lstLoadErrorMessages (){
	LOAD_LIST_ERRORS
}

//*************************************************************************
// Checking number of elements in list
//*************************************************************************
extern int lstSize (const ListPtr psList){
	return psList->numElements;
}

extern bool lstIsEmpty (const ListPtr psList){
	if(psList == NULL){
		processError("lstIsEmpty", ERROR_INVALID_LIST);
	}
	return psList->psFirst == NULL;
}

//*************************************************************************
//												List Testing
//*************************************************************************
extern bool lstHasCurrent (const ListPtr psList){
	if(psList == NULL){
		processError("lstHasCurrent", ERROR_INVALID_LIST);
	}
	return psList->psCurrent != NULL;
}

extern bool lstHasNext (const ListPtr psList){
	if(psList == NULL){
		processError("lstHasNext", ERROR_INVALID_LIST);
	}
	return lstHasCurrent(psList) && (psList->psCurrent->psNext != NULL);
}

//*************************************************************************
//													Peek Operations
//*************************************************************************
extern void *lstPeek (const ListPtr psList, void *pBuffer, int size){
	if(psList == NULL){
		processError("lstPeek", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstPeek", ERROR_NULL_PTR);
	}
	if(lstIsEmpty(psList)){
		processError("lstPeek", ERROR_EMPTY_LIST);
	}
	if(!lstHasCurrent(psList)){
		processError("lstPeek", ERROR_NO_CURRENT);
	}

	memcpy(pBuffer, psList->psCurrent->pData, size);
	return pBuffer;
}

extern void *lstPeekNext (const ListPtr psList, void *pBuffer, int size){
	if(psList == NULL){
		processError("lstPeekNext", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstPeekNext", ERROR_NULL_PTR);
	}
	if(lstIsEmpty(psList)){
		processError("lstPeekNext", ERROR_EMPTY_LIST);
	}
	if(!lstHasCurrent(psList)){
		processError("lstPeekNext", ERROR_NO_CURRENT);
	}
	if(!lstHasNext(psList)){
		processError("lstPeekNext", ERROR_NO_NEXT);
	}

	memcpy(pBuffer, psList->psCurrent->psNext->pData, size);
	return pBuffer;
}

//*************************************************************************
//							Retrieving values and updating current
//*************************************************************************
extern void lstFirst (ListPtr psList){
	if(psList == NULL){
		processError("lstFirst", ERROR_INVALID_LIST);
	}
	if(lstIsEmpty(psList)){
		processError("lstFirst", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psFirst;
	return;
}

extern void lstNext (ListPtr psList){
	if(psList == NULL){
		processError("lstNext", ERROR_INVALID_LIST);
	}
	if(lstIsEmpty(psList)){
		processError("lstNext", ERROR_EMPTY_LIST);
	}
	if(!lstHasNext(psList)){
		processError("lstNext", ERROR_NO_NEXT);
	}

	psList->psCurrent = psList->psCurrent->psNext;
	return;
}

extern void lstLast (ListPtr psList){
	if(psList == NULL){
		processError("lstLast", ERROR_INVALID_LIST);
	}
	if(lstIsEmpty(psList)){
		processError("lstLast", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psLast;
	return;
}

//*************************************************************************
//									Insertion, Deletion, and Updating
//*************************************************************************

extern void lstInsertAfter (ListPtr psList, const void *pBuffer, int size){
	if(psList == NULL){
		processError("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstInsertAfter", ERROR_NULL_PTR);
	}

	if(lstIsEmpty(psList)){
		ListElementPtr psNew = makeNewFilled(NULL, pBuffer, size);
		psList->psFirst = psNew;
		psList->psCurrent = psList->psFirst;
		psList->numElements++;
	}
	else if(!lstHasCurrent(psList)){
		processError("lstInsertAfter", ERROR_NO_CURRENT);
	}
	else{
		ListElementPtr psNew = makeNewFilled(psList->psCurrent->psNext, pBuffer, size);
		psList->psCurrent->psNext = psNew;
		psList->psCurrent = psList->psCurrent->psNext;
		psList->numElements++;
	}
	updateLast(psList);
	return;
}

extern void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size){
	if(psList == NULL){
		processError("lstDeleteCurrent", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstDeleteCurrent", ERROR_NULL_PTR);
	}
	if(lstIsEmpty(psList)){
		processError("lstDeleteCurrent", ERROR_EMPTY_LIST);
	}
	if(!lstHasCurrent(psList)){
		processError("lstDeleteCurrent", ERROR_NO_CURRENT);
	}
	memcpy(pBuffer, psList->psCurrent->pData, size);

	noSaveDelete(psList);
	return pBuffer;
}
// requires: List is not empty
// results: The current element is deleted and its successor and
//				  predecessor become each others successor and predecessor. If
//					the deleted element had a predecessor, then make it the new
// 					current element; otherwise, make the first element current if
// 					it exists. The value of the deleted element is returned.
//          error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//					                     ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void lstInsertBefore (ListPtr psList, const void *pBuffer,
														 int size){
	if(psList == NULL){
		processError("lstInsertBefore", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstInsertBefore", ERROR_NULL_PTR);
	}

	if(!lstHasCurrent(psList) && psList->psFirst != NULL){
			processError("lstInsertBefore", ERROR_NO_CURRENT);
		}
	//Because if the rest is implemented correctly both psFirst
	//and psCurrent should be null if empty so should double for that.
	else if(psList->psCurrent == psList->psFirst){
		ListElementPtr psNew = makeNewFilled(psList->psFirst, pBuffer, size);
		psList->psFirst = psNew;
		psList->psCurrent = psList->psFirst;
		psList->numElements++;
	}
	else{
		psList->psCurrent = findPrev(psList);
		ListElementPtr psNew = makeNewFilled(psList->psCurrent->psNext, pBuffer, size);
		psList->psCurrent->psNext = psNew;
		psList->numElements++;
	}
}
// requires: List is not full
// results:  If the list is not empty, insert the new element as the
//           predecessor of the current element and make the inserted
//           element the current element; otherwise, insert element
//           and make it current.
//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//																ERROR_NO_CURRENT

extern void lstUpdateCurrent (ListPtr psList, const void *pBuffer,
														  int size){
	if(psList == NULL){
		processError("lstUpdateCurrent", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstUpdateCurrent", ERROR_NULL_PTR);
	}
	if(lstIsEmpty(psList)){
		processError("lstUpdateCurrent", ERROR_EMPTY_LIST);
	}
	if(!lstHasCurrent(psList)){
		processError("lstUpdateCurrent", ERROR_NO_CURRENT);
	}

	assign(psList->psCurrent, pBuffer, size);
	return;
}
// requires: List is not empty
// results:  The value of pBuffer is copied into the current element
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//					                       ERROR_EMPTY_LIST, ERROR_NO_CURRENT
// IMPORTANT: user could update with smaller, larger, or the same size data
//					  so free data, then reallocate based on size before updating

//*************************************************************************
//								Static functions for misc. utilities
//*************************************************************************
static ListElementPtr makeNewEmpty(ListElementPtr psOldNext){
	ListElementPtr psNew = (ListElementPtr)malloc(sizeof(ListElement));
	psNew->psNext = psOldNext;
	psNew->pData = NULL;

	return psNew;
}

static ListElementPtr makeNewFilled(ListElementPtr psOldNext, const void *pBuffer, int size){
	ListElementPtr psNew = makeNewEmpty(psOldNext);
	assign(psNew, pBuffer, size);

	return psNew;
}

static ListElementPtr findPrev(ListPtr psList){
	ListElementPtr psIterator = psList->psFirst;

	while(psIterator->psNext != psList->psCurrent){
		psIterator = psIterator->psNext;
	}

	return psIterator;
}

static void assign(ListElementPtr psElement, const void *pUpdate, int size){
	free(psElement->pData);
	psElement->pData = malloc(size);
	memcpy(psElement->pData, pUpdate, size);
}

static void updateLast(ListPtr psList){
	ListElementPtr psTemp = NULL;
	psTemp = psList->psCurrent;
	while(psTemp != NULL && psTemp->psNext != NULL){
		psTemp = psTemp->psNext;
	}
	psList->psLast = psTemp;
	return;
}

static void noSaveDelete(ListPtr psList){
	ListElementPtr psTemp = psList->psCurrent->psNext;
	free(psList->psCurrent->pData);
	if(psList->psCurrent == psList->psFirst){
		psList->psFirst = psTemp;
		free(psList->psCurrent);
		psList->psCurrent = psList->psFirst;
	}
	else{
		psList->psCurrent = findPrev(psList);
		free(psList->psCurrent->psNext);
		psList->psCurrent->psNext = psTemp;
	}
	psList->numElements--;
	updateLast(psList);
	return;
}
