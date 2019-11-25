/**************************************************************************
 File name:		  loader.h
 Author:        Frisk Oster
 Date:					11/23/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       Provides the functions to load hashtables for invoice
 *************************************************************************/

#ifndef HT_H
#define HT_H

#define MAX_ITEM_CHARS 20

#include "../../HashTable/include/ht.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Item{
		char szName[MAX_ITEM_CHARS];
		char szManufacturer[MAX_ITEM_CHARS];
}Item;

extern bool loadConversion(char* szConversionsFileName, HashTablePtr psConversions);
extern bool loadItems(char* szItemsFileName, HashTablePtr psItems);
extern char* getItemName(Item *psItem);
extern char* getManufacturer(Item *psItem);

#endif
