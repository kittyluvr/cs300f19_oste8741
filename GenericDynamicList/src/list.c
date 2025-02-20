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

/**************************************************************************
 Function: 	 	lstTerminate

 Description: Clears list so it can be deleted without memleaks

 Parameters:	psList - pointer to the list to be terminated

 Returned:	 	None
 *************************************************************************/
extern void lstTerminate (ListPtr psList){
	if(psList == NULL){
		processError("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}

	while(!lstIsEmpty(psList)){
		lstFirst(psList);
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

/**************************************************************************
 Function: 	 	lstSize

 Description: Returns size of list

 Parameters:	psList - pointer to the list

 Returned:	 	size
 *************************************************************************/
extern int lstSize (const ListPtr psList){
	return psList->numElements;
}

/**************************************************************************
 Function: 	 	lstIsEmpty

 Description: Returns true if list is empty

 Parameters:	psList - pointer to the list

 Returned:	 	is list empty
 *************************************************************************/
extern bool lstIsEmpty (const ListPtr psList){
	if(psList == NULL){
		processError("lstIsEmpty", ERROR_INVALID_LIST);
	}
	return psList->psFirst == NULL;
}

//*************************************************************************
//												List Testing
//*************************************************************************

/**************************************************************************
 Function: 	 	lstHasCurrent

 Description: Returns if list has a current

 Parameters:	psList - pointer to the list

 Returned:		is current not null
 *************************************************************************/
extern bool lstHasCurrent (const ListPtr psList){
	if(psList == NULL){
		processError("lstHasCurrent", ERROR_INVALID_LIST);
	}
	return psList->psCurrent != NULL;
}

/**************************************************************************
 Function: 	 	lstHasNext

 Description: Checks for a next in current

 Parameters:	psList - pointer to the list

 Returned:		next does/doesn't exist
 *************************************************************************/
extern bool lstHasNext (const ListPtr psList){
	if(psList == NULL){
		processError("lstHasNext", ERROR_INVALID_LIST);
	}
	return lstHasCurrent(psList) && (psList->psCurrent->psNext != NULL);
}

//*************************************************************************
//													Peek Operations
//*************************************************************************

/**************************************************************************
 Function: 	 	lstPeek

 Description: Copies data from current into pBuffer

 Parameters:	psList 	- pointer to the list
 	 	 	 	 	 	 	pBuffer - pointer to buffer to put data
 	 	 	 	 	 	 	size 		- size of datatype of pData

 Returned:	 	pBuffer
 *************************************************************************/
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

/**************************************************************************
 Function: 	 	lstPeekNext

 Description: Copies data from next into pBuffer

 Parameters:	psList 	- pointer to the list
 	 	 	 	 	 	 	pBuffer - pointer to buffer to put data
 	 	 	 	 	 	 	size 		- size of datatype

 Returned:	 	pBuffer
 *************************************************************************/
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

/**************************************************************************
 Function: 	 	lstFirst

 Description: Moves current to the first element

 Parameters:	psList - pointer to the list

 Returned:	 	None
 *************************************************************************/
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

/**************************************************************************
 Function: 	 	lstNext

 Description: Moves current to the next element

 Parameters:	psList - pointer to the list

 Returned:	 	None
 *************************************************************************/
extern void lstNext (ListPtr psList){
	if(psList == NULL){
		processError("lstNext", ERROR_INVALID_LIST);
	}
	if(lstIsEmpty(psList)){
		processError("lstNext", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psCurrent->psNext;
	return;
}

/**************************************************************************
 Function: 	 	lstLast

 Description: Moves current to the last element

 Parameters:	psList - pointer to the list

 Returned:	 	None
 *************************************************************************/
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

/**************************************************************************
 Function: 	 	lstInsertAfter

 Description: Creates new list element with data from pBuffer

 Parameters:	psList 	- pointer to the list
 	 	 	 	 	 	 	pBuffer - pointer to buffer to put data
 	 	 	 	 	 	 	size 		- size of datatype

 Returned:	 	none
 *************************************************************************/
extern void lstInsertAfter (ListPtr psList, const void *pBuffer, int size){
	if(psList == NULL){
		processError("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if(pBuffer == NULL){
		processError("lstInsertAfter", ERROR_NULL_PTR);
	}
	bool isLast = psList->psCurrent == psList->psLast;
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
		ListElementPtr psNew = makeNewFilled(psList->psCurrent->psNext, pBuffer,
				size);
		psList->psCurrent->psNext = psNew;
		psList->psCurrent = psList->psCurrent->psNext;
		psList->numElements++;
	}

	//Check if Last
	if(isLast){
		psList->psLast = psList->psCurrent;
	}
	return;
}

/**************************************************************************
 Function: 	 	lstDeleteCurrent

 Description: Deletes current and copies data into pBuffer

 Parameters:	psList 	- pointer to the list
 	 	 	 	 	 	 	pBuffer - pointer to buffer to put data
 	 	 	 	 	 	 	size 		- size of datatype

 Returned:	 	pBuffer
 *************************************************************************/
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

/**************************************************************************
 Function: 	 	lstInsertBefore

 Description: Creates new list element with data from pBuffer before current

 Parameters:	psList 	- pointer to the list
 	 	 	 	 	 	 	pBuffer - pointer to buffer to put data
 	 	 	 	 	 	 	size 		- size of datatype

 Returned:	 	none
 *************************************************************************/
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
		ListElementPtr psNew = makeNewFilled(psList->psCurrent->psNext, pBuffer,
				size);
		psList->psCurrent->psNext = psNew;
		psList->numElements++;
	}
}

/**************************************************************************
 Function: 	 	lstUpdateCurrent

 Description: Updates current list element with data from pBuffer

 Parameters:	psList 	- pointer to the list
 	 	 	 	 	 	 	pBuffer - pointer to buffer to put data
 	 	 	 	 	 	 	size 		- size of datatype

 Returned:	 	none
 *************************************************************************/
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

//*************************************************************************
//								Static functions for misc. utilities
//*************************************************************************

/**************************************************************************
 Function: 	 	makeNewEmpty

 Description: Sets up new element for use in inserting stuff

 Parameters:	psOldNext - previous next (becomes next of new element)

 Returned:	 	pointer to new element
 *************************************************************************/
static ListElementPtr makeNewEmpty(ListElementPtr psOldNext){
	ListElementPtr psNew = (ListElementPtr)malloc(sizeof(ListElement));
	psNew->psNext = psOldNext;
	psNew->pData = NULL;

	return psNew;
}

/**************************************************************************
 Function: 	 	makeNewFilled

 Description: Sets up new element for use in inserting stuff with data

 Parameters:	psOldNext - previous next (becomes next of new element)
 	 	 	 	 	 	  pBuffer 	- data to put in element
 	 	 	 	 	 	  size 			- size of data

 Returned:	 	pointer to new element
 *************************************************************************/
static ListElementPtr makeNewFilled(ListElementPtr psOldNext,
		const void *pBuffer, int size){
	ListElementPtr psNew = makeNewEmpty(psOldNext);
	assign(psNew, pBuffer, size);

	return psNew;
}

/**************************************************************************
 Function: 	 	findPrev

 Description: Finds pointer to the previous list element

 Parameters:	psList - pointer to the list

 Returned:	 	previous list element
 *************************************************************************/
static ListElementPtr findPrev(ListPtr psList){
	ListElementPtr psIterator = psList->psFirst;

	while(psIterator->psNext != psList->psCurrent){
		psIterator = psIterator->psNext;
	}

	return psIterator;
}

/**************************************************************************
 Function: 	 	assign

 Description: assign's data in an element

 Parameters:	psElement - pointer to the element to assign
 	 	 	 	 	 	 	pBuffer 	- pointer to buffer to put data
 	 	 	 	 	 	 	size 			- size of datatype

 Returned:	 	none
 *************************************************************************/
static void assign(ListElementPtr psElement, const void *pUpdate, int size){
	free(psElement->pData);
	psElement->pData = malloc(size);
	memcpy(psElement->pData, pUpdate, size);
}

/**************************************************************************
 Function: 	 	noSaveDelete

 Description: Deletes current without outputting the data. Used within
 	 	 	 	 	 	 	lstDeleteCurrent and in terminate (when datatype is unknown)

 Parameters:	psList - pointer to the list

 Returned:	 	none
 *************************************************************************/
static void noSaveDelete(ListPtr psList){
	ListElementPtr psTemp = psList->psCurrent->psNext;
	bool isLast = psList->psCurrent == psList->psLast;
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

	//Check if last
	if(isLast){
		psList->psLast = psList->psCurrent;
	}
	return;
}
