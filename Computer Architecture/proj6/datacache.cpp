/***********************************************************
* *
* Name: James Bach *
* Class: CDA3101 *
* Assignment: Implementing a Data Cache Simulator *
* Compile: "g++47 -std=c++11 -o datacache.x datacache.cpp" *
* *
***********************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <list>
#include <climits>
#include <sstream>
#define CONFIG 3
#define INTSIZE sizeof(int) * 8
#define BITVALID 1
#define MAXNUMSETS 8192
#define MINLINESIZE 8

using namespace std;

//input data structure
struct DataLine
{
	string error;
	char access;
	unsigned int sizeofRef, address;
};

//used to collect info for line prints
struct LineInfo
{
	int tag, index, offset, memrefs;
	char RorW;
	string result;
	bool isGood = true;
};

// each index level of cache
struct CacheStatus
{
	vector<bool> validBit;
	vector<bool> dirtyBit;
	vector<int> cacheTag;
	list<int> LRU;
	CacheStatus(){}
	CacheStatus(int x)
	{
		validBit.resize(x);
		cacheTag.resize(x);
		dirtyBit.resize(x);
		for (int i = 0; i < x; i++)
		{
			LRU.push_back(i);
		}
	}
};

void InitCacheStatus();
void PrintHeaderToFile(ofstream&);
void PrintBodyToFile(ofstream&);
void PrintFooterToFile(ofstream&);
void ExtractDATFile(ifstream&);
void ExtractConfigFile(ifstream&);
void CheckInput();
bool CheckCache(LineInfo&);
int GetAlignment(int, int);
LineInfo GetLineInfo(int);

//config input
int traceConfig[CONFIG];
int iLN, oLN, hit, miss, misaligned = 0;
vector<DataLine> traceData; //trace.dat extraction
vector<CacheStatus> status; //current cache status

//********************** MAIN
int main(int argc, char** argv)
{
	if (argc != 2) //check for bad parameters
	{
		cerr << "Usage: " << argv[0] << " trace.dat " << endl;
		exit(1);
	}
	ifstream inFile("trace.config");
	ExtractConfigFile(inFile);
	inFile.close();
	inFile.open(argv[1]);
	ExtractDATFile(inFile);
	inFile.close();
	ofstream outFile("trace.stats");
	PrintHeaderToFile(outFile);
	PrintBodyToFile(outFile);
	PrintFooterToFile(outFile);
	outFile.close();
	return EXIT_SUCCESS;
}

//extract information from the trace.config
void ExtractConfigFile(ifstream& in)
{
	string line;
	int count = 0;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			sscanf(line.c_str(),"%*[^:]: %d", &traceConfig[count++]);
			// [0] is number of sets; [1] is set size; [2] is line size;
		}
	}
	else
	{
		cerr << "could not open trace.config file in current directory" << endl;
		exit(1);
	}

	CheckInput();
	InitCacheStatus();
	iLN = log2(traceConfig[0]);	//index = log2#ofsets
	oLN = log2(traceConfig[2]);	//offset = log2linesize	
}

//validates the trace.config file inputs
void CheckInput()
{
	if (traceConfig[0] > MAXNUMSETS)
	{
		cerr << "error - number of sets requested exceeds MAXNUMSETS" << endl;
		exit(1);
	}
	if (traceConfig[2] < MINLINESIZE)
	{
		cerr << "linesize too small" << endl;
		exit(1);
	}
	int i = traceConfig[0];
	int o = traceConfig[2];
	while (i > 1)
	{
		if (i % 2 != 0)
		{
			cerr << "numsets not a power of two" << endl;
			exit(1);
		}
		i %= 2;
	}
	while (o > 1)
	{
		if (o % 2 != 0)
		{
			cerr << "linesize not a power of two" << endl;
			exit(1);
		}
		o %= 2;
	}
}

//initialize the state of the cache
void InitCacheStatus()
{
	status.resize(traceConfig[0]);
	for (size_t i = 0; i < status.size(); i++)
	{
		CacheStatus cs {traceConfig[1]};
		status[i] = cs;
	}
}

//extract the data file
void ExtractDATFile(ifstream& in)
{
	string line;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			DataLine dat;
			if (sscanf(line.c_str(),"%c : %u : %x", &dat.access, &dat.sizeofRef, &dat.address) != 3)
			{
				dat.error = line;
			}
			traceData.push_back(dat);
		}
	}
	else
	{
		cerr << "Cannot Read trace.dat" << endl;
		exit(1);
	}	
}

//begin printing the output header
void PrintHeaderToFile(ofstream& out)
{
	out << "Cache Configuration" << endl << endl;
	out << "   " << traceConfig[0] << " " << traceConfig[1] << "-way set associative entries" << endl;
	out << "   of line size " << traceConfig[2] << " bytes" << endl << endl << endl;
	out << "Results for Each Reference" << endl << endl;
	out << "Ref  Access Address    Tag   Index Offset Result Memrefs" << endl;
	out << "---- ------ -------- ------- ----- ------ ------ -------" << endl;
}

//print body section using data file
void PrintBodyToFile(ofstream& out)
{

	for (size_t i = 0; i < traceData.size(); i++)
	{
		//check if the line was valid input
		if (traceData[i].error.length() > 0)
		{
			cerr << "reference " << dec << i + 1 << " is illegal: " 
			<< traceData[i].error << endl << endl;
			misaligned++;
			continue;
		}
		//check for R or W and get the word form for printing
		string accessType;
		switch (traceData[i].access)
		{
			case 'R': accessType = "read"; break;
			case 'W': accessType = "write"; break;
			default: cerr << "reference " << i + 1 << 
			" has unknown access type " << traceData[i].access << endl;
			misaligned++;
			continue;
		}
		LineInfo p = GetLineInfo(i);//get and validate line for printing
		if (p.isGood)
		{
			out << setw(4) << right << dec << i - misaligned + 1; //list starts at 1
			out << setw(7) << right << accessType;
			out << setw(9) << right << hex << traceData[i].address;
			out << setw(8) << right << hex << p.tag;
			out << setw(6) << right << dec << p.index;
			out << setw(7) << right << dec << p.offset;
			out << setw(7) << right << dec << p.result;
			out << setw(8) << right << dec << p.memrefs;
			out << endl;
		}
		else
		{
			//if it was bad skip it
			misaligned++;
		}
	}
	out << endl << endl;
}

//gets and validates the line printing information
LineInfo GetLineInfo(int x) 
{
	//build the line for output
	LineInfo line;
	line.RorW = traceData[x].access;
	line.offset = traceData[x].address & (UINT_MAX >> (INTSIZE - oLN));
	line.index = (traceData[x].address & (UINT_MAX >> (INTSIZE - iLN)) << oLN) >> oLN;
	line.tag = traceData[x].address >> (iLN + oLN);

	//check for alignment
	int align = GetAlignment(traceData[x].sizeofRef, x);
	if (align < 0)
	{
		line.isGood = false;
		return line;
	}
	else if ((line.offset & align) != 0)
	{
		cerr << "line " << dec << x + 1 << " has misaligned reference at address " 
		<< hex << traceData[x].address << " for size " << dec << traceData[x].sizeofRef << endl; 
		line.isGood = false;
		return line;
	}
	
	bool isHit = CheckCache(line);
	
	//if the cache was a hit or miss
	if (isHit)
	{
		hit++;
		line.result = "hit";
	}	
	else
	{
		miss++;
		line.result = "miss";
	}
	return line;
}

//validate the alignment is correct
int GetAlignment(int s, int lineNum)
{
	switch (s)
	{
		case 1: return 0; 	case 2: return 1;
		case 4: return 3; 	case 8: return 7;
		default: cerr << "line " << dec << lineNum + 1
		<< " has illegal size " << s << endl;	
		return -1;
	}
}

//check the cache based on the index already found
bool CheckCache(LineInfo& line)
{
	CacheStatus* lineState = &status[line.index];
	for (int i = 0; i < traceConfig[1]; i++)
	{
		//if tag matches and valid bit is set
		if (lineState->cacheTag[i] == line.tag 
		&& lineState->validBit[i])
		{
			//if write
			if (line.RorW == 'W')
			{
				line.memrefs = 0;
				lineState->dirtyBit[i] = true;
			}
			else // its read
			{
				line.memrefs = 0;
			}
			//update the LRU
			lineState->LRU.remove(i);
			lineState->LRU.push_back(i);
			return true;
		}
	}
	//if no tags matched, is the LRU dirty bit set
	if (lineState->dirtyBit[lineState->LRU.front()])
	{
		line.memrefs = 2;
		//is the next one a  read
		if (line.RorW == 'R')
		{
			lineState->dirtyBit[lineState->LRU.front()] = false;
		}	
	}
	else //not dirty
	{
		line.memrefs = 1;
		//is the next one write
		if (line.RorW == 'W')
		{
			lineState->dirtyBit[lineState->LRU.front()] = true;
		}		
	}
	lineState->validBit[lineState->LRU.front()] = true;
	lineState->cacheTag[lineState->LRU.front()] = line.tag;
	lineState->LRU.push_back(lineState->LRU.front());
	lineState->LRU.pop_front();	
	return false;
}

//print out the footer section
void PrintFooterToFile(ofstream& out)
{
	int totalAccess = traceData.size() - misaligned;
	out << "Simulation Summary Statistics" << endl;
	out << "-----------------------------" << endl;
	out << "Total hits       : " << dec << hit << endl;
	out << "Total misses     : " << miss << endl;
	out << "Total accesses   : " << totalAccess << endl;
	out << fixed << setprecision(6); //set formatting
	out << "Hit ratio        : " << hit * 1.0 / totalAccess << endl;
	out << "Miss ratio       : " << miss * 1.0 / totalAccess << endl << endl;
}



