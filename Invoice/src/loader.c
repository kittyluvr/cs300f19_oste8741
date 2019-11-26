/**************************************************************************
 File name:		  loader.c
 Author:        Frisk Oster
 Date:					11/23/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       Defines the functions to load hashtables for invoice
 *************************************************************************/

#include "../include/loader.h"
#include "../../HashTable/include/ht.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool conversionValidate(void* key);
static int conversionHash(void* key);
static int conversionCompare(void* key1, void* key2);
static void conversionPrint(void* key, void* pData);

static bool itemValidate(void* pKey);
static int itemHash(void* pKey);
static int itemCompare(void* pKey1, void* pKey2);
static void itemPrint(void* pKey, void* pData);

/**************************************************************************
 Function: 	 	loadConversion

 Description: Loads conversion hashtable with conversions from file.
 	 	 	 	 	 	 	(Important Note: This function handles ht create and required
 	 	 	 	 	 	 	functions. Passing a hashtable that is already created WILL
 	 	 	 	 	 	 	cause memory errors.)

 Parameters:	szConversionsFileName - The file name to load from
 	 	 	 	 	 	  psConversions					- The hashtable to load into.

 Returned:	 	Whether ht loaded successfully from file.
 *************************************************************************/
extern bool loadConversion(char* szConversionsFileName,
		HashTablePtr psConversions){
	const int CONVERSION_TABLE_SIZE = 31;
	const int MAX_CURRENCY_NAME_LENGTH = 3;
	const int EXPECTED_NUM_ITEMS_RECEIVED = 2;

	bool bSuccess = true;
	FILE* inFile;
	char szCurrency[MAX_CURRENCY_NAME_LENGTH];
	double conversion;

	inFile = fopen(szConversionsFileName, "r");
	if(inFile == NULL){
		bSuccess = false;
	}
	else{
		htCreate(psConversions, CONVERSION_TABLE_SIZE, sizeof(szCurrency),
				sizeof(double), conversionValidate, conversionHash, conversionCompare,
				conversionPrint);
		while(bSuccess && !feof(inFile)){
			if((fscanf(inFile, "%s %lf", szCurrency, &conversion))
					== EXPECTED_NUM_ITEMS_RECEIVED){
				htInsert(psConversions, szCurrency, &conversion);
			}
		}
		fclose(inFile);
	}
	return bSuccess;
}

/**************************************************************************
 Function: 	 	loadItems

 Description: Loads items hashtable with items from file.
 	 	 	 	 	 	 	(Important Note: This function handles ht create and required
 	 	 	 	 	 	 	functions. Passing a hashtable that is already created WILL
 	 	 	 	 	 	 	cause memory errors.)

 Parameters:	szItemsFileName - The file name to load from
 	 	 	 	 	 	  psItems					- The hashtable to load into.

 Returned:	 	Whether ht loaded successfully from file.
 *************************************************************************/
extern bool loadItems(char* szItemsFileName, HashTablePtr psItems){
	const int ITEMS_TABLE_SIZE = 256;
	const int EXPECTED_NUM_ITEMS_RECEIVED = 3;

	bool bSuccess = true;
	FILE* inFile;

	int id;
	Item sItem;

	inFile = fopen(szItemsFileName, "r");
	if(inFile == NULL){
		bSuccess = false;
	}
	else{
		htCreate(psItems, ITEMS_TABLE_SIZE, sizeof(int), sizeof(Item),
				itemValidate, itemHash, itemCompare, itemPrint);
		while(bSuccess && !feof(inFile)){
			memset(sItem.szName, '\0', MAX_ITEM_CHARS);
			memset(sItem.szManufacturer, '\0', MAX_ITEM_CHARS);
			if((fscanf(inFile, "%i %s %s", &id, sItem.szName,
					sItem.szManufacturer)) == EXPECTED_NUM_ITEMS_RECEIVED){
				htInsert(psItems, &id, &sItem);
			}
		}
		fclose(inFile);
	}
	return bSuccess;
}

/**************************************************************************
 Function: 	 	getItemName

 Description: gets the name from an item.

 Parameters:	psItem - the item to get the name from.
 	 	 	 	 	 	 	szName - the string to load the name into

 Returned:	 	None.
 *************************************************************************/
