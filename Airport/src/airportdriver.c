#include "../include/airport.h"
#include <stdio.h>

void runSimulation(AirportPtr psAirport, FILE* inFile);
void printStats(AirportPtr psAirport);

int main(int argc, char* argv[]){
	FILE* inFile = NULL;
	Airport sAirport;

	//Check received enough for a file name.
	if(argc == 2){
		//Try opening file
		inFile = fopen(argv[1], "r");
		if(inFile != NULL){
			runSimulation(&sAirport, inFile);
			printStats(&sAirport);
		}
		else{
			printf("Could not open file");
		}
		fclose(inFile);
	}
	else{
		printf("Unexpected number of arguments");
	}
	return 0;
}
