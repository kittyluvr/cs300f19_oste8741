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
	}
}
// results: If the list can be terminated, then the list no longer exists
//				  and is empty; otherwise, ERROR_NO_LIST_TERMINATE

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
extern int lstSize (const ListPtr psList);
// results: Returns the number of elements in the list
// 					error code priority: ERROR_INVALID_LIST

extern bool lstIsFull (const ListPtr psList);
// results: If list is full, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_LIST

extern bool lstIsEmpty (const ListPtr psList);
// results: If list is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_LIST

//*************************************************************************
//												List Testing
//*************************************************************************
extern bool lstHasCurrent (const ListPtr psList);
// results: Returns true if the current node is not NULL; otherwise, false
//					is returned
// 				  error code priority: ERROR_INVALID_LIST

extern bool lstHasNext (const ListPtr psList);
 // results: Returns true if the current node has a successor; otherwise,
 //					 false is returned
 // 				 error code priority: ERROR_INVALID_LIST

//*************************************************************************
//													Peek Operations
//*************************************************************************
extern void *lstPeek (const ListPtr psList, void *pBuffer, int size);
// requires:  List is not empty
// results:   The value of the current element is returned
// IMPORTANT: Do not change current
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//											           ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void *lstPeekNext (const ListPtr psList, void *pBuffer, int size);
// requires:  List contains two or more elements and current is not last
// results:   The data value of current's successor is returned
// IMPORTANT: Do not change current
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//											           ERROR_EMPTY_LIST, ERROR_NO_CURRENT,
//																 ERROR_NO_NEXT

//*************************************************************************
//							Retrieving values and updating current
//*************************************************************************
extern void *lstFirst (ListPtr psList, void *pBuffer, int size);
// requires:  List is not empty
// results: 	If the list is not empty, the value of the first element is
//						returned and current is changed to the first element
//          	error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//															 	 ERROR_EMPTY_LIST

extern void *lstNext (ListPtr psList, void *pBuffer, int size);
// requires:  List is not empty
// results:   The value of the current element is returned
// IMPORTANT: Current is changed to the successor of the current element
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//																 ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void *lstLast (ListPtr psList, void *pBuffer, int size);
// requires:  List is not empty
// results:   The value of the last element is returned
// IMPORTANT: Current is changed to last if it exists
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//																 ERROR_EMPTY_LIST

//*************************************************************************
//									Insertion, Deletion, and Updating
//*************************************************************************

extern void lstInsertAfter (ListPtr psList, const void *pBuffer, int size);
// requires: List is not full
// results:  If the list is not empty, insert the new element as the
//           successor of the current element and make the inserted element
//           the current element; otherwise, insert element and make it
//					 current.
//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//																ERROR_NO_CURRENT

extern void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size);
// requires: List is not empty
// results: The current element is deleted and its successor and
//				  predecessor become each others successor and predecessor. If
//					the deleted element had a predecessor, then make it the new
// 					current element; otherwise, make the first element current if
// 					it exists. The value of the deleted element is returned.
//          error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//					                     ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void lstInsertBefore (ListPtr psList, const void *pBuffer,
														 int size);
// requires: List is not full
// results:  If the list is not empty, insert the new element as the
//           predecessor of the current element and make the inserted
//           element the current element; otherwise, insert element
//           and make it current.
//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//																ERROR_NO_CURRENT

extern void lstUpdateCurrent (ListPtr psList, const void *pBuffer,
														  int size);
// requires: List is not empty
// results:  The value of pBuffer is copied into the current element
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//					                       ERROR_EMPTY_LIST, ERROR_NO_CURRENT
// IMPORTANT: user could update with smaller, larger, or the same size data
//					  so free data, then reallocate based on size before updating
