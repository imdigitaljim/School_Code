CC=cc
CPP=c++
LIBS=
COFLAGS=-g -O2
CWFLAGS=-Wall -Wextra
CIFLAGS=
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)

all: lextest

lextest: lexer.o lextest.o error.o symbol.o init.o
	$(CC) $(CFLAGS) -o lextest lexer.o lextest.o error.o symbol.o init.o
.c.o:
		$(CC) $(CFLAGS) -c $<
clean:
		-rm -f *.o
