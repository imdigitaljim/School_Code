#ifndef _H_MYDIST_
#define _H_MYDIST_
#include <iostream>

using namespace std;

class Distance
{
    friend ostream& operator<<(ostream&, const Distance&);
    friend istream& operator>>(istream&, Distance&);
    friend Distance operator+(const Distance&, const Distance&);
    friend Distance operator-(const Distance&, const Distance&);
    friend Distance operator*(const Distance&, const Distance&);
    friend bool operator<(const Distance&, const Distance&);
    friend bool operator>(const Distance&, const Distance&);
    friend bool operator<=(const Distance&, const Distance&);
    friend bool operator>=(const Distance&, const Distance&);
    friend bool operator==(const Distance&, const Distance&);
    friend bool operator!=(const Distance&, const Distance&);

public:

    Distance();
    Distance(int);
    Distance(int, int, int, int);

    Distance& operator++ (); // pre 
    Distance& operator-- (); // pre
    Distance operator++(int); //post
    Distance operator--(int); // post

private:

    void Set(int,int,int,unsigned long long);
    unsigned long long GetTotalInches() const;
    //to prevent edge case from stable max (intmax, 1759, 2, 11)

    int inches;
    int feet;
    int yards;
    int miles;

};

#endif
