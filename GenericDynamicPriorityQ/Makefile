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

all: bin bin/pqueuedriver

bin:
	mkdir -p bin
	
bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o ../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/pqueuedriver.o bin/pqueue.o ../GenericDynamicList/bin/list.o -o bin/pqueuedriver
	
bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h ../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/pqueuedriver.c -o bin/pqueuedriver.o

bin/pqueue.o: src/pqueue.c include/pqueue.h ../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o

../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/pqueuedriver

tarball: clean
	tar czf ../cs300_3_Oste8741.tar.gz ../GenericDynamicList \
	../GenericDynamicPriority

clean:
	rm -rf bin/*.o bin/pqueuedriver
	cd ../GenericDynamicList; make clean