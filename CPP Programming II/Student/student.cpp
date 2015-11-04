#include <iostream>
#include "student.h"

using namespace std;

Biology::Biology(string* name, int* grade)
{
    lastName = name[0];
    firstName = name[1];
    course = "Biology";
    lab = grade[0];
    finalExam = grade[4];
    for (int i = 0; i < 3; i++)
    {
        midterm[i] = grade[i + 1];
    }
}

Theater::Theater(string* name, int* grade)
{
    lastName = name[0];
    firstName = name[1];
    course = "Theater";
    participation = grade[0];
    midterm = grade[1];
    finalExam = grade[2];
}

ComputerScience::ComputerScience(string* name, int* grade)
{
    lastName = name[0];
    firstName = name[1];
    course = "Computer Science";
    for (int i = 0; i < 6; i++)
    {
        assignment[i] = grade[i];
    }
    midterm[0] = grade[6];
    midterm[1] = grade[7];
    finalExam = grade[8];

}


int Biology::GetFinalExam() const
{
    return finalExam;
}

int Theater::GetFinalExam() const
{
    return finalExam;
}
int ComputerScience::GetFinalExam() const
{
    return finalExam;
}
string Student::GetFirstName() const
{
    return firstName;
}

string Student::GetLastName() const
{
    return lastName;
}

string Student::GetCourse() const
{
    return course;
}

double Biology::GetAverage() const
{
    double average = lab * 0.30;
    average += (midterm[0] + midterm[1] + midterm[2]) * 0.15;
    average += finalExam * .25;
    return average; 
}

double Theater::GetAverage() const
{
    double average = participation * 0.40;
    average += midterm * 0.25;
    average += finalExam * 0.35;
    return average;
}

double ComputerScience::GetAverage() const
{
    double average = 0;
    for (int i = 0; i < 6; i++)
    {
        average += assignment[i];
    }
    average = (average / 6) * 0.30;
    average += (midterm[0] + midterm[1]) * 0.20;
    average += finalExam * 0.30;
    return average;
}

char Student::GetLetterGrade() const
{
    return CalculateLetterGrade(GetAverage());
}

char Student::CalculateLetterGrade(double grade) const
{
    if (grade >= 90)
    {
        return 'A';
    }
    else if (grade >= 80)
    {
        return 'B';
    }
    else if (grade >= 70)
    {
        return 'C';
    }
    else if (grade >= 60)
    {
        return 'D';
    }
    else 
    {
        return 'F';
    }
}

