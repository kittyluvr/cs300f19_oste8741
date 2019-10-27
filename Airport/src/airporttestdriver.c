/**************************************************************************
 File name:		  pqueuedriver.c
 Author:        Frisk Oster
 Date:          10/04/19
 Class:         CS300
 Assignment:    Priority Queue Implementation Test
 Purpose:       This file implements the priority queue data structure.
 *************************************************************************/
#include "../include/airport.h"

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success(char *pszStr) {
	printf("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void failure(char *pszStr) {
	printf("FAILURE: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 failure

 Parameters:	bExpression - Expression being asserted as true
 	 	 	 	 	 	 	pTrue				- String to print if successful
 	 	 	 	 	 	 	pFalse			- String to print if failure

 Returned:	 	none
 ****************************************************************************/
static void assert(bool bExpression, char *pTrue, char *pFalse) {
	if (bExpression) {
		success(pTrue);
	} else {
		failure(pFalse);
	}
}

/****************************************************************************
 Function: 	 	main

 Description: main function for pqueuedriver. tests pqueue ADT

 Parameters:

 Returned:	 	none
 ****************************************************************************/
int main(){
	const int TEST_LOOP_SIZE = 1000000;

	Airport sAirport;
	RunwayStatus runways[NUM_RUNWAYS];
	int numTakeoff = 0;
	int numLanding = 0;

	bool bAllExpected = true;
	int i = 0;
	Plane sTempPlane;

	airportCreate(&sAirport);

	//Check blank airport
	airportGetTurnInfo(&sAirport, runways, &numTakeoff, &numLanding);
	for(i = 0; i < NUM_RUNWAYS; i++){
		if(runways[i] != UNUSED){
			bAllExpected = false;
		}
	}
	assert(bAllExpected, "Runways as expected", "Runways used?");
	assert(numTakeoff == 0 && numLanding == 0, "Queues as expected",
	"Queues used?");

	//Enqueue a bunch of landing planes
	for(i = 0; i < TEST_LOOP_SIZE; i++){
		sTempPlane.startTime = i;
		airportEnqueueLanding(&sAirport, sTempPlane, i);
	}
	airportGetTurnInfo(&sAirport, runways, &numTakeoff, &numLanding);
	bAllExpected = true;
	i = 0;
	for(i = 0; i < NUM_RUNWAYS; i++){
		if(runways[i] != UNUSED){
			bAllExpected = false;
		}
	}
	assert(bAllExpected, "Runways as expected", "Runways used?");
	assert(numTakeoff == 0 && numLanding == TEST_LOOP_SIZE, "Queues as expected",
	"Queues weird");

	//Land some planes
	airportUseRunways(&sAirport, TEST_LOOP_SIZE);
	airportGetTurnInfo(&sAirport, runways, &numTakeoff, &numLanding);
	bAllExpected = true;
	i = 0;
	for(i = 0; i < NUM_RUNWAYS; i++){
		if(runways[i] != LANDING){
			bAllExpected = false;
		}
	}
	assert(bAllExpected, "Runways used for landing", "weirdness with runways");
	assert(numTakeoff == 0 && numLanding == TEST_LOOP_SIZE - NUM_RUNWAYS,
			"Queues as expected", "Queues weird");

	//Prep for a new turn
	airportNewTurnPrep(&sAirport);
	bAllExpected = true;
	i = 0;
	for(i = 0; i < NUM_RUNWAYS; i++){
		if(runways[i] != UNUSED){
			bAllExpected = false;
		}
	}
	assert(bAllExpected, "Runways as expected", "Runways used?");
	assert(numTakeoff == 0 && numLanding == TEST_LOOP_SIZE - NUM_RUNWAYS,
		"Queues as expected", "Queues weird");

	//Enqueue a bunch of taking off planes
	for(i = 0; i < TEST_LOOP_SIZE; i++){
		sTempPlane.startTime = i;
		airportEnqueueTakeoff(&sAirport, sTempPlane);
	}

	//Take off some planes
	airportUseRunways(&sAirport, TEST_LOOP_SIZE);
	airportGetTurnInfo(&sAirport, runways, &numTakeoff, &numLanding);
	bAllExpected = true;
	i = 0;
	for(i = 0; i < NUM_RUNWAYS; i++){
		if(runways[i] != TAKEOFF){
			bAllExpected = false;
		}
	}
	assert(bAllExpected, "Runways used for TAKEOFF", "weirdness with runways");
	assert(numTakeoff == TEST_LOOP_SIZE - NUM_RUNWAYS && numLanding == TEST_LOOP_SIZE - NUM_RUNWAYS,
		"Queues as expected", "Queues weird");

	return EXIT_SUCCESS;
}
