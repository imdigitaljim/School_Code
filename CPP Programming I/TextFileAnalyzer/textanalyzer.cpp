#include <iomanip>
#include <iostream>
#include <fstream>
#include <cctype>


using namespace std;


void docWord(ofstream & out, const char *c, int f, double g); // & is a passby reference which gives reference to original object so the
// new function can edit the passed variables //if using pointers like *c they should stay const unless being changed

int main(){

	ifstream inFile;
	ofstream outFile;
	char userFile[80];
	char outputFile[80];
	int numberCount = 0;
	int digitCount = 0;
	int upperCount = 0;
	int alphaCount = 0;
	int spaceCount = 0;
	int miscCount = 0;
	int totalChar = 0;
	int letterCount[26];
	int numberSum = 0;

	for (int x = 0; x < 26; x++)
	{
		letterCount[x] = 0;
	}

	cout << "Please enter the name of the input file: " << endl;
	cout << "Filename:";
	cin >> userFile;

	inFile.open(userFile);

	if (!inFile.good())
	{
		cout << "This is an invalid file" << endl ;
	}
	else 
	{ 
		char c = inFile.peek(); //looks at the char but has to be here before while so it checks for it its good before it runs
		while (inFile.good()) //  ^another iteration. must be followed at end of loop
		{


			if (isdigit(c)){

				int temp = 0;
				inFile >> temp;
				numberSum += temp;
				numberCount++;
				int w = 0;
				do
				{
					temp /= 10;
					w++;
					digitCount++;
					totalChar++;

				}while (temp > 0);
			}




			else 
			{
				totalChar++;
				c = inFile.get();
				if (isalpha(c)){

					alphaCount++;
					if (isupper(c))
					{
						upperCount++;

					}
					char d = tolower(c);
					letterCount[d - 'a']++;

				}

				else if (isspace(c)){
					spaceCount++;
				}
				else
				{
					miscCount++;
				}
			}
			c = inFile.peek(); // to continue the loop until completed
		} 
	}

	cout << "Please enter the name of the output file: " << endl;
	cout << "Filename:";
	cin >> outputFile;



	inFile.close();
	outFile.open(outputFile);
	outFile << "Statistics for file: " << outputFile << endl
		<< setfill('-') << setw(50) << "" << endl
		<< "Total # of characters in file: " << setfill(' ') << setw(10) << totalChar << endl
		<< endl << "Category                How many in file           % of file" << endl
		<< setfill('-') << setw(70) << "" << endl;
	docWord(outFile, "Letters", alphaCount, alphaCount*100.0/totalChar); // .0 on the 100 turns 2 ints into a double... 100.0f would float
	docWord(outFile, "White Space", spaceCount, ((double) spaceCount)*100/totalChar); // (double) is a cast
	docWord(outFile, "Digits", digitCount, digitCount*100.0/totalChar);
	docWord(outFile, "Other characters", miscCount, miscCount*100.0/totalChar);
	outFile << endl << endl 
		<< "LETTER STATISTICS" << endl << endl
		<< "Category                How many in file    % of all letters" << endl
		<< setfill('-') << setw(70) << endl;
	docWord(outFile, "Uppercase", upperCount, upperCount*100.0/alphaCount);
	docWord(outFile, "Lowercase", alphaCount - upperCount, (alphaCount - upperCount)*100.0/alphaCount);
	for (int i = 0; i < 26; i++)
	{
		char z[2] = {i + 97,0}; 
		// making a char array of 2 characters long, z[0] is i, z[1] is 0; 
		//it created an array with a character then a terminator "0"
		//in the example: "Uppercase" autoterminates.
		//The pointer* gets the first of the type from the line until it terminates.
		docWord(outFile, z, letterCount[i], letterCount[i]*100.0/alphaCount);
	}
	outFile << endl << endl 
		<< "NUMBER ANALYSIS" << endl << endl
		<< left << setw(35) <<"Number of integers in the file:" << numberCount << endl
		<< left << setw(35) <<"Their sum:" << numberSum << endl
		<< left << setw(35) <<"Their average:" << setprecision(2) << numberSum*1.0/ numberCount << endl;

	outFile.close();


	return 0;
}


void docWord(ofstream & out, const char *c, int f, double g)
{
	out << setfill(' ') << setw(15) << left << c  << setw(24) << right <<  f  << setw(22) << right  << setprecision(2) << fixed << g << " %" << endl;
}