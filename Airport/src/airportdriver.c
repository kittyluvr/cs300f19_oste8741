#include "../include/airport.h"
#include <stdio.h>

void runSimulation(FILE* inFile);
void printStats(AirportPtr psAirport);

int main(int argc, char* argv[]){
	FILE* inFile = NULL;

	//Check received enough for a file name.
	if(argc == 2){
		//Try opening file
		inFile = fopen(argv[1], "r");
		if(inFile != NULL){
			runSimulation(inFile);
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

void runSimulation(AirportPtr psAirport, FILE* inFile){
	const int LINE_WIDTH = 80;

	char gszMessage[LINE_WIDTH];
	int newLanding = 0;
	int newTakeoff = 0;
	int numLanding = 0;
	int numTakeoff = 0;
	int inputFuel;
	int i = 0;
	int turn = 0;
	int numCrashes = 0;

	Plane sTemp;
	RunwayStatus runways[NUM_RUNWAYS];

	for(turn = 0; inFile != EOF || numLanding != 0 || numTakeoff != 0; turn++){
		//1. Load from file
		if(inFile != EOF){
			fscanf(inFile, "%d %d", newTakeoff, newLanding);
			sTemp.startTime = turn;
			//Enqueue takeoff
			for(i = 0; i < newTakeoff; i++){
				airportEnqueueTakeoff(psAirport, sTemp);
			}
			//Enqueue landing
			for(i = 0; i < newLanding; i++){
				fscanf(inFile, "%d", inputFuel);
				airportEnqueueLanding(psAirport, sTemp, inputFuel);
			}
			//If enqueue < MAX then iterate through remaining 0s in line of file
			for(i = 0; i < NUM_RUNWAYS-newLanding; i++){
				fscanf(inFile, "%d", inputFuel);
			}
		}
		//Step 2 done above
		//3. decrement fuel
		airportDecrementFuel(psAirport);
		//4. emergency landings
		airportEmergencyLandings(psAirport, turn, &numCrashes);
		//Step 5 done above
		//6. print remaining results
		airportGetTurnInfo(psAirport, runways, &numTakeoff, &numLanding);
	}
	printStats(psAirport);
}
void printStats(AirportPtr psAirport);

