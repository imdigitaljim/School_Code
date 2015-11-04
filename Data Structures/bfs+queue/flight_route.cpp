#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Queue.h"

using namespace std;
using namespace cop4530;

struct CityNode
{
	int previous, costToPrevious;
	bool added;
	string name;
	vector<int> neighbors, cost;
};
int get_index(vector<CityNode>&, string);
void min_hop(vector<CityNode>&,int, int);
void reset(vector<CityNode>&);
void trace_back(vector<CityNode>&, int, int);

int main(int argc, char**argv)
{
	fstream file;
	string source, destination, input;
	int cityCount, value, src, dest;
	char select;
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " airline_file" << endl;
		exit(1);
	}
	file.open(argv[1]);
	if (!file.good())
	{
		cout << "invalid file" << endl;
		exit(1);
	}
	file >> cityCount;
	file.ignore();
	vector<CityNode> graph(cityCount);
	
	for (int i = 0; i < cityCount; ++i)
	{
		getline(file, input);
		graph[i].name = input;
	}
	for (int i = 0; i < cityCount; ++i)
	{
		for (int j = 0; j < cityCount; ++j)
		{
			file >> value;
			if (value > 0)
			{
				graph[i].neighbors.push_back(j);
				graph[i].cost.push_back(value);
			}
		}
	}
	file.close();
	
	cout << cityCount << " cities: " << endl;
	for (int i = 0; i < cityCount; ++i)
	{	
		cout << "    " <<  graph[i].name << endl;
	}
	cout << endl;
	cout << "direct flights between cities" << endl;
	cout << "-------------------------" << endl;
	for (int i = 0; i < cityCount; i++)
	{
		CityNode c = graph[i];
		cout << c.name << ": " << endl;
		for (size_t j = 0; j < c.neighbors.size(); j++)
		{
			if (c.cost[j] > 0)
			{
				cout << "    " << graph[c.neighbors[j]].name << ", ";
				cout << "$" << c.cost[j] << endl;
			}				
		}
	}
	cout << "------------------------" << endl << endl;
	
	do
	{
		reset(graph);
		cout << "Source city : ";
		getline(cin, source);
		src = get_index(graph, source);
		cout << "Destination city : ";
		getline(cin, destination);
		dest = get_index(graph, destination);
		cout << "finding min_hop route...." << endl;
		if (src < 0)
		{
			cout << "    path not found, source city, " << source;
			cout << ", not on the map" << endl << endl;
		}
		else if (dest < 0)
		{
			cout << "    path not found, destination city, " << destination;
			cout << ", not on the map" << endl << endl;
		}
		else
		{
			min_hop(graph, src, dest);
			trace_back(graph, dest, src);
		}

		do
		{
			cout << "Search another route? (Y/N)";
			getline(cin, input);
			select = toupper(input[0]);
		}
		while (!(select == 'Y' || select == 'N'));
	}while (select != 'N');
	return 0;
}
int get_index(vector<CityNode>& node, string s)
{
	for (size_t i = 0; i < node.size(); i++)
	{
		if (node[i].name == s)
		{
			return i;
		}
	}
	return -1;
}
void reset(vector<CityNode>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i].added = false;
		v[i].previous = -1;
	}
}

void min_hop(vector<CityNode>& g, int s, int d)
{
	Queue<int> path;
	int next;
	path.push(s);	
	g[s].added = true;
	while (!path.empty())
	{
		next = path.front();
		CityNode c = g[next];
		path.pop();
		for (size_t i= 0; i < c.neighbors.size(); ++i)
		{
			int currentNode = c.neighbors[i];
			if (currentNode == d || !g[currentNode].added)
			{
				g[currentNode].previous = next;
				g[currentNode].costToPrevious = g[next].cost[i];
				if (currentNode == d) return;
				g[currentNode].added = true;
				path.push(currentNode);	
			}
		}
	}
	cout << "path not found." << endl << endl;
	
}
void trace_back(vector<CityNode>& g, int back, int source)
{
	int tripCost = 0;
	vector<int> path;
	while (back != source)
	{
		path.push_back(back);
		tripCost += g[back].costToPrevious;
		back = g[back].previous;
	}
	path.push_back(source);
	cout << "   ";
	while (path.size() > 1)
	{
		cout << g[path.back()].name << " -> ";
		path.pop_back();
	}
	cout << g[path.front()].name << ", $" << tripCost << endl;

}
