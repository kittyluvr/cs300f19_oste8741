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
	const int MAX_FILENAME_LENGTH = 20;

	char conversionsFile[MAX_FILENAME_LENGTH] = "data/conversions.txt";
	char itemsFile[MAX_FILENAME_LENGTH] = "data/items.txt";

	HashTable sConversions;
	HashTable sItems;

	//ht create is called in both of these.
	if(!loadConversion(conversionsFile, sConversions)){
		printf("Could not load conversions file.");
		return EXIT_FAILURE;
	}
	else if(!loadItems(itemsFile, sItems)){
		printf("Could not load items file.");
		return EXIT_FAILURE;
	}
	else{

	}
	return EXIT_SUCCESS;
}
