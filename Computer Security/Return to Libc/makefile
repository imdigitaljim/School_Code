all: retlib exploit shellcheck foobar
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
retlib: retlib.c
	gcc -fno-stack-protector -z noexecstack -o retlib retlib.c

exploit: exploit.c
	gcc -o exploit exploit.c
	
shellcheck: shellcheck.c
	gcc -o shellcheck shellcheck.c

foobarS: foobar.c
	gcc -S foobar.c
	
foobar: foobar.c
	gcc -o foobar foobar.c

clean:
	rm retlib foobar exploit shellcheck badfile *.o
