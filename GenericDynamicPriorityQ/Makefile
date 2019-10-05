#############################################################################
# File name:  Makefile
# Author:     Frisk oster
# Date:       9.17.19
# Class:      CS 300
# Assignment: GenericDynamicList
# Purpose: 	  This is the Makefile for the GenericDynamicList    
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/pqueuetester

bin:
	mkdir -p bin
	
bin/pqueuetester: bin/pqueuetester.o bin/pqueue.o
	${CC} ${CFLAGS} bin/pqueuetester.o bin/pqueue.o -o bin/listdriver
	
bin/pqueuetester.o: src/pqueuetester.c include/list.h
	${CC} ${CFLAGS} -c src/pqueuetester.c -o pqueuetester.o

bin/pqueue.o: src/pqueue.c include/pqueue.h ../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o

../GenericDynamicList/bin/list.o
	cd ../GenericDynamicList; make bin/list.o

tarball: clean
	tar csf ../cs300_3_Oste8741.tar.gz ../GenericDynamicList ../GenericDynamicPriorityQ

clean:
	rm -rf bin/*.o bin/pqueuetester