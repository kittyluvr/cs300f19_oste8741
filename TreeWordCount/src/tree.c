/**************************************************************************
 File name:		  tree.c
 Author:        Frisk Oster
 Date:          11/04/19
 Class:         CS300
 Assignment:    treeWordCount
 Purpose:       This file implements the BST data structure.
 *************************************************************************/

#include "../include/tree.h"

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

extern void trCreate (TreeNodePtr *hsTree){
	if(hsTree == NULL){
		processError("trCreate", TR_NO_CREATE_ERROR);
	}
	if(*hsTree !=){
		(*hsTree)->psLeft  = NULL;
		(*hsTree)->psRight = NULL;
	}
	return;
}
// results: If the tree can be created, then the tree exists and is empty;
//					otherwise, TR_NO_CREATE_ERROR if psTree is NULL

extern void trTerminate (TreeNodePtr *hsTree){
	//if NULL then done
	if(hsTree != NULL){
		//Clear children
		trTerminate(&((*hsTree)->psLeft));
		trTerminate(&((*hsTree)->psLeft));
		//Clear self (since now won't leak children)
		free(*hsTree);
	}
	return;
}
// results: If the tree can be terminated, then the tree no longer exists
//				  and is empty; otherwise, TR_NO_TERMINATE_ERROR

extern bool trIsEmpty (const TreeNodePtr psTree){
	return psTree == NULL;
}
// results: If tree is empty, return true; otherwise, return false
// 					error code priority: TR_NO_MEMORY_ERROR


extern bool trInsert (TreeNodePtr *hsTree, const char* key, int value){
	if(hsTree == NULL){
		processError("trInsert", TR_NO_MEMORY_ERROR);
	}

	int cmpResult;

	//check if first element
	if(*hsTree == NULL){
		*hsTree = (TreeNodePtr)malloc(sizeof(TreeNode));
		trCreate(hsTree);
		(*hsTree)->count = value;
		(*hsTree)->szWord = key;
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

extern bool trUpdate (TreeNodePtr psTree, const char* key, int value){

}
// results: if the tree is valid, and the key does exist in the
//					tree, update the node with the new value passed in and return
//					true.  If the key does not exist in the tree, return false
//					and do not alter the tree.
//					error code priority: TR_NO_MEMORY_ERROR

extern bool trFind (const TreeNodePtr psTree, const char* key, int *pValue);
// results: if the tree is valid, and the key does exist in the
//					tree, return the value through pValue and return true.
//					The user must supply valid memory for pValue.
//					This function does not call malloc.
//				 	If the key does not exist in the tree, return false;
//					error code priority: TR_NO_MEMORY_ERROR, TR_NO_BUFFER_ERROR

extern void trPrintInOrder(const TreeNodePtr psTree);
// results: if the tree is valid, print the key and value for each node
//					in key order (ascending).
//					error code priority: TR_NO_MEMORY_ERROR
