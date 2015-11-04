#
# Makefile for SunPass Tracker
# 10/06/13
#

cflags = -I. -Wall -Wextra 
CC     = g++47 -std=c++11

AREA51  = /home/courses/cop3330p/fall13/area51

standard: tester.x tracker.x
assess:   testerStudent.x trackerHybrid1.x trackerHybrid2.x trackerStudent.x testerCorrect.x trackerCorrect.x
all:      standard assess

tester.x: tester.o verbose.o
	$(CC) -otester.x tester.o verbose.o

tracker.x: tracker.o vehicles.o shapes.o
	$(CC) -otracker.x tracker.o vehicles.o shapes.o

tracker.o: shapes.h vehicles.h tracker.cpp
	$(CC) $(cflags) -c tracker.cpp

tester.o: shapes.h vehicles.h tester.cpp
	$(CC) $(cflags) -c tester.cpp

shapes.o: shapes.h shapes.cpp
	$(CC) $(cflags) -c shapes.cpp

vehicles.o: shapes.h vehicles.h vehicles.cpp
	$(CC) $(cflags) -c vehicles.cpp

verbose.o: shapes.h vehicles.h verbose.cpp
	$(CC) $(cflags) -c verbose.cpp

testerStudent.x: tester.o verbose.o
	$(CC) -otesterStudent.x tester.o verbose.o

testerCorrect.x: $(AREA51)/tester_i.x
	cp $(AREA51)/tester_i.x testerCorrect.x
	chmod 700 testerCorrect.x

trackerHybrid1.x: $(AREA51)/tracker_i.o vehicles.o shapes.o
	$(CC) -otrackerHybrid1.x $(AREA51)/tracker_i.o vehicles.o shapes.o

trackerHybrid2.x: tracker.o $(AREA51)/vehicles_i.o $(AREA51)/shapes_i.o
	$(CC) -otrackerHybrid2.x tracker.o $(AREA51)/vehicles_i.o $(AREA51)/shapes_i.o

trackerCorrect.x: $(AREA51)/tracker_i.x
	cp $(AREA51)/tracker_i.x trackerCorrect.x
	chmod 700 trackerCorrect.x

trackerStudent.x: tracker.o vehicles.o shapes.o
	$(CC) -otrackerStudent.x tracker.o vehicles.o shapes.o

# Note that in the hybrid versions, different header files are used. If the
# student vehicles.h and the "correct" vehicles.h do not have the same footprint
# layout, there can be runtime issues because function addresses are calculated
# using one footprint whereas they may be in a different place in the code due
# to using a different class definition. 
#
# Thus the hybrid builds are a good test of the API correctness, but they are
# not so good for runtime. In a normal team environment, the entire team would
# use the same set of header files.
