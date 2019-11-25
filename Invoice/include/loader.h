/**************************************************************************
 File name:		  loader.h
 Author:        Frisk Oster
 Date:					11/23/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       Provides the functions to load hashtables for invoice
 *************************************************************************/

#ifndef LOADER_H
#define LOADER_H

#define MAX_ITEM_CHARS 20

#include "../../HashTable/include/ht.h"
#include "../../GenericDynamicList/include/list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Item{
		char szName[MAX_ITEM_CHARS];
		char szManufacturer[MAX_ITEM_CHARS];
}Item;

extern bool loadConversion(char* szConversionsFileName,
		HashTablePtr psConversions);
extern bool loadItems(char* szItemsFileName, HashTablePtr psItems);
extern void getItemName(Item *psItem, char* szName);
extern void getItemManufacturer(Item *psItem, char* szMan);

#endif
