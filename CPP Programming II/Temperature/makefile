all:main.cpp temperature.o
	g++ main.cpp temperature.o -o hw2.out
temperature.o: temperature.h temperature.cpp
	g++ -c temperature.cpp
clean:
	rm hw2.out
	rm *.o
	rm *.gch