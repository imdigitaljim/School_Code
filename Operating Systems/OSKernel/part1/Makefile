CC=gcc

.PHONY : compile clean run
compile : part1

part1 :
	$(CC) -o part1.x part1.c

strace : part1
	strace -o log ./part1.x

clean :
	rm *.x log