extern void getItemName(Item *psItem, char* szName){
	strncpy(szName, psItem->szName, MAX_ITEM_CHARS);
	return;
}

/**************************************************************************
 Function: 	 	getItemManufacturer

 Description: gets the manufacturer from an item.

 Parameters:	psItem - the item to get the manufacturer from.
 	 	 	 	 	 	 	szMan  - the string to load the manufacturer name into

 Returned:	 	None.
 *************************************************************************/
extern void getItemManufacturer(Item *psItem, char* szMan){
	strncpy(szMan, psItem->szManufacturer, MAX_ITEM_CHARS);
}

/**************************************************************************
 Function: 	 	conversionValidate

 Description: the key validate function for the conversion table.

 Parameters:	key - the key to validate

 Returned:	 	whether it's a valid key.
 *************************************************************************/
static bool conversionValidate(void* key){
	const int CURRENCY_NAME_LENGTH = 3;

	return strlen((char*)key) == CURRENCY_NAME_LENGTH;
}

/**************************************************************************
 Function: 	 	conversionHash

 Description: the key hash function for the conversion table.

 Parameters:	key - the key to hash

 Returned:	 	the hash value
 *************************************************************************/
static int conversionHash(void* key){
	int i = 0;
	int hash = 0;
	for(i = 0; i < strlen((char*)key); i++){
		hash = 31*hash + (int)(*(char*)key);
	}
	return hash;
}

/**************************************************************************
 Function: 	 	conversionCompare

 Description: the key compare function for the conversion table.

 Parameters:	key1 - the first key to compare
 	 	 	 	 	 	 	key2 - the second key to compare

 Returned:	 	< 0 if key1 is smaller,
 	 	 	 	 	 	  0 if they are the same,
 	 	 	 	 	 	 	> 0 if key1 is larger
 *************************************************************************/
static int conversionCompare(void* key1, void* key2){
	const int MAX_CURRENCY_NAME_LENGTH = 3;
	return strncmp((char*)key1, (char*)key2, MAX_CURRENCY_NAME_LENGTH);
}

/**************************************************************************
 Function: 	 	conversionPrint

 Description: the conversion print function for that table.

 Parameters:	pKey  - the key to print
 	 	 	 	 	 	 	pData - the data to print

 Returned:	 	None.
 *************************************************************************/
static void conversionPrint(void* key, void* pData){
	printf("%s %f, ", (char*)key, *(double*)pData);
	return;
}

/**************************************************************************
 Function: 	 	itemValidate

 Description: the key validate function for the item table.

 Parameters:	key - the key to validate

 Returned:	 	whether it's a valid key.
 *************************************************************************/
static bool itemValidate(void* pKey){
	return (int*)pKey != NULL;
}

/**************************************************************************
 Function: 	 	itemHash

 Description: the key hash function for the item table.

 Parameters:	key - the key to hash

 Returned:	 	the hash value
 *************************************************************************/
static int itemHash(void* pKey){
	const uint64_t MASK = 0x0000000FF0000000;
	uint64_t keySquare = (*((int*)pKey))*(*((int*)pKey));
	uint64_t hash = MASK & keySquare;
	hash = hash>>14;
	return hash;
}

/**************************************************************************
 Function: 	 	itemCompare

 Description: the key compare function for the item table.

 Parameters:	pKey1 - the first key to compare
 	 	 	 	 	 	 	pKey2 - the second key to compare

 Returned:	 	< 0 if pKey1 is smaller,
 	 	 	 	 	 	  0 if they are the same,
 	 	 	 	 	 	 	> 0 if pKey1 is larger
 *************************************************************************/
static int itemCompare(void* pKey1, void* pKey2){
	return *(int*)pKey1 - *(int*)pKey2;
}

/**************************************************************************
 Function: 	 	itemPrint

 Description: the item print function for that table.

 Parameters:	pKey  - the key to print
 	 	 	 	 	 	 	pData - the data to print

 Returned:	 	None.
 *************************************************************************/
static void itemPrint(void* pKey, void* pData){
	printf("%i %s %s, ", *(int*)pKey, ((Item*)pData)->szName,
			((Item*)pData)->szManufacturer);
	return;
}
