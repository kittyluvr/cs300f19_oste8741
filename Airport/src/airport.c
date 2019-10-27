/**************************************************************************
 File name:		  airport.c
 Author:        Frisk Oster
 Date:          10/21/19
 Class:         CS300
 Assignment:    Airport
 Purpose:       This file implements the airport data structure.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../GenericDynamicPriorityQ/include/pqueue.h"
#include "../../GenericDynamicQ/include/queue.h"
#include "../include/airport.h"

char gszAPErrors[NUMBER_OF_AP_ERRORS][MAX_ERROR_AP_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode){
	printf("Function: %s %s \n ", pszFunctionName,
					 gszAPErrors[errorCode]);
	exit (EXIT_FAILURE);
}

//Create Functions
extern void airportCreate(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportCreate", NULL_AIRPORT_PTR);
	}
	pqueueCreate(&psAirport->sLandingPlanes);
	queueCreate(&psAirport->sTakeoffPlanes);
	newTurnPrep(&psAirport);
	return;
}
extern void airportTerminate(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportTerminate", NULL_AIRPORT_PTR);
	}
	pqueueTerminate(&psAirport->sLandingPlanes);
	queueTerminate(&psAirport->sTakeoffPlanes);
	return;
}
extern void airportLoadErrorMessages(){
	LOAD_AP_ERRORS
	queueLoadErrorMessages();
}

//Iterative steps
extern void airportNewTurnPrep(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportNewTurnPrep", NULL_AIRPORT_PTR);
	}
	int i = 0;
	for(i = 0; i < 3; i++){
		psAirport->runways[i] = UNUSED;
	}
	return;
}
extern void airportEnqueueTakeoff(AirportPtr psAirport, Plane newPlane){
	if(psAirport == NULL){
		processError("airportEnqueueTakeoff", NULL_AIRPORT_PTR);
	}
	queueEnqueue(&psAirport->sTakeoffPlanes, &newPlane, sizeof(Plane));
	return;
}
extern void airportEnqueueLanding(AirportPtr psAirport, Plane newPlane, int fuel){
	if(psAirport == NULL){
		processError("airportEnqueueLanding", NULL_AIRPORT_PTR);
	}
	pqueueEnqueue(&psAirport->sLandingPlanes, &newPlane, sizeof(Plane), fuel);
	return;
}
extern void airportDecrementFuel(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportDecrementFuel", NULL_AIRPORT_PTR);
	}

	const int FUEL_DECREMENT = -1;

	pqueueChangePriority(&psAirport->sLandingPlanes, FUEL_DECREMENT);
	return;
}

extern void airportEmergencyLandings(AirportPtr psAirport, int turnNum){
	if(psAirport == NULL){
		processError("airportEmergencyLandings", NULL_AIRPORT_PTR);
	}

	const int ELANDING_THRESHOLD = 0;

	bool bELandingsDone = false;
	int fuel;
	Plane sLandingPlane;

	for(int i = 0; i < NUM_RUNWAYS && !bELandingsDone; i++){
		//Check there are planes waiting to land
		if(!pqueueIsEmpty(&psAirport->sLandingPlanes)){
			//If there are check, the lowest fuel to see if it needs to land
			pqueuePeek(&psAirport->sLandingPlanes, &sLandingPlane, sizeof(Plane),
					&fuel);
			//If so, land
			if(fuel == ELANDING_THRESHOLD){
				pqueueDequeue(&psAirport->sLandingPlanes, &sLandingPlane, sizeof(Plane),
						&fuel);
				psAirport->runways[i] = EMERGENCY;
				psAirport->sStats->emergencyLandings++;
				psAirport->sStats->landings++;
				psAirport->sStats->totalLandingWait += turnNum - sLandingPlane.startTime;
			}
			//Otherwise, exit loop
			else{
				bELandingsDone = true;
			}
		}
		//if there are no planes, exit loop
		else{
			bELandingsDone = true;
		}
	}
	return;
}
extern void airportUseRunways(AirportPtr psAirport, int turnNum){
	if(psAirport == NULL){
		processError("airportUseRunways", NULL_AIRPORT_PTR);
	}

	int i = 0;
	int fuel = 0;
	Plane sPlane;

	for(i = 0; i < NUM_RUNWAYS; i++){
		//Check if runway is available
		if(psAirport->runways[i] == UNUSED){
			//If takeoff queue is larger takeoff, else land
			if(queueSize(&psAirport->sTakeoffPlanes) >
			pqueueSize(&psAirport->sLandingPlanes)){
				//Takeoff
				psAirport->runways[i] = TAKEOFF;
				queueDequeue(&psAirport->sTakeoffPlanes, &sPlane, sizeof(Plane));
				psAirport->sStats->takeoffs++;
				psAirport->sStats->totalTakeoffWait += turnNum - sPlane.startTime;
			}
			else{
				//Double check landing queue is not empty. (If it is than both queues are empty)
				if(!pqueueIsEmpty(&psAirport->sLandingPlanes)){
					//Land
					psAirport->runways[i] = LANDING;
					pqueueDequeue(&psAirport->sLandingPlanes, &sPlane, sizeof(Plane),
							&fuel);
					psAirport->sStats->landings++;
					psAirport->sStats->totalLandingWait += turnNum - sPlane.startTime;
				}
			}
		}
	}
	return;
}
extern void airportGetTurnInfo(AirportPtr psAirport, RunwayStatus runways[],
		int *pNumTakeoff, int *pNumLanding){
	if(psAirport == NULL){
		processError("airportGetTurnInfo", NULL_AIRPORT_PTR);
	}
	if(pNumTakeoff == NULL || pNumLanding == NULL){
		processError("airportGetTurnInfo", INVALID_DATA_PTR);
	}

	int i = 0;

	for(i = 0; i < NUM_RUNWAYS; i++){
		runways[i] = psAirport->runways[i];
	}

	*pNumTakeoff = queueSize(&psAirport->sTakeoffPlanes);
	*pNumLanding = pqueueSize(&psAirport->sLandingPlanes);
	return;
}
