all: main.cpp distance.o
	g++ main.cpp distance.cpp -o hw3.out
distance.o: distance.cpp distance.h
	g++ -c distance.cpp
clean:
	rm hw3.out
	rm *.o
	rm *.gch