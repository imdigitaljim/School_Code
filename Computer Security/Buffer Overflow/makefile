all: vuln exploit shellcode
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
vuln: stack.c
	gcc -o vuln stack.c -fno-stack-protector -z execstack

exploit: exploit.c
	gcc -o exploit exploit.c
	
shellcode: call_shellcode.c
	gcc -o shellcode call_shellcode.c -fno-stack-protector -z execstack
clean:
	rm vuln exploit shellcode badfile *.o
