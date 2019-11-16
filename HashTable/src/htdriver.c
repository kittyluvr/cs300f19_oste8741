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

int main(){
	const int SIZE = 11;
	HashTable HT;

	htLoadErrorMessages();

	htCreate(&HT, SIZE, &intValidate, &intHash, &intComp, &intPrint);
	assert(htIsEmpty(&HT), "ht created as expected", "ht create weird");
	htTerminate(&HT);

	return EXIT_SUCCESS;
}

bool intValidate(void* pKey){
	return pKey != NULL;
}

int intHash(void* pKey){
	const uint32_t MASK = 0x0003C000;
	uint32_t keySquare = (*((int*)pKey))*(*((int*)pKey));
	uint32_t hash = MASK & keySquare;
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
	printf("%d %d, ", (int*)pKey, (int*)pData);
	return;
}
