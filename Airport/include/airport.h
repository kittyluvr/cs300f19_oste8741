/**************************************************************************
 File name:		  airport.h
 Author:        CS, Pacific University
 Date:					10/21/19
 Class:         CS300
 Assignment:    Airport Simulation
 Purpose:       This file defines the airport datatype used for handling a
 	 	 	 	 	 	 	 	simulation of airport
 *************************************************************************/

#ifndef AIRPORT_H
#define AIRPORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../GenericDynamicQ/include/queue.h"

#define MAX_ERROR_AP_CHARS 64

enum airportErrors{ NULL_AIRPORT_PTR= 0, INVALID_PLANE_DATA };
#define NUMBER_OF_AP_ERRORS INVALID PLANE_DATA - NULL_AIRPORT_PTR + 1

//Errors
#define LOAD_AP_ERRORS strcpy(gszAPErrors[NULL_AIRPORT_PTR], "Error: received null Airport pointer");\
strcpy(gszAPErrors[INVALID_PLANE_DATA], "Error: Received invalid plane");

//User Defined Types
enum RunwayStatus { UNUSED, EMERGENCY, TAKEOFF, LANDING };
typedef enum RunwayStatus RunwayStatus;

typedef struct Plane{
	int startTime;
} Plane;
//This struct isn't strictly necessary but it's included for both readability
//and potential reusablity.

typedef struct Statistics{
	int totalPlanes 			= 0;
	int takeoffs 					= 0;
	int landings 					= 0;
	int emergencyLandings = 0;
	int crashes 					= 0;
	int totalLandingFuel 	= 0;
} Statistics;

typedef struct Airport *AirportPtr;
typedef struct Airport{
	Queue sTakeoffPlanes;
	PriorityQueue sLandingPlanes;
	RunwayStatus runways[3];
	Statistics sStats;
} Airport;

//Create Functions
extern void airportCreate(AirportPtr pAirport);
extern void airportTerminate(AirportPtr pAirport);
extern void airportLoadErrorMessages();

//Iterative steps
extern void airportNewTurnPrep(AirportPtr pAirport);
extern void airportEnqueueTakeoff(AirportPtr pAirport, Plane newPlane);
extern void airportEnqueueLanding(AirportPtr pAirport, Plane newPlane, int fuel);
extern void airportDecrementFuel(AirportPtr pAirport);
extern void airportEmergencyLandings(AirportPtr pAirport);
extern void airportUseRunways(AirportPtr pAirport);
extern void airportGetTurnInfo(AirportPtr pAirport, RunwayStatus runways[], int *numTakeoff,
		int *numLanding);

#endif
