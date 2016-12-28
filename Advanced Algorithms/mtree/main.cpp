#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "debugtimer.h"
#include "mtree.h"
#include "inversion.h"

using namespace std;

/*function declarations*/
void extract_inversions(const char* fileName);
MTree*  build_mtree();
void clear_tree();

/* Heap Memory storage for access and cleanup*/
extern vector<MTreeNode*> connectors;
extern vector<MTree*> trees;
vector<MTreeNode*> nodes; //global for saving entries

int main(int argc, char** argv)
{
	string invFile;
	getline(cin, invFile);
	cout <<"opening " << invFile << "..." << endl;
	#if TIME_ON
	BTimer benchmark;
	benchmark.Start();
	#endif
	extract_inversions(invFile.c_str()); //get entries from file and save to global: nodes
	TIME(benchmark.GetDeltaTime());
	MTree* t = build_mtree(); //build the m-tree in memory
	TIME(benchmark.GetDeltaTime());
	cout << "serializing..." << endl;
	t->root->Serialize(); //begin the serialization process from the in memory tree
	cout << "serialized!" << endl;
	TIME(benchmark.GetDeltaTime());
	clear_tree(); //heap cleanup
	TIME(benchmark.GetDeltaTime());
	#if TIME_ON
	cout << "TOTAL TIME:" << benchmark.Stop() << endl;
	#endif
	return 0;
}

MTree* build_mtree() //build m-tree data structure
{
	cout << "building tree..." << endl;
	MTree* result = new MTree(true);
	trees.push_back(result);
	int len = nodes.size();
	#if TIME_ON
	int marker, amount = len / 10;
	marker = amount;
	BTimer benchmark;
	benchmark.Start();
	#endif
	
	for (int i = 0; i < len; i++)
	{
		#if TIME_ON
		if (i == marker)
		{
			marker += amount;
			cout << i << " " << benchmark.GetDeltaTime() << endl;
		}
		#endif
		result->root->AddNode(nodes[i]);
	}
	cout <<"tree complete!" << endl;
	return result;
}

// heap cleanup function
void clear_tree() 
{
	cout << "clearing tree from heap..." << endl;
	int len = connectors.size();
	for (int i = 0; i < len; i++)
	{
		delete connectors[i];
	}
	len = trees.size();
	for (int i = 0; i < len; i++)
	{
		delete trees[i];
	}
	len = nodes.size();
	for (int i = 0; i < len; i++)
	{
		delete nodes[i];
	}
	cout << "tree cleared!" << endl;
}

//extracting entries efficiently from input file
void extract_inversions(const char* fileName)
{
	cout << "extracting..." << endl;
	FILE* inputFile;
	int fileSize, readAmount;
	char* inMemoryBuffer;
	inputFile = fopen(fileName, "rb");
	if (inputFile == nullptr)
	{
		cerr << "Error: Could not open file" << endl;
		exit(1);
	}
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	rewind(inputFile);
	inMemoryBuffer = (char*)malloc(sizeof(unsigned char)*fileSize);
	if (inMemoryBuffer == nullptr)
	{
		cerr << "Error: Could not allocate required memory" << endl;
		exit(2);
	}

	readAmount = fread(inMemoryBuffer, 1, fileSize, inputFile);
	if (readAmount != fileSize)
	{
		cerr << "Error: Did not read complete file" << endl;
		exit(3);
	}
	//this next section is effectively a custom (faster) strtok made using the well defined input file
	//optimized for faster extraction
	int index = 0, col = 0;
	char tempRow[32];
	char* current = inMemoryBuffer, *end = inMemoryBuffer + fileSize; 
	while (current <= end) //while tracking variable is valid
	{
		if (current[0] >= '1' && current[0] <= '3') // check for 2 digit case
		{
			if (current[1] < '0' || current[1] > '9') // was 1 digit
			{
				tempRow[col] = current[0] - '0'; // custom (faster) atoi, builds 32 entry array for tree entry
				current += 2;
			}
			else // was 2 digits
			{
				tempRow[col] = 10 * (current[0] - '0') + (current[1] - '0'); //custom (faster) atoi
				current += 3;
			}
		}
		else { // all remaining 1 digit cases
			tempRow[col] = current[0] - '0';
			current += 2; // eg 0,1     currently on 0, needs to be on '1' so needs 2 moves
		}
		col++;
		if (col == 32) //if end of row reset row
		{
			col = 0;
			//save all nodes (and their entries/line numbers) for building tree
			nodes.push_back(new MTreeNode(tempRow, index++)); 
		}
	}
	#if TIME_ON
	cout << "lines read = " << index << endl;
	#endif
	fclose(inputFile);
	free(inMemoryBuffer);
	cout << "extracting complete!" << endl;
}





