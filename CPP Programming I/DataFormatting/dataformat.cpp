#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>

using namespace std; 

struct Student
{
	char lName[20];
	char fName[20];
	char course;
	int gradeOne;
	int gradeTwo;
	int gradeFinal;
	double testAverage;
	char letterGrade;
} ;

void extractData(ifstream &, Student *, int);
void docFill(ofstream &, Student *, int);  
void classFill(ofstream &, Student *, int, char);
void sort (Student *, int);

int main (){

	ifstream inFile;
	ofstream outFile;
	char userInputFile[80];
	char userOutputFile[80];
	cout << "Please enter the name of the input file." << endl
		<< "Filename:";
	cin >> userInputFile;
	inFile.open(userInputFile);

	while (inFile.fail()) 
	{	
		cout << "You have entered an invalid file." << endl
			<< "Please enter the name of the input file." << endl
			<< "Filename:";
		cin >> userInputFile;
		inFile.open(userInputFile);
	}

	if (inFile.good()) 
	{
		int recordSize = 0;
		inFile >> recordSize;
		Student* reportCard = new Student[recordSize]; //dynamic size struct array
		inFile.ignore(); // ignores the /n <- newline nonvisible char 
		extractData(inFile, reportCard, recordSize);
		inFile.close();
		sort(reportCard, recordSize);
		cout << "Please enter the name of the output file." << endl
			<< "Filename:";
		cin >> userOutputFile;
		outFile.open(userOutputFile);
		docFill(outFile, reportCard, recordSize);
		outFile.close();
		delete [] reportCard;
		cout << "Processing Complete." << endl;
	}
	return 0;

}
void docFill(ofstream & out, Student *data, int size)
{
	out << "Student Grade Summary" << endl
		<< "---------------------" << endl << endl
		<< "ENGLISH CLASS" << endl << endl;
	classFill(out, data, size, 'E');
	out << "HISTORY CLASS" << endl << endl;
	classFill(out, data, size,'H');
	out << "MATH CLASS" << endl << endl;
	classFill(out, data, size, 'M');

}
void classFill(ofstream & out, Student *data, int size, char c)
{
	double average = 0;
	int count = 0;
	out << "Student Name                             Test Avg" << endl
		<<"----------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < size; i++)
	{
		if (data[i].course == c)
		{
			count++;
			average+= data[i].testAverage;
			out << data[i].fName << " " << data[i].lName << right << setw(48 - strlen(data[i].fName) - strlen(data[i].lName))
				<< setprecision(2) << fixed << data[i].testAverage << "    " << data[i].letterGrade
				<< endl;
		}
	}
	if (count != 0) // DO NOT DIVIDE BY ZERO!! 
	{
		average /= count;
	}
	out << endl << "                Class Average               " 
		<< setprecision(2) << fixed << average << endl
		<< "----------------------------------------------------------------"
		<< endl << endl << endl;
}
void sort(Student *data, int size)  // simple sort
{
	for(int i = 0; i < size-1; i++){
		for(int j = i+1; j < size; j++){
			if(strcmp(data[i].lName, data[j].lName) > 0){
				Student temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
}

void extractData(ifstream & in, Student *data, int size)
{
	for (int i = 0; i < size; i++)
	{
		in.getline(data[i].lName, 20,','); 
		in.getline(data[i].fName, 20,','); 
		data[i].course = in.get(); 
		in.ignore(); 
		in >> data[i].gradeOne; 
		in.ignore(); 
		in >> data[i].gradeTwo; 
		in.ignore();  
		in >> data[i].gradeFinal;
		in.ignore(); 
		data[i].testAverage = data[i].gradeOne *.3f + data[i].gradeTwo *.3f + data[i].gradeFinal * .4f;
		if (data[i].testAverage >= 90)
		{
			data[i].letterGrade = 'A';
		}
		else if (data[i].testAverage >= 80)
		{
			data[i].letterGrade = 'B';
		}
		else if (data[i].testAverage >= 70)
		{
			data[i].letterGrade = 'C';
		}
		else if (data[i].testAverage >= 60)
		{
			data[i].letterGrade = 'D';
		}
		else
		{
			data[i].letterGrade = 'F';
		}
	}
}