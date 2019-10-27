#############################################################################
# File name:  Makefile
# Author:     Frisk oster
# Date:       10.21.19
# Class:      CS 300
# Assignment: Airport
# Purpose: 	  This is the Makefile for Airport
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/airportdriver bin/airporttestdriver

bin:
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o \
../GenericDynamicQ/bin/queue.o ../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/airportdriver.o bin/airport.o \
	../GenericDynamicQ/bin/queue.o ../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -o bin/airportdriver

bin/airporttestdriver: bin/airporttestdriver.o bin/airport.o \
../GenericDynamicQ/bin/queue.o ../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/airporttestdriver.o bin/airport.o \
	../GenericDynamicQ/bin/queue.o ../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -o bin/airporttestdriver

bin/airportdriver.o: src/airportdriver.c include/airport.h \
../GenericDynamicQ/include/queue.h ../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c src/airportdriver.c -o bin/airportdriver.o

bin/airporttestdriver.o: src/airporttestdriver.c include/airport.h \
../GenericDynamicQ/include/queue.h ../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c src/airporttestdriver.c -o bin/airporttestdriver.o

bin/airport.o: src/airport.c include/airport.h \
../GenericDynamicQ/include/queue.h ../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c src/airport.c -o bin/airport.o

../GenericDynamicQ/bin/queue.o:
	cd ../GenericDynamicQ; make bin/queue.o

../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPrioirtyQ; make bin/pqueue.o

../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list

testvalgrind: bin/airporttestdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/airporttestdriver

valgrind: bin/airportdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/airportdriver data/airport.txt

tarball: clean
	tar czf ../cs300_3_Oste8741.tar.gz ../GenericDynamicList \
../GenericDynamicPriorityQ ../GenericDynamicQ ../Airport

clean:
	rm -rf bin/*.o bin/airportdriver bin/airporttestdriver
	cd ../GenericDynamicQ; make clean