/*
Course: CNT5505 - Data Networks and Communications
Semester: Spring 2016
Name: James Bach
*/

#include "socketutil.h"

using namespace std;

int main(int argc, char** argv)
{
	Server conn;
	while(true)
	{
		conn.ioListen();
	}
	return 0;
}