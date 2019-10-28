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

enum airportErrors{ NULL_AIRPORT_PTR= 0, EMPTY_PLANE_QUEUE, INVALID_DATA_PTR };
#define NUMBER_OF_AP_ERRORS INVALID_DATA_PTR - NULL_AIRPORT_PTR + 1

//Errors
#define LOAD_AP_ERRORS strcpy(gszAPErrors[NULL_AIRPORT_PTR], \
"Error: received null Airport pointer"); \
strcpy(gszAPErrors[EMPTY_PLANE_QUEUE], "Error: no planes in the queue");\
strcpy(gszAPErrors[INVALID_DATA_PTR], "Error: Received invalid data ptr");

//User Defined Types
#define NUM_RUNWAYS 3

enum RunwayStatus { UNUSED, EMERGENCY, TAKEOFF, LANDING };
typedef enum RunwayStatus RunwayStatus;

typedef struct Plane{
	int startTime;
} Plane;
//This struct isn't strictly necessary but it's included for both readability
//and potential reusablity.

typedef struct Statistics{
	int takeoffs;
	int landings;
	int emergencyLandings;
	int crashes;
	int totalLandingFuel;
	int totalLandingWait;
	int totalTakeoffWait;
} Statistics;

typedef struct Airport *AirportPtr;
typedef struct Airport{
	Queue sTakeoffPlanes;
	PriorityQueue sLandingPlanes;
	RunwayStatus runways[NUM_RUNWAYS];
	Statistics sStats;
} Airport;

//Create Functions
extern void airportCreate(AirportPtr psAirport);
extern void airportTerminate(AirportPtr psAirport);
extern void airportLoadErrorMessages();

//Iterative steps
extern void airportNewTurnPrep(AirportPtr psAirport);
extern void airportEnqueueTakeoff(AirportPtr psAirport, Plane newPlane);
extern void airportEnqueueLanding(AirportPtr psAirport, Plane newPlane,
		int fuel);
extern void airportDecrementFuel(AirportPtr psAirport);
extern void airportEmergencyLandings(AirportPtr psAirport, int turnNum,
		int *crashes);
extern void airportUseRunways(AirportPtr psAirport, int turnNum);
extern void airportGetTurnInfo(AirportPtr psAirport, RunwayStatus runways[],
		int *numTakeoff, int *numLanding);
extern void airportGetFinalStats(AirportPtr psAirport, Statistics *psStats);

#endif
