/**************************************************************************
 File name:		  htdriver.c
 Author:        Frisk Oster
 Date:					11/16/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       This file tests the ht datatype
 *************************************************************************/

#include "../include/ht.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

bool intValidate(void*);
int intHash(void*);
int intComp(void*, void*);
void intPrint(void*, void*);

/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 *************************************************************************/
static void success(char *pszStr) {
	printf("SUCCESS: %s\n", pszStr);
}

/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 *************************************************************************/
static void failure(char *pszStr) {
	printf("FAILURE: %s\n", pszStr);
}

/**************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 failure

 Parameters:	bExpression - Expression being asserted as true
 	 	 	 	 	 	 	pTrue				- String to print if successful
 	 	 	 	 	 	 	pFalse			- String to print if failure

 Returned:	 	none
 *************************************************************************/
static void assert(bool bExpression, char *pTrue, char *pFalse) {
	if (bExpression) {
		success(pTrue);
	} else {
		failure(pFalse);
	}
}

/*************************************************************************
 Function: 	 	main

 Description: main function for htdriver. tests hashtable ADT

 Parameters:	None

 Returned:	 	Exit status
 ************************************************************************/
int main(){
	const int SIZE = 11;
	const int LOOP_LENGTH = 20;
	HashTable HT;

	int i = 0;
	int updateTestKey = 2;
	int updateTestData = 0;
	int getTestKey = 5;
	int getTestData = -10;
	bool bSuccess = true;

	htLoadErrorMessages();

	htCreate(&HT, SIZE, sizeof(int), sizeof(int), intValidate, intHash, intComp,
			intPrint);
	assert(htIsEmpty(&HT), "ht created as expected", "ht create weird");
	//These are just for me because I know how to interpret them.
	//htPrint(&HT);
	for(i = 0; bSuccess && i < LOOP_LENGTH; i++){
		bSuccess = htInsert(&HT, &i, &i);
	}
	assert(bSuccess, "Everything appears to have inserted correctly",
			"insert for loop exited early");
	assert(!htIsEmpty(&HT), "ht has items", "ht didn't insert");
	//htPrint(&HT);
	assert((*(int*)((htElement*)(HT.hashTable[0].psFirst->pData))->data) == 0,
			"First is correct.", "Unexpected behavior from first");
	assert((*(int*)((htElement*)(HT.hashTable[0].psLast->pData))->data) ==
			LOOP_LENGTH - 1, "Last is correct.", "Unexpected behavior from last");
	//htPrint(&HT);
	i = 0;
	htDelete(&HT, &i);
	assert((*(int*)((htElement*)(HT.hashTable[0].psFirst->pData))->data) == 1,
				"Delete successful.", "Unexpected behavior from delete");
	htUpdate(&HT, &updateTestKey, &updateTestData);
	assert((*(int*)((htElement*)(HT.hashTable[0].psFirst->psNext->pData))->key)
			== updateTestKey, "looking at correct key.", "wrong element");
	assert((*(int*)((htElement*)(HT.hashTable[0].psFirst->psNext->pData))->data)
			== updateTestData, "Update successful", "Update error");
	//htPrint(&HT);
	assert(htGet(&HT, &getTestKey, &getTestData), "Get returns success",
			"Get failed.");
	assert(getTestData == 5, "Get got expected result", "Get weird");
	htTerminate(&HT);

	return EXIT_SUCCESS;
}

bool intValidate(void* pKey){
	return pKey != NULL;
}

int intHash(void* pKey){
	const uint64_t MASK = 0x0000000FF0000000;
	uint64_t keySquare = (*((int*)pKey))*(*((int*)pKey));
	uint64_t hash = MASK & keySquare;
	hash = hash>>14;
	return hash;
}

int intComp(void* pKey1, void* pKey2){
	int comp = (*((int*)pKey1)) - (*((int*)pKey2));
	if(comp < 0){
		return -1;
	}
	else if(comp > 0){
		return 1;
	}
	else{
		return 0;
	}
}
void intPrint(void* pKey, void* pData){
	printf("%d %d, ", *(int*)pKey, *(int*)pData);
	return;
}
