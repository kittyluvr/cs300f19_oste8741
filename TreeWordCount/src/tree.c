/**************************************************************************
 File name:		  tree.c
 Author:        Frisk Oster
 Date:          11/04/19
 Class:         CS300
 Assignment:    treeWordCount
 Purpose:       This file implements the BST data structure.
 *************************************************************************/

#include "../include/tree.h"
#include <stdio.h>

char gszTreeErrors[TR_NUMBER_OF_ERRORS][TR_MAX_ERROR_CHARS];

/**************************************************************************
 Function: 	 	trLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
extern void trLoadErrorMessages (){
	LOAD_ERRORS
}

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode){
	printf("Function: %s %s \n ", pszFunctionName,
					 gszTreeErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	trCreate

 Description: Checks that a tree is ready to be used.

 Parameters:	hsTree - pointer to the tree

 Returned:	 	None
 *************************************************************************/
extern void trCreate (TreeNodePtr *hsTree){
	if(hsTree == NULL){
		processError("trCreate", TR_NO_CREATE_ERROR);
	}
	else{
		*hsTree = NULL;
	}
	return;
}
// results: If the tree can be created, then the tree exists and is empty;
//					otherwise, TR_NO_CREATE_ERROR if psTree is NULL

/**************************************************************************
 Function: 	 	trTerminate

 Description: Emptys a tree by recursively calling itself on both subtrees
 	 	 	 	 	 	 	then deleting the root node.

 Parameters:	hsTree - pointer to the tree

 Returned:	 	None
 *************************************************************************/
extern void trTerminate (TreeNodePtr *hsTree){
	if(hsTree == NULL){
		processError("trTerminate", TR_NO_TERMINATE_ERROR);
	}
	//if NULL then done
	if(*hsTree != NULL){
		//Clear children
		trTerminate(&((*hsTree)->psLeft));
		trTerminate(&((*hsTree)->psRight));
		//Clear self (since now won't leak children)
		free(*hsTree);
		*hsTree = NULL;
	}
	return;
}
// results: If the tree can be terminated, then the tree no longer exists
//				  and is empty; otherwise, TR_NO_TERMINATE_ERROR

/**************************************************************************
 Function: 	 	trIsEmpty

 Description: Checks if a tree is empty

 Parameters:	psTree - pointer to the tree

 Returned:	 	Whether or not tree is empty
 *************************************************************************/
extern bool trIsEmpty (const TreeNodePtr psTree){
	return psTree == NULL;
}
// results: If tree is empty, return true; otherwise, return false
// 					error code priority: TR_NO_MEMORY_ERROR

/**************************************************************************
 Function: 	 	trInsert

 Description: Inserts an element into the tree if it's not already there.

 Parameters:	hsTree - pointer to the tree
 	 	 	 	 	 	 	key		 - the key of the element to insert
 	 	 	 	 	 	 	value	 - the data to insert in that element

 Returned:	 	Whether the element could be inserted. (If false element
 	 	 	 	 	 	 	with that key already present.)
 *************************************************************************/
extern bool trInsert (TreeNodePtr *hsTree, const char* key, int value){
	if(hsTree == NULL){
		processError("trInsert", TR_NO_MEMORY_ERROR);
	}
	if(key == NULL){
		processError("trInsert", TR_NO_BUFFER_ERROR);
	}

	int cmpResult;

	//check if first element
	if(*hsTree == NULL){
		*hsTree = (TreeNodePtr)malloc(sizeof(TreeNode));
		(*hsTree)->psLeft  = NULL;
		(*hsTree)->psRight = NULL;
		(*hsTree)->count   = value;
		strncpy((*hsTree)->szWord, key, WORD_MAX);
		return true;
	}
	//Else check if key is equal, greater than, or less than.
	cmpResult = strncmp((*hsTree)->szWord, key, WORD_MAX);
	if(cmpResult == 0){
		return false;
	}
	else if(cmpResult > 0){ //szWord > key, left
		return trInsert(&((*hsTree)->psLeft), key, value);
	}
	else{ // szWord < key, right
		return trInsert(&((*hsTree)->psRight), key, value);
	}
}
// results: if the tree is valid, and the key does not exist in the
//					tree, insert the key/value and return true
//					If the key does exist in the tree return false and
//					do not alter the tree
//					error code priority: TR_NO_MEMORY_ERROR

/**************************************************************************
 Function: 	 	trUpdate

 Description: Updates an element in the tree

 Parameters:	psTree - pointer to the tree
 	 	 	 	 	 	 	key		 - the key of the element to update
 	 	 	 	 	 	 	value	 - the data to put in that element

 Returned:	 	Whether the element could be updated. (If false element
 	 	 	 	 	 	 	not found.)
 *************************************************************************/
extern bool trUpdate (TreeNodePtr psTree, const char* key, int value){
	if(key == NULL){
		processError("trUpdate", TR_NO_BUFFER_ERROR);
	}
	if(psTree == NULL){
		return false;
	}
	int cmpResult = strncmp(psTree->szWord, key, WORD_MAX);
	if(cmpResult == 0){
		psTree->count = value;
		return true;
	}
	else if(cmpResult > 0){
		return trUpdate(psTree->psLeft, key, value);
	}
	else{
		return trUpdate(psTree->psRight, key, value);
	}
}
// results: if the tree is valid, and the key does exist in the
//					tree, update the node with the new value passed in and return
//					true.  If the key does not exist in the tree, return false
//					and do not alter the tree.
//					error code priority: TR_NO_MEMORY_ERROR

/**************************************************************************
 Function: 	 	trFind

 Description: Searches for an element in the tree

 Parameters:	psTree - pointer to the tree
 	 	 	 	 	 	 	key		 - the key of the element to find
 	 	 	 	 	 	 	pValue - the buffer to fill with the data

 Returned:	 	Whether the element could be found.
 *************************************************************************/
extern bool trFind (const TreeNodePtr psTree, const char* key, int *pValue){
	if(pValue == NULL || key == NULL){
		processError("trFind", TR_NO_BUFFER_ERROR);
	}
	if(psTree == NULL){
		return false;
	}
	//Valgrind gives an error here but it's unclear why
	int cmpResult = 0;
	cmpResult = strncmp(psTree->szWord, key, WORD_MAX);
	if(cmpResult == 0){
		*pValue = psTree->count;
		return true;
	}
	else if(cmpResult > 0){
		return trFind(psTree->psLeft, key, pValue);
	}
	else{
		return trFind(psTree->psRight, key, pValue);
	}
}
// results: if the tree is valid, and the key does exist in the
//					tree, return the value through pValue and return true.
//					The user must supply valid memory for pValue.
//					This function does not call malloc.
//				 	If the key does not exist in the tree, return false;
//					error code priority: TR_NO_MEMORY_ERROR, TR_NO_BUFFER_ERROR

/**************************************************************************
 Function: 	 	trPrintInOrder

 Description: Prints the tree to the console in order

 Parameters:	psTree - the tree

 Returned:	 	None
 *************************************************************************/
extern void trPrintInOrder(const TreeNodePtr psTree){
	if(psTree != NULL){
		trPrintInOrder(psTree->psLeft);
		printf("%s %d \n", psTree->szWord, psTree->count);
		trPrintInOrder(psTree->psRight);
	}
	return;
}
// results: if the tree is valid, print the key and value for each node
//					in key order (ascending).
//					error code priority: TR_NO_MEMORY_ERROR
