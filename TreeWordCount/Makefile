#############################################################################
# File name:  Makefile
# Author:     Frisk oster
# Date:       11.4.19
# Class:      CS 300
# Assignment: TreeWordCount
# Purpose: 	  This is the Makefile for the TreewordCount    
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/treedriver bin/wordCountDriver

bin/treedriver: bin/treedriver.o bin/tree.o
	${CC} ${CFLAGS} bin/treedriver.o bin/tree.o -o bin/treedriver

bin/treedriver.o: src/treedriver.c include/tree.h
	${CC} ${CFLAGS} -c src/treedriver.c -o bin/treedriver.o

bin/wordCountDriver: bin/wordCountDriver.o bin/tree.o
	${CC} ${CFLAGS} bin/wordCountDriver.o bin/tree.o -o bin/wordCountDriver

bin/wordCountDriver.o: src/wordCountDriver.c include/tree.h
	${CC} ${CFLAGS} -c src/wordCountDriver.c -o bin/wordCountDriver.o

bin/tree.o: src/tree.c include/tree.h
	${CC} ${CFLAGS} -c src/tree.c -o bin/tree.o
	
valgrind: bin/wordCountDriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/wordCountDriver

tarball: clean
	tar czf ../cs300_5_Oster8741.tar.gz ../TreeWordCount

clean:
	rm -rf bin/*.o bin/treedriver bin/wordCountDriver