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

#define MAX_FILENAME_LENGTH 25

/*************************************************************************
 Function: 	 	main

 Description: main function for invoice.
 	 	 	 	 	 	 	loads files and makes invoice.txt

 Parameters:	None

 Returned:	 	Exit status
 ************************************************************************/
int main(){
	const int EXPECTED_NUM_ITEMS_RECEIVED = 4;
	const int MAX_CURRENCY_NAME_LENGTH = 3;

	char szActionsFile[MAX_FILENAME_LENGTH] = "data/actions.txt";
	char szOutputFile[MAX_FILENAME_LENGTH] = "data/invoice.txt";
	char szConversionsFile[MAX_FILENAME_LENGTH] = "data/conversions.txt";
	char szItemsFile[MAX_FILENAME_LENGTH] = "data/items.txt";

	FILE* inFile;
	FILE* outFile;

	int idNum;
	int count;
	double cost;
	char szCurrency[MAX_CURRENCY_NAME_LENGTH];

	double conversion;
	Item sItem;
	char szItemName[MAX_ITEM_CHARS];
	char szItemMan[MAX_ITEM_CHARS];

	HashTable sConversions;
	HashTable sItems;

	htLoadErrorMessages();

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
		//Both tables are loaded.
		inFile = fopen(szActionsFile, "r");
		outFile = fopen(szOutputFile, "w");
		if(inFile == NULL){
			printf("Could not open actions file.");
			return EXIT_FAILURE;
		}
		if(outFile == NULL){
			printf("Could not access output file.");
			return EXIT_FAILURE;
		}
		else{
			while(!feof(inFile)){
				if((fscanf(inFile, "%i %i %lf %s\n", &idNum, &count, &cost, szCurrency))
					== EXPECTED_NUM_ITEMS_RECEIVED){
					htGet(&sItems, &idNum, &sItem);
					htGet(&sConversions, szCurrency, &conversion);
					cost = cost*conversion;
					getItemName(&sItem, szItemName);
					getItemManufacturer(&sItem, szItemMan);
					//ID# Name, Manufacturer Quantity Cost_In_USD_For_1_Item
					//Total_Cost_in_USD \n
					fprintf(outFile, "%i %s, %s %i %.2f %.2f\n", idNum, szItemName,
							szItemMan, count, cost, cost*count);
			}
			}
			fclose(inFile);
			fclose(outFile);
		}
	}
	htTerminate(&sItems);
	htTerminate(&sConversions);
	return EXIT_SUCCESS;
}
