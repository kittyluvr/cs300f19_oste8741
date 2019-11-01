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

void runSimulation(FILE* inFile){
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
	Airport sAirport;
	airportCreate(&sAirport);

	//print table header
	printf("     |           Planes Added            |      Runways      |");
	printf("   Queue  Lengths\n");
	printf("Time | Takeoff  Landing (Fuel Remaining) |  1   2   3  Crash |");
	printf(" Takeoff  Landing\n");
	printf("---- | -------  ------------------------ | --- --- --- ----- |");
	printf(" -------  -------\n");

	for(turn = 0; !feof(inFile) || numLanding != 0 || numTakeoff != 0; turn++){
		printf("%4d | ", turn);
		airportNewTurnPrep(&sAirport);
		//1. Load from file
		if(!feof(inFile)){
			fscanf(inFile, "%d %d", &newTakeoff, &newLanding);
			sTemp.startTime = turn - 1;
			printf("%7d  %7d |", newTakeoff, newLanding);
			//Enqueue takeoff
			for(i = 0; i < newTakeoff; i++){
				airportEnqueueTakeoff(&sAirport, sTemp);
			}
			//Enqueue landing
			for(i = 0; i < newLanding; i++){
				fscanf(inFile, "%d", &inputFuel);
				printf("%5d", inputFuel);
				airportEnqueueLanding(&sAirport, sTemp, inputFuel);
			}
			//If enqueue < MAX then iterate through remaining 0s in line of file
			for(i = 0; i < NUM_RUNWAYS-newLanding; i++){
				printf("    -");
				fscanf(inFile, "%d", &inputFuel);
			}
		}
		else{
			printf("      0        0 |    -    -    -");
		}
		printf(" | ");
		//Step 2 done above
		//3. decrement fuel
		airportDecrementFuel(&sAirport);
		//4. emergency landings
		numCrashes = 0;
		airportEmergencyLandings(&sAirport, turn, &numCrashes);
		//5. use remaining runways
		airportUseRunways(&sAirport, turn);
		//6. print remaining results
		airportGetTurnInfo(&sAirport, runways, &numTakeoff, &numLanding);
		for(i = 0; i < NUM_RUNWAYS; i++){
			switch(runways[i]){
				case UNUSED:
					printf(" -  ");
					break;
				case EMERGENCY:
					printf(" E  ");
					break;
				case LANDING:
					printf(" L  ");
					break;
				case TAKEOFF:
					printf(" T  ");
			}
		}
		printf("%5d | %7d  %7d\n", numCrashes, numTakeoff, numLanding);
	}
	printf("\n");
	printStats(&sAirport);
}

void printStats(AirportPtr psAirport){
	Statistics sStats;
	double avgTakeoffWait;
	double avgLandingWait;
	double avgFuel;

	airportGetFinalStats(psAirport, &sStats);

	avgTakeoffWait = ((double)(sStats.totalTakeoffWait))/sStats.takeoffs;
	avgLandingWait = ((double)(sStats.totalLandingWait))/sStats.landings;
	avgFuel				 = ((double)(sStats.totalLandingFuel))/sStats.landings;

	printf("Average takeoff waiting time: %.5g\n", avgTakeoffWait);
	printf("Average landing waiting time: %.5g\n", avgLandingWait);
	printf("Average flying time remaining on landing: %.5g\n", avgFuel);
	printf("Number of planes landing with zero fuel: %d\n",
			sStats.emergencyLandings);
	printf("Number of crashes: %d", sStats.crashes);

	return;
}

