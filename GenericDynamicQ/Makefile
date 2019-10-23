#############################################################################
# File name:  Makefile
# Author:     Frisk oster
# Date:       9.17.19
# Class:      CS 300
# Assignment: GenericDynamicQueue
# Purpose: 	  This is the Makefile for the GenericDynamicQueue  
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/queuedriver

bin:
	mkdir -p bin
	
bin/queuedriver: bin/queuedriver.o bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o ../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/queuedriver.o bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o ../GenericDynamicList/bin/list.o \
	 -o bin/queuedriver
	
bin/queuedriver.o: src/queuedriver.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c src/queuedriver.c -o bin/queuedriver.o

bin/queue.o: src/queue.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c src/queue.c -o bin/queue.o

../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o

../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/queuedriver

tarball: clean
	tar czf ../cs300_3_Oste8741.tar.gz ../GenericDynamicList \
../GenericDynamicPriorityQ ../GenericDynamicQ

clean:
	rm -rf bin/*.o bin/queuedriver
	cd ../GenericDynamicPriorityQ; make clean