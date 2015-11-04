#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <string>

using namespace std;

class Student
{
public:
    virtual double GetAverage() const = 0;
    virtual char GetLetterGrade() const;
    virtual int GetFinalExam() const = 0;
    char CalculateLetterGrade(double) const;
    
    string GetCourse() const;
    string GetFirstName() const;
    string GetLastName() const;
protected:
    string firstName;
    string lastName;
    string course;

};

class Biology: public Student
{
public:
    Biology(string*,int*);
    int GetFinalExam() const;
    double GetAverage() const;
    //    char GetLetterGrade() const;
private:
    int lab;//30%
    int midterm[3]; //15% each
    int finalExam;    //final 25%
};

class Theater: public Student
{
public:
    Theater(string*,int*);
    int GetFinalExam() const;
    double GetAverage() const;
    // char GetLetterGrade() const;
private:
    int participation; //40%
    int midterm; // 25%
    int finalExam;//final 35%
};

class ComputerScience: public Student
{
public:
    int GetFinalExam() const;
    ComputerScience(string*,int*);
    double GetAverage() const;
    // char GetLetterGrade() const;
    
private:
    int assignment[6]; // average = 30% 
    int midterm[2];  //20% each
    int finalExam; //final 30%
};

#endif
