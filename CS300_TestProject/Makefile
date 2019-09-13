#############################################################################
# File name:  Makefile
# Author:     Computer Science, Pacific University
# Date:       9.28.16
# Class:      CS 300
# Assignment: Git Example
# Purpose: 	  Demonstrate Git    
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/driver

bin: 
	mkdir -p bin

bin/driver: bin/driver.o bin/example.o
	${CC} ${CFLAGS} bin/driver.o bin/example.o -o bin/driver

bin/driver.o: src/driver.c include/example.h
	${CC} ${CFLAGS} -c src/driver.c -o bin/driver.o
	 
bin/example.o: src/example.c include/example.h
	${CC} ${CFLAGS} -c src/example.c -o bin/example.o
 	
clean:
	rm bin/*.o bin/driver