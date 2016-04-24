/*
Course: CNT5505 - Data Networks and Communications
Semester: Spring 2016
Name: James Bach
*/
#ifndef _SOCK_UTIL_H
#define _SOCK_UTIL_H
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <sstream>
#include <limits.h>
#include <list>

#define KEYBOARD 0
#define FAILURE -1
#define BACKLOG 5
#define MSGMAX sizeof(unsigned long int)
#define sockaddr_in struct sockaddr_in
#define addrinfo struct addrinfo
#define sockaddr struct sockaddr
#define in_addr struct in_addr

using namespace std;

class Connection
{
	protected:
		int initReadSet(fd_set& rs, int ms, list<int> *cL = nullptr);
		addrinfo getHints(int flags);
		string ultostr(unsigned long int);
		sockaddr_in getSockAddrInfo(int port);
		void getMessageBuffer(int sock, int bytes);
		
		int main_socket;
		fd_set readset;
		char buffer[MSGMAX + 1], *msg;				
};

class Client : public Connection
{
	
	public:
		Client(const char* host, const char *port);
		~Client();
		
		void ioListen();
		
	private:
		string server_ip;
};


class Server : public Connection
{
	
	public:	
		Server();
		~Server();
		
		void ioListen();
		
	private:
		void checkExitServer();
		void checkNewConnections();
		void checkNewMessages();
		bool msgIsValid();
		
		list<int> conn_list;
		int open_port;
};
#endif