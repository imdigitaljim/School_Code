/*
Course: CNT5505 - Data Networks and Communications
Semester: Spring 2016
Name: James Bach
*/

#include "socketutil.h"

using namespace std;

int main(int argc, char** argv)
{	
	if (argc != 3)
	{
		cerr << "usage: " << argv[0] << " <servhost> <servport>" << endl;
		exit(1);
	}
	Client conn(argv[1], argv[2]);	
	while(true)
	{
		conn.ioListen();
	}
	return 0;
}

