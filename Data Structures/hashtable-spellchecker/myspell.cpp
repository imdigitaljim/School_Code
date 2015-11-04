#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include "hashtable.h"
#define MAXMATCH 10

using namespace std;
using namespace cop4530;

void menu();
void spellChecker(char**);
void replaceWord(string&, string, int);
string updateWord(HashTable<string>&, string);

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		menu();	
	}
	else if (argc == 4)
	{
		spellChecker(argv);
	}
	return EXIT_SUCCESS;
}

void menu()
{
	size_t htSize = 0;
	string input;
	cout << "Enter preferred hash table capacity: ";
	getline(cin, input);
	stringstream ss(input);
	ss >> htSize;
	HashTable<string> ht{htSize};

	while(true)
	{
		cout << "\n\n";
		cout << "l - Load Dictionary From File" << endl;
		cout << "a - Add Word" << endl;
		cout << "r - Remove Word" << endl;
		cout << "c - Clear HashTable" << endl;
		cout << "f - Find Word" << endl;
		cout << "d - Dump HashTable" << endl;
		cout << "s - HashTable Size" << endl;
		cout << "w - Write to File" << endl;
		cout << "x - Exit program" << endl;
		cout << "\nEnter choice : ";
		getline(cin, input);

		switch (tolower(input[0]))
		{
			case 'l':
				cout << "Enter dictionary filename to load from: ";
				cin >> input;
				cin.ignore();
				if (ht.load(input.c_str()))
				{
					cout << "Dictionary loaded successfully." << endl;
				}
				else
				{
					cout << "Cannot open file " << input << endl;
				}
				break;
			case 'a':
				cout << "Enter word: ";
				cin >> input;
				cin.ignore();
				cout << endl;
				if (ht.insert(input))
				{
					cout << "Word " << input << " added." << endl;
				}
				else
				{
					cout << "*****: Word already exists. Could not add." << endl;
				}
				break;
			case 'r':
				cout << "Enter word: ";
				cin >> input;
				cin.ignore();
				if (ht.remove(input))
				{
					cout << "Word " << input << " deleted." << endl;
				}
				else
				{
					cout << "*****: Word not found.  Could not delete" << endl;
				}
				break;
			case 'c':
				ht.clear();
				break;
			case 'f':
				cout << "Enter word: ";
				cin >> input;
				cin.ignore();
				if (ht.contains(input))
				{
					cout << "Word " << input << " found." << endl;
				}
				else
				{
					cout << "Word " << input << " not found." << endl;
				}
				break;
			case 'd':
				ht.dump();
				break;
			case 's':
				cout << "Size of hashtable: " << ht.size();
				break;
			case 'w':
				cout << "Enter dictionary file name to write to: ";
				cin >> input;
				cin.ignore();
				if (ht.write_to_file(input.c_str()))
				{
					cout << "Written successfully." << endl;
				}
				else
				{
					cout << "Cannot open file to write." << endl;
				}
				break;
			case 'x':
				exit(0);
			default:
				cout << "*****Error: Invalid entry.  Try again." << endl;
				break;
			
		}
	}
}

void spellChecker(char** argv)
{
	HashTable<string> dict{};
	cout << dict.capacity() << endl;
	dict.load(argv[1]);
	ifstream inFile(argv[2]);
	ofstream outFile(argv[3]);
	string input,line;
	if (inFile.is_open())
	{
		while(getline(inFile,line))
		{
			stringstream ss(line);
			int wc = 1;
			while (ss >> input)
			{	
				if (!dict.contains(input))
				{
					string misspell = input;
					transform(misspell.begin(), misspell.end(), misspell.begin(), ::toupper);
					replaceWord(line, misspell, wc);
					cout << line << endl;
					cout << "====================================" << endl;
					input = updateWord(dict, input);
					replaceWord(line, input, wc);
				}
				++wc;
			}
			if (outFile.is_open())
			{
				outFile << line << endl;
			}
		}
	}
	else
	{
		cerr << "Input file invalid" << endl;
		exit(1);
	}
	inFile.close();
	outFile.close();
}

void replaceWord(string& line, string replace, int wc)
{
	int pos = 1;
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!isspace(line[i])) 
		{
			if (wc == pos)
			{
				size_t j = 0;
				while (j < replace.length())
				{
					line[i] = replace[j];
					++i;
					++j;
				}
			}
			else
			{
				while (!isspace(line[i]))
				{
					++i;
				}
			}
			++pos;	
		}	
	}
}

string updateWord(HashTable<string>& dict, string input)
{
	vector<string> replacement;
	for (size_t i = 0; i < input.size() && replacement.size() < MAXMATCH; i++)
	{

		int j = 'a';
		string word = input;
		while (j < 'z' && replacement.size() < MAXMATCH)
		{
			word[i] = j;
			if (dict.contains(word))
			{
				cout << replacement.size() << "): " << word << endl;
				replacement.push_back(word);
			}
			j++;
		}
	}
	size_t select = -1;
	string choice;
	cout << "n (no change): " << endl;
	cout << "====================================" << endl;
	cout << "Your choice: ";
	getline(cin, choice);
	stringstream ss(choice); 
	ss >> select;
	
	if (select >= 0 && select < replacement.size())
	{
		input = replacement[select];
	}
	return input;
}


