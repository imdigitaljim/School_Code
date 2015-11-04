#include <iostream>
#include "distance.h"

using namespace std;

Distance::Distance()
{
    Set(0, 0, 0, 0);
}

Distance::Distance(int d)
{
    Set(0, 0, 0, d);
}

Distance::Distance(int m, int y, int f, int i)
{
    Set(m, y, f, i);
}

void Distance::Set(int m, int y, int f, unsigned long long i)
{
	unsigned long long foot_container;  //
	unsigned long long yard_container;  //
	unsigned long long mile_container;  // is used to preserve the specs of support int, int, int, int size
    if (i < 0 || f < 0 || y < 0 || m < 0)
    {
        inches = 0;
        feet = 0;
        yards = 0;
        miles = 0;
    }
    else
    {
        foot_container = f + i / 12;
        inches = i % 12;
		
        yard_container = y + foot_container / 3;
        feet = foot_container % 3;
       
        mile_container = m + yard_container / 1760;
        yards = yard_container % 1760;
    
        miles = mile_container;
    }
}
unsigned long long Distance::GetTotalInches() const
{
    const long long feetTemp = 12; 
    const long long yardTemp = 36; 
    const long long mileTemp = 63360;
    //^edge case prevention from conversion math operation int to long long
    return inches + (feet * feetTemp) + (yards * yardTemp) + (miles * mileTemp); 
}

ostream& operator<<(ostream& out, const Distance& d)
{
    if (d.miles > 0)
    {
        out << d.miles << "m ";
    }
    if (d.yards > 0)
    {
        out << d.yards << "y ";
        }
    if (d.feet > 0)
    {
        out << d.feet << "' ";
    }
    out << d.inches << "\"";
    return out;
}

istream& operator>>(istream& in, Distance& d)
{
    char temp;
    in >> d.miles >> temp >> d.yards >> temp >> d.feet >> temp >> d.inches;
    d.Set(d.miles, d.yards, d.feet, d.inches);
}

Distance operator+(const Distance& x, const Distance& y)
{
    Distance temp;
    temp.Set(0, 0, 0, x.GetTotalInches() + y.GetTotalInches());
    return temp;
}

Distance operator-(const Distance& x, const Distance& y)
{
    Distance temp;
    temp.Set(0, 0, 0, x.GetTotalInches() - y.GetTotalInches());
    return temp;
}

Distance operator*(const Distance& x, const Distance& y)
{
    Distance temp;
    temp.Set(0, 0, 0, x.GetTotalInches() * y.GetTotalInches());
    return temp;
}

bool operator<(const Distance& x, const Distance& y)
{
    if (x.GetTotalInches() < y.GetTotalInches())
    {
        return true;
    }
    return false;
}

bool operator>(const Distance& x, const Distance& y) 
{
    return y < x;
}

bool operator<=(const Distance& x, const Distance& y)
{
    return !(y < x);
}

bool operator>=(const Distance& x, const Distance& y)
{
    return !(x < y);
}

bool operator==(const Distance& x, const Distance& y)
{
    return !(x < y || y < x);
}

bool operator!=(const Distance& x, const Distance& y)
{
    return !(x == y);
}

Distance& Distance::operator++()
{
    Set(miles, yards, feet, inches + 1);
    return *this;
}

Distance& Distance::operator--()
{
    Set(0, 0, 0, GetTotalInches() - 1);
    return *this;
}

Distance Distance::operator++(int i)
{
    Distance temp = *this;
    Set(miles, yards, feet, inches + 1);
    return temp;
}

Distance Distance::operator--(int i)
{
    Distance temp = *this;
    Set(0, 0, 0, GetTotalInches() - 1);
    return temp;
}
