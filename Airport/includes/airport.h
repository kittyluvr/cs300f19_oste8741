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

#include "../../GenericDynamicQ/include/queue.h"

enum airportErrors{ NULL_AIRPORT_POINTER, INVALID_DATA };

enum RunwayStatus { U, E, T, L }; //U for unused
typedef enum RunwayStatus RunwayStatus;

//User Defined Types
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
extern void newTurnPrep(AirportPtr pAirport);
extern void enqueueTakeoff(AirportPtr pAirport, const Plane newPlane);
extern void enqueueLanding(AirportPtr pAirport, const Plane newPlane, const int fuel);
extern void decrementFuel(AirportPtr pAirport);
extern void emergencyLandings(AirportPtr pAirport);
extern void useRunways(AirportPtr pAirport);
extern void getTurnInfo(AirportPtr pAirport, RunwayStatus runways[], int *numTakeoff,
		int *numLanding);

#endif
