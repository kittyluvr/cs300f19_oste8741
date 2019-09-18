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

all: bin bin/listdriver

bin:
	mkdir -p bin
	
bin/listdriver: bin/listdriver.o bin/list.o
	${CC} ${CFLAGS} bin/listdriver.o bin/list.o -o bin/listdriver

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c src/listdriver.c -o bin/listdriver.o

bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o

tarball: clean
	tar czf ../cs300_2_Oste8741.tar.gz ../GenericDynamicList
	
clean:
	rm -rf bin/*.o bin/listdriver