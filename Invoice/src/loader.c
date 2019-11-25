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

static bool conversionValidate(void* key);
static int conversionHash(void* key);
static int conversionCompare(void* key1, void* key2);
static int conversionPrint(void* key, void* data);

static bool itemValidate(void* key);
static int itemHash(void* key);
static int itemCompare(void* key1, void* key2);
static int itemPrint(void* key, void* data);

extern bool loadConversion(char* szConversionsFileName,
		HashTablePtr psConversions){
	const int CONVERSION_TABLE_SIZE = 31;
	const int MAX_CURRENCY_NAME_LENGTH;

	bool bSuccess = true;
	FILE* inFile;
	char szCurrency[MAX_CURRENCY_NAME_LENGTH];

	inFile = fopen(szConversionsFileName, "r");
	if(inFile == NULL){
		bSuccess = false;
	}
	else{
		htCreate(psConversions, CONVERSION_TABLE_SIZE, sizeof(szCurrency),
				sizeof(double), conversionValidate, conversionHash, conversionCompare,
				conversionPrint);
	}
	return bSuccess;
}

extern bool loadItems(char* szItemsFileName, HashTablePtr psItems){
	const int ITEMS_TABLE_SIZE = 256;
	bool bSuccess = true;
	FILE* inFile;

	inFile = fopen(szItemsFileName, "r");
	if(inFile == NULL){
		bSuccess = false;
	}
	else{
		htCreate(psItems, ITEMS_TABLE_SIZE, sizeof(int), sizeof(Item),
				itemValidate, itemHash, itemCompare, itemPrint);
	}
	return bSuccess;
}

extern char* getItemName(Item *psItem){
	return psItem->szName;
}

extern char* getManufacturer(Item *psItem){
	return psItem->szManufacturer;
}

static bool conversionValidate(void* key){
	return true;
}

static int conversionHash(void* key){
	return 0;
}

static int conversionCompare(void* key1, void* key2){
	return 0;
}

static int conversionPrint(void* key, void* data){
	return 0;
}

static bool itemValidate(void* key){
	return true;
}

static int itemHash(void* key){
	return 0;
}

static int itemCompare(void* key1, void* key2){
	return 0;
}

static int itemPrint(void* key, void* data){
	return 0;
}
