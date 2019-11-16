/**************************************************************************
 File name:		  ht.h
 Author:        CS, Pacific University
 Date:					10/21/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       This file defines the airport datatype used for handling a
 	 	 	 	 	 	 	 	simulation of airport
 *************************************************************************/

#ifndef HT_H
#define HT_H

#define MAX_HT_AP_CHARS 64

#include "../../GenericDynamicList/include/list.h"
#include <stdlib.h>

enum htErrors{ NULL_HT_PTR = 0, HT_INVALID_KEY, HT_INVALID_DATA_PTR };
#define NUMBER_OF_HT_ERRORS HT_INVALID_DATA_PTR - NULL_HT_PTR + 1

//Error management
#define LOAD_HT_ERRORS strcpy(gszHTErrors[NULL_HT_PTR], "Error: invalid HT");\
	strcpy(gszHTErrors[HT_INVALID_KEY], "Error: received invalid key");\
	strcpy(gszHTErrors[HT_INVALID_DATA_PTR], "Error: received invalid data");

//Function pointers;
typedef bool (*keyCheck)(void*);
//Checks that the key type is consistent with what the user is expecting
typedef int (*hashFunc)(void*);
//Hash function. Turns key into array index
typedef int (*cmpKeys)(void*, void*);
//Used for comparing keys
typedef void (*printFunc)(void*);
//Prints key and data since ht doesn't know their types

//Hashtable struct
typedef struct HashTable *HashTablePtr;
typedef struct HashTable{
		ListPtr hashTable;
		int hashSize;
		keyCheck keyValidation;
		hashFunc hash;
		cmpKeys compare;
		printFunc print;
} HashTable;

typedef struct htElement{
		void* key;
		void* data;
}htElement;

//Create Functions
extern void htCreate(HashTablePtr psHT, int size, hashFunc hash,
		keyCheck validate, cmpKeys compFunc, printFunc print);
extern void htTerminate(HashTablePtr psHT);
extern void htLoadErrorMessages();

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
