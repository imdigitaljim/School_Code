/*
Written for GSEC GOLD certification by Atik Pilihanto | datacomm.co.id
This code is modified from Joonbok Lee presentation on IPv6 Socket Programming
Save as server-demo6.c
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define PORT "55555"
int readbuff(char *str)
{
	char got[200];
	strcpy(got,str); printf("MSG = %s\n",got);
	return 0;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in6 from;
	struct addrinfo req, *ans;
	int code, s, s2, len, retval;
	char buff[1024];
	memset(&req, 0, sizeof(req));
	req.ai_flags = AI_PASSIVE;
	req.ai_family = AF_INET6;
	req.ai_socktype = SOCK_STREAM;
	req.ai_protocol = 0;
	retval = getaddrinfo(NULL,PORT,&req,&ans);
	if(retval!=0)
	{
		printf("ERROR!getaddrinfo\n");
		exit(1);
	}
	s = socket(ans->ai_family, ans->ai_socktype, ans->ai_protocol);
	if(s<0)
	{
		printf("ERROR!socket\n");
		exit(1);
	}
	if (bind(s, ans->ai_addr, ans->ai_addrlen) < 0)
	{
		printf("ERROR!bind\n");
		exit(1);
	}
	listen(s,5);
	while(1)
	{
		s2,len = sizeof(from);
		s2 = accept(s, (struct sockaddr *) &from, &len);
		if(s2<0) continue;
		send(s2,"IPv6 Demo Server v0.01\n\r",32,0);
		recv(s2, buff, sizeof(buff),0);
		readbuff(buff);
		close(s2);
	}
	freeaddrinfo(ans);
	exit(0);
}
