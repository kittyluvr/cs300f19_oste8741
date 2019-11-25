/**************************************************************************
 File name:		  invoice.c
 Author:        Frisk Oster
 Date:					11/23/19
 Class:         CS300
 Assignment:    HashTable
 Purpose:       includes main function for invoice program
 *************************************************************************/

#include "../include/loader.h"
#include "../../HashTable/include/ht.h"

int main(){
	char szConversionsFile[25] = "data/conversions.txt";
	char szItemsFile[25] = "data/items.txt";

	HashTable sConversions;
	HashTable sItems;

	//ht create is called in both of these.
	if(!loadConversion(szConversionsFile, &sConversions)){
		printf("Could not load conversions file.");
		return EXIT_FAILURE;
	}
	else if(!loadItems(szItemsFile, &sItems)){
		printf("Could not load items file.");
		return EXIT_FAILURE;
	}
	else{
		htPrint(&sConversions);
		htPrint(&sItems);
	}
	return EXIT_SUCCESS;
}
