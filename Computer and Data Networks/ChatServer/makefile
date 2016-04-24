#Course: CNT5505 - Data Networks and Communications
#Semester: Spring 2016
#Name: James Bach
#
# Compile using on linprog
#


CC=g++
CFLAGS=-pedantic -Wall -std=c++11

all: chatclient chatserver
	
chatserver: chatserver.o socketutil.o
	$(CC) $(CFLAGS) chatserver.o socketutil.o -o chatserver

chatclient: chatclient.o socketutil.o
	$(CC) $(CFLAGS) chatclient.o socketutil.o -o chatclient
	
chatclient.o: chatclient.cpp 
	$(CC) $(CFLAGS) -c chatclient.cpp
	
chatserver.o: chatserver.cpp
	$(CC) $(CFLAGS) -c chatserver.cpp

socketutil.o: socketutil.cpp socketutil.h
	$(CC) $(CFLAGS) -c socketutil.cpp
	
clean:
	rm *.o chatserver chatclient
