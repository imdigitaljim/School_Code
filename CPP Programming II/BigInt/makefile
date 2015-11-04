all: myint.o ec2.cpp
	g++ ec2.cpp myint.cpp -o hw5.out
myint.o: myint.cpp myint.h
	g++ -c myint.cpp
clean:
	rm hw5.out
	rm *.o
	rm *.gch