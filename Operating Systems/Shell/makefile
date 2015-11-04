CC=gcc
CFLAGS=-I. -ansi -pedantic -Wall

.PHONY : compile clean run
compile : oshell

oshell : main.o shellops.o 
	$(CC) $(CFLAGS) -o oshell main.o shellops.o

main.o : shellops.o
	$(CC) $(CFLAGS) -c main.c 
	
shellops.o :  
	$(CC) $(CFLAGS) -c shellops.c 

run : compile
	oshell
	
clean : 
	rm *.x *.o *.gch
