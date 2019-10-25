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
extern void airportCreate(AirportPtr pAirport){
	pqueueCreate(&pAirport->sLandingPlanes);
	queueCreate(&pAirport->sTakeoffPlanes);
	newTurnPrep(&pAirport);
	return;
}
extern void airportTerminate(AirportPtr pAirport){

}
extern void airportLoadErrorMessages(){
	LOAD_AP_ERRORS
	queueLoadErrorMessages();
}

//Iterative steps
extern void airportNewTurnPrep(AirportPtr pAirport){
	if(pAirport == NULL){
		processError("newTurnPrep");
	}
	int i = 0;
	for(i = 0; i < 3; i++){
		pAirport->runways[i] = UNUSED;
	}
}
extern void airportEnqueueTakeoff(AirportPtr pAirport, Plane newPlane){
	queueEnqueue(&pAirport->sTakeoffPlanes, &newPlane, sizeof(Plane));
	return;
}
extern void airportEnqueueLanding(AirportPtr pAirport, Plane newPlane, int fuel);
extern void airportDecrementFuel(AirportPtr pAirport);
extern void airportEmergencyLandings(AirportPtr pAirport);
extern void airportUseRunways(AirportPtr pAirport);
extern void airportGetTurnInfo(AirportPtr pAirport, RunwayStatus runways[], int *numTakeoff,
		int *numLanding);
