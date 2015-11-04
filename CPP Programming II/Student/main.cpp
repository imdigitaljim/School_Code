#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>
#include <string>
#include "student.h"

using namespace std;

void ConvertToUpper(string&);
void PostStudents(const int, const string, Student**, ofstream&, int*);
void SortStudents(Student**, const int);

int main()
{
    ifstream inFile;
    ofstream outFile;

    string fileName;
    string studentName[2];
    string subject;

    int rosterSize;
    int letterGrades[6] = {};
    int grades[9];
    
    //get and validate input file
    cout << "Please enter the name of the input file." << endl;
    cout << "Filename: ";
    getline(cin,fileName);
    if (!inFile.good())
    {
        cout << "This is an invalid file (1)" << endl ;
        return 0;
    }
    inFile.open(fileName.c_str());
    
    //get and set the roster size
    inFile >> rosterSize;
    inFile.ignore(); // ignore eol
    Student** roster = new Student*[rosterSize];
    for (int i = 0; i < rosterSize; i++)
    {
        getline(inFile, studentName[0], ',');
        inFile.ignore(); //ignore space after comma
        getline(inFile, studentName[1]);
        inFile >> subject;
        if (subject == "Computer")
        {
            inFile >> subject; // catch 'Science'
            for (int j = 0; j < 9; j++)
            {
                inFile >> grades[j];
            }
            roster[i] = new ComputerScience(studentName, grades);
        }
        else if (subject == "Theater")
        {            
            for (int j = 0; j < 3; j++)
            {
                inFile >> grades[j];
            }
            roster[i] = new Theater(studentName, grades);
        }
        else if (subject == "Biology")
        {
            for (int j = 0; j < 5; j++)
            {
                inFile >> grades[j];
            }
            roster[i] = new Biology(studentName, grades);
        }
        else
        {
            cout << "This is an invalid file (2)" << endl ;
            return 0;
        } 
        inFile.ignore();
    }
    SortStudents(roster, rosterSize);
    
    //prepare output file
    cout << "Please enter the name of the output file." << endl;
    cout << "Filename: ";
    getline(cin,fileName);

    outFile.open(fileName.c_str());
    outFile << "Student Grade Summary" << endl;
    outFile << "---------------------" << endl;
    
    outFile << endl;
    outFile << "BIOLOGY CLASS" << endl;
    outFile << endl;
    PostStudents(rosterSize, "Biology", roster, outFile, letterGrades);
    
    outFile << endl << endl;
    outFile << "THEATER CLASS" << endl;
    outFile << endl;
    PostStudents(rosterSize, "Theater", roster, outFile, letterGrades);
   
    outFile << endl << endl;
    outFile << "COMPUTER SCIENCE CLASS" << endl;
    outFile << endl;
    PostStudents(rosterSize, "Computer Science", roster, outFile, letterGrades);
    
    outFile << endl << endl;
    outFile << "OVERALL GRADE DISTRIBUTION" << endl;
    outFile << endl;
    outFile << "A:   " << letterGrades[0] << endl;
    outFile << "B:   " << letterGrades[1] << endl;
    outFile << "C:   " << letterGrades[2] << endl;
    outFile << "D:   " << letterGrades[3] << endl;
    outFile << "F:   " << letterGrades[5] << endl;
 
    for (int i = 0; i < rosterSize; i++)
    {
        delete roster[i];
    }
    delete[] roster;
    return 0;
}

void ConvertToUpper(string& name)
{
    for (int i = 0; i < name.length(); i++)
    {
        name[i] = toupper(name[i]);
    }
}

void SortStudents(Student** r, const int size)
{
    string name1;
    string name2;
    int orderBefore;

    for (int i = 0; i < size - 1; i++)
    {
        name1 = r[i]->GetLastName() +  r[i]->GetFirstName(); 
        ConvertToUpper(name1);
        orderBefore = i;
        for (int j = i + 1; j < size; j++)
        {
            name2 = r[j]->GetLastName() + r[j]->GetFirstName(); 
            ConvertToUpper(name2);
            if (name1 > name2)
            {
                name1 = name2;
                orderBefore = j;
            } 
            
        }
        if (orderBefore != i)
        {
            swap(r[i],r[orderBefore]);
        }
    }
}

void PostStudents(const int size, const string subject, Student** r, ofstream& out, int* letter)
{
    out << "Student                                   Final   Final   Letter" << endl;
    out << "Name                                      Exam    Avg     Grade " << endl;
    out << "----------------------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++)
    {
       
        if (r[i]->GetCourse() == subject)
        {
        string name = r[i]->GetFirstName() + " " +  r[i]->GetLastName(); 
        out << left << setw(42) << name; 
        out << r[i]->GetFinalExam() << "      ";
        out << setprecision(2) << fixed << r[i]->GetAverage() << "   ";
        out << r[i]->GetLetterGrade() << endl;
        letter[r[i]->GetLetterGrade() - 'A']++;            
        }
    } 
}

 


