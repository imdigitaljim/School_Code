CC=cc
CPP=c++
LIBS=
COFLAGS=-g -O2
CWFLAGS=-Wall -Wextra
CIFLAGS=
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)
all: calcclass Calc compile

compile:  lexer.o compile.o error.o symbol.o init.o javaclass.h bytecode.h javaclass.o bytecode.o
	$(CC) $(CFLAGS) -o compile compile.o lexer.o error.o symbol.o init.o javaclass.o bytecode.o

calcclass:	javaclass.h bytecode.h calcclass.c javaclass.o bytecode.o
		$(CC) $(CFLAGS) -o calcclass calcclass.c javaclass.o bytecode.o
		
Calc:		calcclass
		./calcclass
.c.o:
		$(CC) $(CFLAGS) -c $<

.PHONY: 	clean distclean
clean:
		-rm -f *.o
distclean:
		-rm -f calcclass *.o *.class compile lextest 
