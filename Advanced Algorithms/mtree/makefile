CC=g++
FLAGS=-O2 -pedantic -Wall -std=c++11

all: preprocess.x query.x

#preprocess
preprocess: preprocess.x
	preprocess.x
	
preprocess.x: main.o
	$(CC) $(FLAGS) main.o -o preprocess.x 
main.o: main.cpp debugtimer.h mtree.h inversion.h
	$(CC) -c $(FLAGS) main.cpp

#query	
query: query.x
	query.x
	
query.x: query.o
	$(CC) $(FLAGS) query.o -o query.x
	
query.o: query.cpp debugtimer.h mtree.h inversion.h
	$(CC) -c $(FLAGS) query.cpp
	
clean:
	rm *.o preprocess.x query.x *.mtree

