all: server-demo6 server-fms6

server-fms6: server-fms6.c
	gcc -fno-stack-protector -z execstack -o server-fms6 server-fms6.c

server-demo6: server.c
	gcc -fno-stack-protector -z execstack -o server-demo6 server.c
	
clean:
	rm server-demo6 server-fms6 *.o

