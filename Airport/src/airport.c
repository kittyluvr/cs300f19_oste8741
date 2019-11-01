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

/************************************************************************
 Function: 	 	airportCreate

 Description: create function for airport to make sure everything is set up
 	 	 	 	 	 	 	correctly

 Parameters:	psAirport - pointer to Airport

 Returned:	 	None
 ************************************************************************/
extern void airportCreate(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportCreate", NULL_AIRPORT_PTR);
	}
	//Prep queues
	pqueueCreate(&psAirport->sLandingPlanes);
	queueCreate(&psAirport->sTakeoffPlanes);

	//Clear stats
	psAirport->sStats.takeoffs 					= 0;
	psAirport->sStats.landings 					= 0;
	psAirport->sStats.emergencyLandings = 0;
	psAirport->sStats.crashes 					= 0;
	psAirport->sStats.totalLandingFuel 	= 0;
	psAirport->sStats.totalLandingWait 	= 0;
	psAirport->sStats.totalTakeoffWait	= 0;

	airportNewTurnPrep(psAirport);
	return;
}

/************************************************************************
 Function: 	 	airportTemrinate

 Description: Terminate function for airport to make sure everything is
 	 	 	 	 	 	 	removed correctly

 Parameters:	psAirport - pointer to Airport

 Returned:	 	None
 ************************************************************************/
extern void airportTerminate(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportTerminate", NULL_AIRPORT_PTR);
	}
	pqueueTerminate(&psAirport->sLandingPlanes);
	queueTerminate(&psAirport->sTakeoffPlanes);
	return;
}

/**************************************************************************
 Function: 	 	airportLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_AP_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file. Also calls function to load
 	 	 	 	 	 	  queue errors

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
extern void airportLoadErrorMessages(){
	LOAD_AP_ERRORS
	queueLoadErrorMessages();
}

//Iterative steps

/************************************************************************
 Function: 	 	airportNewTurnPrep

 Description: Preps airport at the start of each turn

 Parameters:	psAirport - pointer to Airport

 Returned:	 	None
 ************************************************************************/
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

/************************************************************************
 Function: 	 	airportEnqueueTakeoff

 Description: Enqueues a plane in the takeoff queue

 Parameters:	psAirport - pointer to Airport
 	 	 	 	 	 	 	newPlane	- plane to enqueue

 Returned:	 	None
 ************************************************************************/
extern void airportEnqueueTakeoff(AirportPtr psAirport, Plane newPlane){
	if(psAirport == NULL){
		processError("airportEnqueueTakeoff", NULL_AIRPORT_PTR);
	}
	queueEnqueue(&psAirport->sTakeoffPlanes, &newPlane, sizeof(Plane));
	return;
}

/************************************************************************
 Function: 	 	airportEnqueueLanding

 Description: Enqueues a plane in the landing queue

 Parameters:	psAirport - pointer to Airport
 	 	 	 	 	 	 	newPlane	- plane to enqueue

 Returned:	 	None
 ************************************************************************/
extern void airportEnqueueLanding(AirportPtr psAirport, Plane newPlane,
		int fuel){
	if(psAirport == NULL){
		processError("airportEnqueueLanding", NULL_AIRPORT_PTR);
	}
	pqueueEnqueue(&psAirport->sLandingPlanes, &newPlane, sizeof(Plane), fuel);
	return;
}

/************************************************************************
 Function: 	 	airportDecrementFuel

 Description: Decrements the fuel of all planes in landing queue

 Parameters:	psAirport - pointer to Airport

 Returned:	 	None
 ************************************************************************/
extern void airportDecrementFuel(AirportPtr psAirport){
	if(psAirport == NULL){
		processError("airportDecrementFuel", NULL_AIRPORT_PTR);
	}

	const int FUEL_DECREMENT = -1;

	pqueueChangePriority(&psAirport->sLandingPlanes, FUEL_DECREMENT);
	return;
}

/************************************************************************
 Function: 	 	airportEmergencyLanding

 Description: Performs emergency landings and crashes

 Parameters:	psAirport - pointer to Airport
 	 	 	 	 	 	 	turnNum 	- current turn (for calculating wait time)

 Returned:	 	None
 ************************************************************************/
extern void airportEmergencyLandings(AirportPtr psAirport, int turnNum,
		int *crashes){
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
				psAirport->sStats.emergencyLandings++;
				psAirport->sStats.landings++;
				psAirport->sStats.totalLandingWait += turnNum - sLandingPlane.startTime;
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

	//Check for crashing planes
	while(!bELandingsDone){
		//Ensure planes still in queue. (If all planes have 0 fuel it's possible
		//for this to be false.)
		if(!pqueueIsEmpty(&psAirport->sLandingPlanes)){
			//Check if remaining planes with no fuel.
			pqueuePeek(&psAirport->sLandingPlanes, &sLandingPlane, sizeof(Plane),
				&fuel);
			//If so, crash
			if(fuel == ELANDING_THRESHOLD){
				pqueueDequeue(&psAirport->sLandingPlanes, &sLandingPlane, sizeof(Plane),
					&fuel);
				psAirport->sStats.crashes++;
				psAirport->sStats.landings++;
				psAirport->sStats.totalLandingWait += turnNum - sLandingPlane.startTime;
				(*crashes)++;
			}
			else{
				bELandingsDone = true;
			}
		}
		else{
			bELandingsDone = true;
		}
	}
	return;
}

/************************************************************************
 Function: 	 	airportEmergencyLanding

 Description: Performs landings and takeoffs on unused runways

 Parameters:	psAirport - pointer to Airport
 	 	 	 	 	 	 	turnNum 	- current turn (for calculating wait time)

 Returned:	 	None
 ************************************************************************/
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
				psAirport->sStats.takeoffs++;
				psAirport->sStats.totalTakeoffWait += turnNum - sPlane.startTime;
			}
			else{
				//Double check landing queue is not empty. (If it is than both queues are empty)
				if(!pqueueIsEmpty(&psAirport->sLandingPlanes)){
					//Land
					psAirport->runways[i] = LANDING;
					pqueueDequeue(&psAirport->sLandingPlanes, &sPlane, sizeof(Plane),
							&fuel);
					psAirport->sStats.landings++;
					psAirport->sStats.totalLandingWait += turnNum - sPlane.startTime;
					psAirport->sStats.totalLandingFuel += fuel;
				}
			}
		}
	}
	return;
}

/************************************************************************
 Function: 	 	airportGetTurnInfo

 Description: Gets info from the current turn so it can be output

 Parameters:	psAirport 	- pointer to Airport
 	 	 	 	 	 	 	runways 		- array of runways to copy runway status to
 	 	 	 	 	 	 	pNumTakeoff - place to put number currently in takeoff
 	 	 	 	 	 	 								queue
 	 	 	 	 	 	 	pNumLanding - place to put number currently in landing
 	 	 	 	 	 	 								queue

 Returned:	 	None
 ************************************************************************/
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

/************************************************************************
 Function: 	 	airportGetFinalStats

 Description: Gets stats struct

 Parameters:	psAirport - pointer to Airport
 	 	 	 	 	 	 	psStats		- stats to copy into

 Returned:	 	None
 ************************************************************************/
extern void airportGetFinalStats(AirportPtr psAirport, Statistics *psStats){
	if(psAirport == NULL){
		processError("airportGetFinalStats", NULL_AIRPORT_PTR);
	}
	if(psStats == NULL){
		processError("airportGetFinalStats", INVALID_DATA_PTR);
	}
	memcpy(psStats, &psAirport->sStats,  sizeof(Statistics));
	return;
}
