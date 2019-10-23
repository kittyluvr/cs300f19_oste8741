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
	Statistics sStats;
} Airport;

#endif
