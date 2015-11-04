all: menu.cpp song.o playlist.o
	g++ menu.cpp song.cpp playlist.cpp -o hw4.out
song.o: song.cpp song.h
	g++ -c song.cpp 
playlist.o: playlist.cpp playlist.h
	g++ -c playlist.cpp
clean:	
	rm hw4.out	
	rm *.o
	rm *.gch	