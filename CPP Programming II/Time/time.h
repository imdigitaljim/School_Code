#ifndef _MYTIME_H
#define _MYTIME_H
#include <iostream>

using namespace std;

class Time

{  
    friend ostream& operator << (ostream&, const Time&);
    friend istream& operator >> (istream&, Time&);
    friend Time operator + (const Time&, const Time&);
    friend Time operator - (const Time&, const Time&);
    friend bool operator < (const Time&, const Time&);
    friend bool operator > (const Time&, const Time&);
    friend bool operator <= (const Time&, const Time&);
    friend bool operator >= (const Time&, const Time&);
    friend bool operator == (const Time&, const Time&);
    friend bool operator != (const Time&, const Time&);


public:

    Time& operator ++ (); // pre-
    Time& operator -- (); 
    Time operator ++ (int); // post- 
    Time operator -- (int);

    Time();
    Time(int, int, int, int);
    Time(int);


private:

    void PrintTwoDigit(ostream&, int) const;
    void Set(int, int, int, int);
    void Reduce(int, int, int, int);
    int days;
    int hours;
    int minutes;
    int seconds;
};


#endif