/**************************************************************************
 File name:  tree.h
 Author:     Computer Science, Pacific University
 Date:			 08.15.19
 Class:			 CS300
 Assignment: Trees
 Purpose:    Interface for a tree
 *************************************************************************/


#ifndef TREE_H_
#define TREE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define TR_MAX_ERROR_CHARS 64
#define TR_MAX_ELEMENTS 100

enum {TR_NO_ERROR = 0,
			TR_NO_CREATE_ERROR,
			TR_NO_TERMINATE_ERROR,
			TR_NO_MEMORY_ERROR,
			TR_NO_BUFFER_ERROR}; // If this error name changes, change stmt below
#define TR_NUMBER_OF_ERRORS TR_NO_BUFFER_ERROR - TR_NO_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_ERRORS strcpy (gszTreeErrors[TR_NO_ERROR], "No Error.");\
strcpy (gszTreeErrors[TR_NO_CREATE_ERROR], "Error: No Tree Create.");\
strcpy (gszTreeErrors[TR_NO_TERMINATE_ERROR], "Error: No Tree Terminate.");\
strcpy (gszTreeErrors[TR_NO_MEMORY_ERROR], "Error: No Tree Memory.");\
strcpy (gszTreeErrors[TR_NO_BUFFER_ERROR], "Error: No Buffer.");


#define WORD_MAX 25

typedef struct TreeNode* TreeNodePtr;

typedef struct TreeNode
{
	// the key
	char szWord[WORD_MAX+1];

	// the data
	int count;

	TreeNodePtr psLeft, psRight;
} TreeNode;

//*************************************************************************
// Function prototypes
//*************************************************************************
extern void trLoadErrorMessages ();
extern void trCreate (TreeNodePtr *hsTree);
// results: If the tree can be created, then the tree exists and is empty;
//					otherwise, TR_NO_CREATE_ERROR if psTree is NULL

extern void trTerminate (TreeNodePtr *hsTree);
// results: If the tree can be terminated, then the tree no longer exists
//				  and is empty; otherwise, TR_NO_TERMINATE_ERROR

extern bool trIsEmpty (const TreeNodePtr psTree);
// results: If tree is empty, return true; otherwise, return false
// 					error code priority: TR_NO_MEMORY_ERROR


extern bool trInsert (TreeNodePtr *hsTree, const char* key, int value);
// results: if the tree is valid, and the key does not exist in the
//					tree, insert the key/value and return true
//					If the key does exist in the tree return false and
//					do not alter the tree
//					error code priority: TR_NO_MEMORY_ERROR

extern bool trUpdate (TreeNodePtr psTree, const char* key, int value);
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

#endif /* TREE_H_ */
