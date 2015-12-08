CC=gcc
CFLAGS=-I. -ansi -pedantic -Wall

mutil: fatmount.o
	$(CC) $(CFLAGS) -o mutil fatmount.o

fatmount.o: fatmount.c fatmount.h
	$(CC) $(CFLAGS) -c fatmount.c
	
mem : compile
	valgrind -v --leak-check=full mutil

reset: 
	cp fat32a.img fat32.img
	
clean : 
	rm *.o mutil
