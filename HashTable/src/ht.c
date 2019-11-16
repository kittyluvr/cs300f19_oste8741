/**************************************************************************
 File name:		  ht.h
 Author:        Frisk Oster
 Date:					11/16/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       This file defines the hashtable datatype
 *************************************************************************/

#include "../include/ht.h"

char gszHTErrors[NUMBER_OF_HT_ERRORS][MAX_HT_ERROR_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode){
	printf ("Function: %s %s \n ", pszFunctionName,
					 gszHTErrors [errorCode]);
	exit (EXIT_FAILURE);
}

//Create Functions
extern void htCreate(HashTablePtr psHT, int size, keyCheck VALIDATE,
		hashFunc HASH, cmpKeys COMPARE, printFunc PRINT){
	if(psHT == NULL){
		processError("htCreate", NULL_HT_PTR);
	}
	if(VALIDATE == NULL || HASH == NULL || COMPARE == NULL || PRINT == NULL){
		processError("htCreate", HT_INVALID_CREATE_FUNC);
	}
	psHT->hashTable 	= (ListPtr)malloc(sizeof(List)*size);
	psHT->tableSize 	= size;
	psHT->HT_VALIDATE = VALIDATE;
	psHT->HT_HASH			= HASH;
	psHT->HT_COMP		 	= COMPARE;
	psHT->HT_PRINT 		= PRINT;
	return;
}

extern void htTerminate(HashTablePtr psHT){
	if(psHT == NULL){
		processError("htTerminate", NULL_HT_PTR);
	}
	int i = 0;
	for(i = 0; i < psHT->tableSize; i++){
		lstTerminate(psHT->hashTable[i]);
	}
	free(psHT->hashTable);
	return;
}

extern void htLoadErrorMessages(){
	LOAD_HT_ERRORS
	lstLoadErrorMessages();
}

//Hashtable check function
extern bool htIsEmpty(psHT);
extern bool htIsFull(psHT);

//Data Management Functions
extern bool htInsert(HashTablePtr psHT, void* key, void* pData);
extern bool htDelete(HashTablePtr psHT, void* key);
extern bool htUpdate(HashTablePtr psHT, void* key, void* pData);
extern bool htGet(HashTablePtr psHT, void* key, void* pBuffer);

//Print
extern void htPrint(HashTablePtr psHT);
