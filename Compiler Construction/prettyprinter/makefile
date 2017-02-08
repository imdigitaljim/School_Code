CC=c++
LEX=reflex/src/reflex
LIBS=reflex/lib/libreflex.so
COFLAGS=-O2 -std=c++11
CWFLAGS=-Wall -Wextra
CIFLAGS=-I. -Ireflex/include
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)

pretty: pretty.o
	$(CC) $(CFLAGS) -o pretty $(LIBS) $<
.cpp.o:
	$(CC) $(CFLAGS) -c $<
pretty.cpp: pretty.l
	$(LEX) -+ -o pretty.cpp pretty.l
clean:
	rm pretty.cpp 