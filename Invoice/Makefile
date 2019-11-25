#############################################################################
# File name:  Makefile
# Author:     Frisk oster
# Date:       11.23.19
# Class:      CS 300
# Assignment: HashTable
# Purpose: 	  This is the Makefile for the Invoice program  
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin/invoice

bin/invoice: bin/invoice.o bin/loader.o ../HashTable/bin/ht.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/invoice.o bin/loader.o ../HashTable/bin/ht.o \
	../GenericDynamicList/bin/list.o -o bin/invoice
	
bin/invoice.o: src/invoice.c include/loader.h ../HashTable/include/ht.h
	${CC} ${CFLAGS} -c src/invoice.c -o bin/invoice.o
	
bin/loader.o: src/loader.c include/loader.h ../HashTable/include/ht.h
	${CC} ${CFLAGS} -c src/loader.c -o bin/loader.o

../HashTable/bin/ht.o:
	cd ../HashTable; make bin/ht.o

../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
	
valgrind: bin/invoice
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/invoice
	
tarball: clean
	tar czf ../cs300_6_Oste8741.tar.gz ../GenericDynamicList ../HashTable \
	../Invoice
	
clean:
	rm -rf bin/*.o bin/invoice
	cd ../HashTable; make clean