/*
Course: CNT5505 - Data Networks and Communications
Semester: Spring 2016
Name: James Bach
*/


#include "socketutil.h"

string Connection::ultostr(unsigned long int x)
{
	stringstream ss;
	string result;
	ss << setfill('0') << setw(MSGMAX) << to_string(x);
	return ss.str();
}

int Connection::initReadSet(fd_set& rs, int ms, list<int> *cL)
{
	int maxSocket = ms;
	FD_ZERO(&rs);
	FD_SET(ms, &rs);
	FD_SET(KEYBOARD, &rs);
	if (cL != nullptr)
	{
		for (auto it = cL->begin(); it != cL->end(); it++)
		{
			FD_SET(*it, &rs); //set fd_set
			maxSocket = max(maxSocket, *it); //get a max to socket number
		}
	}
	return maxSocket + 1;
}

void Connection::getMessageBuffer(int sock, int bytes)
{
	buffer[MSGMAX] = 0;			
	unsigned long len = strtoul(buffer, NULL, 10);
	msg = new char[len + 1];
	memset(msg, 0, len + 1);
	read(sock, msg, len);
	msg[len] = 0;
}

addrinfo Connection::getHints(int flags)
{
	addrinfo h;
	memset(&h, 0, sizeof(h));
	h.ai_family = AF_UNSPEC;
	h.ai_socktype = SOCK_STREAM;
	h.ai_flags = AI_PASSIVE | flags;
	return h;
}

sockaddr_in Connection::getSockAddrInfo(int port)
{
	sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = port;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	return sa;
}

Server::Server()
{
	int optval = true;
	char hostname[HOST_NAME_MAX];
	sockaddr_in serv_addr = getSockAddrInfo(htons(0));
	addrinfo hints = getHints(AI_CANONNAME | AI_PASSIVE), *serv_info;
	socklen_t salen = sizeof(serv_addr);
	memset(hostname, 0, HOST_NAME_MAX);
	main_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(main_socket, SOL_SOCKET,	SO_REUSEADDR, &optval, sizeof(optval)) == FAILURE)
	{
		cerr << "Socket options failed." << endl;
		exit(1);
	}
	if (bind(main_socket, (sockaddr *) &serv_addr, sizeof(serv_addr)) == FAILURE)
	{
		cerr << "Bind failed." << endl;
		exit(1);
	}
	if (listen(main_socket, BACKLOG) == FAILURE)
	{
		cerr << "Listen failed." << endl;
		exit(1);
	}
	if (gethostname(hostname, HOST_NAME_MAX) == FAILURE)
	{
		cerr << "Failed to get hostname" << endl;
		exit(1);
	}	
	if (getaddrinfo(hostname, NULL, &hints, &serv_info) == FAILURE) {
		cerr << "Failed to get address info" << endl;
		exit(1);
	}
	if (getsockname(main_socket, (sockaddr *)&serv_addr, &salen) == FAILURE)
	{
		cerr << "No socket created!" << endl;
		exit(1);
	}
	open_port = ntohs(serv_addr.sin_port);
	cout << "admin: started server on '" << serv_info->ai_canonname;
	cout << "' at '" << open_port << "'" << endl;
	freeaddrinfo(serv_info);
}

void Server::checkExitServer()
{
	if (FD_ISSET(KEYBOARD, &readset)) //keyboard
	{
		string input;
		getline(cin, input);
		if (input == "exit")
		{
			exit(0);
		}
	}
}

void Server::checkNewConnections()
{
	if (FD_ISSET(main_socket, &readset))
	{
		int options, cd;
		addrinfo hints = getHints(AI_CANONNAME | AI_PASSIVE);
		addrinfo *serv_info;
		sockaddr_in client_addr;
		char ipstr[INET6_ADDRSTRLEN];
		socklen_t calen = sizeof(client_addr);
		if ((cd = accept(main_socket, (sockaddr* ) &client_addr, &calen)) == FAILURE)
		{
			cerr << "Connection failed to connect" << endl;
			exit(1);
		}
		if ((options = fcntl(cd, F_GETFL)) == FAILURE)
		{
			cerr << "Failed to get new socket connection options" << endl;
			exit(1);
		}
		options |= O_NONBLOCK;
		if (fcntl(cd, F_SETFL, options) == FAILURE)
		{
			cerr << "Failed to set new socket connection options" << endl;
			exit(1);
		}
		if (getpeername(cd, (sockaddr *)&client_addr, &calen) == FAILURE)
		{
			cerr << "No socket found!" << endl;
			exit(1);
		}
		inet_ntop(AF_INET, &client_addr.sin_addr, ipstr, sizeof(ipstr));
		if (getaddrinfo(ipstr, NULL, &hints, &serv_info) == FAILURE)
		{
			cerr << "Failed to get address info " << endl;
			exit(1);
		}
		conn_list.push_back(cd);
		cout << "admin: connect from '" + string(serv_info->ai_canonname) + "' at '" + to_string(ntohs(client_addr.sin_port)) + "'" << endl;	
		string admin_msg = "admin: connected to server on '" + string(serv_info->ai_canonname) + "' at '" + to_string(open_port) + "' thru '" + to_string(ntohs(client_addr.sin_port)) + "'";
		string send_msg = ultostr(admin_msg.length()) + admin_msg;
		for (auto it = conn_list.begin(); it != conn_list.end(); it++)
		{
			write(*it, send_msg.c_str(), send_msg.length());			
		}
		freeaddrinfo(serv_info);
	}
}

