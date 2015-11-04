all: student.o main.cpp
	g++ main.cpp student.o -o hw6.out
student.o: student.h student.cpp
	g++ -c student.cpp
clean:
	rm hw6.out
	rm *.o
	rm *.gch