/**************************************************************************
 File name:		  ht.h
 Author:        Frisk Oster
 Date:					11/16/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       This file defines the hashtable datatype
 *************************************************************************/

#include "../include/ht.h"
#include <stdlib.h>
#include <stdio.h>

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

/**************************************************************************
 Function: 	 	htCreate

 Description: Creates hashtable. Initializes all the member data/functions.

 	 	 	 	 	 	 	The parameters to the validate function are:
 	 	 	 	 	 	 		void* - the pointer to the key to validate
 	 	 	 	 	 	 	validate returns true if a valid key

 	 	 	 	 	 	 	The parameters to the hash function are:
 	 	 	 	 	 	 		void* - the pointer to the key to hash
 	 	 	 	 	 	 	hash returns the hashvalue

 	 	 	 	 	 	 	The parameters to the compare function are:
 	 	 	 	 	 	 		void* - the pointer to the first key
 	 	 	 	 	 	 		void* - the pointer to the second key
 	 	 	 	 	 	 	compare returns a negative value if the first is smaller, 0 if
 	 	 	 	 	 	 	they're equal, and a positive value if the first is greater.

 	 	 	 	 	 	 	The parameters to the print function are:
 	 	 	 	 	 	 		void* - the pointer to the key
 	 	 	 	 	 	 		void* - the pointer to the data
 	 	 	 	 	 	 	print returns void

 Parameters:	psHT 		 - hashtable to initialize
 	 	 	 	 	 	 	size 		 - size of HashTable
 	 	 	 	 	 	 	keySize	 - size of keys expected
 	 	 	 	 	 	 	dataSize - size of data expected
 	 	 	 	 	 	 	validate - validate function
 	 	 	 	 	 	 	hash 		 - hash function
 	 	 	 	 	 	 	compare  - comparison function
 	 	 	 	 	 	 	print 	 - print function

 Returned:	 	None
 *************************************************************************/
extern void htCreate(HashTablePtr psHT, int size, int keySize,
		int dataSize, keyCheck validate,
		hashFunc hash, cmpKeys compare, printFunc print){
	if(psHT == NULL){
		processError("htCreate", NULL_HT_PTR);
	}
	if(validate == NULL || hash == NULL || compare == NULL || print == NULL){
		processError("htCreate", HT_INVALID_CREATE_FUNC);
	}
	psHT->hashTable  = (ListPtr)malloc(sizeof(List)*size);
	psHT->tableSize  = size;
	psHT->keySize		 = keySize;
	psHT->dataSize	 = dataSize;
	psHT->htValidate = validate;
	psHT->htHash		 = hash;
	psHT->htComp		 = compare;
	psHT->htPrint		 = print;
	return;
}

extern void htTerminate(HashTablePtr psHT){
	if(psHT == NULL){
		processError("htTerminate", NULL_HT_PTR);
	}
	int i = 0;
	for(i = 0; i < psHT->tableSize; i++){
		lstTerminate(&(psHT->hashTable[i]));
	}
	free(psHT->hashTable);
	return;
}

extern void htLoadErrorMessages(){
	LOAD_HT_ERRORS
	lstLoadErrorMessages();
}

//Hashtable check function
extern bool htIsEmpty(HashTablePtr psHT){
	bool bEmpty = true;
	int i = 0;
	for(i = 0; bEmpty && i < psHT->tableSize; i++){
		bEmpty = lstIsEmpty(&(psHT->hashTable[i]));
	}
	return bEmpty;
}

extern bool htIsFull(HashTablePtr psHT){
	bool bFull = true;
	int i = 0;
	for(i = 0; bFull && i < psHT->tableSize; i++){
		bFull = lstIsEmpty(&(psHT->hashTable[i]));
	}
	return bFull;
}

//Data Management Functions
extern bool htInsert(HashTablePtr psHT, void* key, void* pData){
	if(psHT == NULL){
		processError("htInsert", NULL_HT_PTR);
	}
	if(pData == NULL)
	if(!psHT->htValidate(key)){
		processError("htInsert", HT_INVALID_KEY);
	}

	htElement sNewEntry;
	sNewEntry.key = malloc(psHT->keySize);
	sNewEntry.data = malloc(psHT->dataSize);
	memcpy(sNewEntry.key, key, psHT->keySize);
	memcpy(sNewEntry.data, pData, psHT->dataSize);
	htElement sOldEntry;
	sOldEntry.key = malloc(psHT->keySize);
	sOldEntry.data = malloc(psHT->dataSize);

	int hash = psHT->htHash(key) % psHT->tableSize;
	int comp = 0;
	//Check for collisions
	if(lstIsEmpty(&(psHT->hashTable[hash]))){
		lstInsertAfter(&(psHT->hashTable[hash]), &sNewEntry, sizeof(htElement));
	}
	else{
		//Go to where key would go
		lstFirst(&(psHT->hashTable[hash]));
		lstPeek(&(psHT->hashTable[hash]), &sOldEntry, sizeof(htElement));
		comp = psHT->htComp(key, sOldEntry.key);
		while(comp < 0){
			lstPeekNext(&(psHT->hashTable[hash]), &sOldEntry, sizeof(htElement));
			comp = psHT->htComp(key, sOldEntry.key);
			if(comp < 0){
				lstNext(&(psHT->hashTable[hash]));
			}
		}
		//Check if key already there (i.e. comp is 0) if so can't insert.
		if(comp == 0){
			return false;
		}
		else{
			lstInsertAfter(&(psHT->hashTable[hash]), &sNewEntry, sizeof(htElement));
		}
	}
	return true;
}
extern bool htDelete(HashTablePtr psHT, void* key);
extern bool htUpdate(HashTablePtr psHT, void* key, void* pData);
extern bool htGet(HashTablePtr psHT, void* key, void* pBuffer);

//Print
extern void htPrint(HashTablePtr psHT){
	int i = 0;
	int j = 0;
	htElement sEntry;
	sEntry.key = malloc(psHT->keySize);
	sEntry.data = malloc(psHT->dataSize);
	for(i = 0; i < psHT->tableSize; i++){
		printf("Table entry %d size %d: ", i, lstSize(&(psHT->hashTable[i])));
		if(!lstIsEmpty(&(psHT->hashTable[i]))){
			for(j = 0; j < lstSize(&(psHT->hashTable[i])); j++){
				lstFirst(&(psHT->hashTable[i]));
				lstPeek(&(psHT->hashTable[i]), &sEntry, sizeof(htElement));
				psHT->htPrint(sEntry.key, sEntry.data);
				lstNext(&(psHT->hashTable[i]));
			}
		}
		printf("\n");
	}
	return;
}