void Server::checkNewMessages()
{
	for (auto it = conn_list.begin(); it != conn_list.end(); ++it)
	{
		if (FD_ISSET(*it, &readset))
		{	
			int bytes_read;
			sockaddr_in client_addr;
			socklen_t calen = sizeof(client_addr);
			memset(buffer, 0, MSGMAX + 1);
			if ((bytes_read = read(*it, buffer, MSGMAX)) == 0)
			{
				//disconnect
				getpeername(*it, (sockaddr*)&client_addr, &calen);
				string admin_msg = "admin: (" + to_string(ntohs(client_addr.sin_port)) + ")" + string(inet_ntoa(client_addr.sin_addr)) + " has disconnected. ";
				cout << admin_msg  << endl;
				close(*it);
				it = conn_list.erase(it);
				string send_msg = ultostr(admin_msg.length()) + admin_msg;
				for (auto it2 = conn_list.begin(); it2 != conn_list.end(); it2++)
				{
					write(*it2, send_msg.c_str(), send_msg.length());	
				}					
			}
			else
			{
				getpeername(*it, (sockaddr*)&client_addr, &calen);			
				getMessageBuffer(*it, bytes_read);	
				if (msgIsValid())
				{
					string peer_msg = "(" + to_string(ntohs(client_addr.sin_port)) + ") " + string(inet_ntoa(client_addr.sin_addr)) + ": " + string(msg);
					cout << peer_msg << endl;
					string send_msg = ultostr(peer_msg.length()) + peer_msg;
					for (auto it2 = conn_list.begin(); it2 != conn_list.end(); it2++)
					{
						if (*it != *it2)
						{
							write(*it2, send_msg.c_str(), send_msg.length());	
						}
					}
				}
				
				delete msg;
			}
		}
	}
}

bool Server::msgIsValid()
{
	return !(strcmp(msg, " ") == 0 || strcmp(msg, "\n") == 0 ||
	   strcmp(msg, "\r") == 0 || strlen(msg) == 0);
}


void Server::ioListen()
{
	if (select(initReadSet(readset, main_socket, &conn_list), &readset, NULL, NULL, NULL) == FAILURE) //read up to max socket for activity
	{
		cerr << "Select failed" << endl;
		exit(1);
	}
	checkExitServer();
	checkNewConnections();
	checkNewMessages();
}


Server::~Server()
{
	for (auto it = conn_list.begin(); it != conn_list.end(); it++)
	{
		close(*it);
	}
	close(main_socket);
}

Client::~Client()
{
	close(main_socket);
}

Client::Client(const char *host, const char *port)
{
	addrinfo *server_info;
	sockaddr_in sa = getSockAddrInfo(htons(atoi(port))), *h;
	if (inet_aton(host, (in_addr *) &sa.sin_addr.s_addr))
	{
		if ((main_socket = socket(AF_INET, SOCK_STREAM, 0)) == FAILURE)
		{
			cerr << "Failed to create socket" << endl;
			exit(1);
		}
		if (connect(main_socket, (sockaddr *) &sa, sizeof(sa)) == FAILURE)
		{
			cerr << "Failed to Connect!" << endl;
			exit(1);
		}
	}
	else
	{
		addrinfo hints = getHints(AI_PASSIVE);
		if (getaddrinfo(host, "http", &hints, &server_info) == FAILURE)
		{
			cerr << host << ": failed to resolve" << endl;
			exit(1);
		}	
		addrinfo *ai_ptr;
		for(ai_ptr = server_info; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next) 
		{
			h = (sockaddr_in *) ai_ptr->ai_addr;
			server_ip = inet_ntoa(h->sin_addr);	
			if (inet_aton(server_ip.c_str(), (in_addr *) &sa.sin_addr.s_addr))
			{
				if ((main_socket = socket(AF_INET, SOCK_STREAM, 0)) == FAILURE)
				{
					continue;
				}

				if (connect(main_socket, (sockaddr *) &sa, sizeof(sa)) == FAILURE)
				{
					continue;
				}
				
				break; //successful connect
			}
		}
		if (ai_ptr == NULL)
		{
			cerr << "Could not connect" << endl;
			exit(1);
		}
		freeaddrinfo(server_info);
	}
}

void Client::ioListen()
{
	if (select(initReadSet(readset, main_socket), &readset, NULL, NULL, NULL) == FAILURE) //read up to max socket for activity
	{
		cerr << "Select failed" << endl;
		exit(1);
	}
	if (FD_ISSET(KEYBOARD, &readset)) //keyboard
	{
		string user_msg;
		getline(cin, user_msg);
		string send_msg = ultostr(user_msg.length()) + user_msg;
		write(main_socket, send_msg.c_str(), send_msg.length());
	}
	if (FD_ISSET(main_socket, &readset)) //server
	{
		int bytes_read;
		if ((bytes_read = read(main_socket, buffer, MSGMAX)) == 0)
		{
			cerr << "Disconnected from server." << endl;
			exit(1);
		}
		else
		{
			getMessageBuffer(main_socket, bytes_read);
			cout << msg << endl;
			delete msg;
		}
	}
}