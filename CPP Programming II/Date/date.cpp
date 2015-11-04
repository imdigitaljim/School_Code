#include "date.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//default constructor
Date::Date() 
{
    Set(1,1,2000);
    format = 'D';
}

Date::Date(int m, int d, int y)
{
    if (!Set(m, d, y))
    {
        Set(1, 1, 2000);
    }
    format = 'D';
}

void Date::Input()
{
    int m, d, y;
    char slash;
    cout << endl << "Enter a Date: ";
    cin >> m >> slash >> d >> slash >> y; 
    while (!Set(m, d, y))
    {
        cout << endl << "Invalid Date. Try again: ";
        cin >> m >> slash >> d >> slash >> y; 
    }
}

void Date::Show() const
{
    const string monthAbbrev[12] = 
    { "Jan", "Feb", "Mar", "Apr", "May", "June", 
    "July", "Aug", "Sept", "Oct", "Nov", "Dec"};

    if (format == 'T') //mm/dd/yy
    {
        cout << setw(2) << setfill('0') << month << "/";
        cout << setw(2) << day << "/";
        cout << setw(2) << year % 100 << endl;
    }
    else if (format == 'L') //month D, Y
    {
        cout << monthAbbrev[month - 1] << " " << day << ", " << year << endl;
    }
    else if (format == 'J') 
    {
        int julianDays = 0;
        for (int i = 1; i < month; i++)
        {
            julianDays += GetDPM(i, year);
        }
        julianDays += day;
        cout << setw(2) << setfill('0') << year % 100;
        cout << "-" << setw(3) << julianDays;
    }
    else
    {
        //M/D/Y
        cout << month << "/" << day << "/" << year << endl;
    }
}

bool Date::SetFormat(char f)
{

    switch (toupper(f))
    {
    case 'D': 
    case 'T':
    case 'L':
    case 'J':
        format = toupper(f);
        return true;
    default:
        return false;
    }
    /*
    'D' = Default format 
    'T' = Two-Digit format 
    'L' = Long format 
    */
}

int Date::Compare(const Date& c) const
{
    const int older = 1;
    const int same = 0;
    const int newer = -1;

    if (c.year < year)
    {
        return older;
    }
    else  if (c.year > year)
    {
        return newer;
    }
    else if (c.month < month)
    {
        return older;
    }
    else if (c.month > month)
    {
        return newer;
    }
    else if (c.day < day)
    {
        return older;
    }
    else if (c.day > day)
    {
        return newer;
    }
    else 
    {
        return same;
    }

}

int Date::GetMonth() const
{
    return month;
}

int Date::GetDay() const
{
    return day;
}

int Date::GetYear() const
{
    return year;
}

bool Date::Set(int m, int d, int y)
{
    if (m < 1 || m > 12)
    {
        return false;
    }
    if (d < 1 || d > GetDPM(m, y))
    {
        return false;
    }
    if (y < 0)
    {
        return false;
    }

    month = m;
    day = d;
    year = y;

    return true;
}

int Date::GetDPM(int m, int y) const
{
    int calendar[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y % 100 != 0 || y % 400 == 0) && y % 4 == 0)
    {
        calendar[1] = 29;
    }
    else
    {
        calendar[1] = 28;
    }
    return calendar[m - 1];
}


void Date::Increment(int numDays)
{
    for (int i = 0; i < numDays; i++)
    {
        day++;
        if (day > GetDPM(month, year))
        {
            day = 1;
            month++;
            if (month > 12)
            {
                year++;
                month = 1;
            }
        }
    }
}
