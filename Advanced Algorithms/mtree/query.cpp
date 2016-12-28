#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include "debugtimer.h"
#include "mtree.h"
#include "inversion.h"

using namespace std;

void read_queries();

/* Heap Memory*/

vector<char*> nodes;
int alpha2num(const char* asciiStr);
extern FILE* inputFile;

/*test variables*/
int query_count;


int main(int argc, char** argv)
{
	#if TIME_ON
	BTimer benchmark;
	benchmark.Start();
	#endif
	MTree t; //to use class functions
	read_queries();
	cout << "querying" << endl;	
	inputFile = fopen("data.mtree", "rb");
	for (int i = 0; i < query_count; i++)
	{
		t.Query(nodes[i]);
		delete nodes[i];
		TIME(benchmark.GetDeltaTime());
	}
	fclose(inputFile);
	#if TIME_ON
	cout << "TOTAL TIME:" << benchmark.Stop() << endl;
	#endif
}


void read_queries()
{
	cin >> query_count; //get query count
	cin.ignore(); //ignore \n
	string input;
	char line[90], *token, *content;
	for (int i = 0; i < query_count; i++)
	{
		content = new char[32];
		getline(cin, input);
		strcpy(line, input.c_str());
		token = strtok(line, ",\n\r");
		for (int i = 0; i < 32; i++)
		{
			content[i] = alpha2num(token);
			token = strtok(nullptr, ",\n");
		}
		nodes.push_back(content);
		

	}
	cout << "query read complete!" << endl;
}

int alpha2num(const char* asciiStr)
{
	int num = 0;
	while (*asciiStr) {
		num = (*asciiStr++ - '0') + num * 10;
	}
	return num;
}
