#include "time.h"
#include <iostream>

using namespace std;

Time::Time()
{
    Set(0, 0, 0, 0);
}

Time::Time(int d, int h, int m, int s)
{
    Set(d, h, m, s); 
}
Time::Time(int s)
{
    Set(0, 0, 0, s);
}

bool operator<(const Time& x, const Time& y)
{
    return y > x;
}

bool operator>(const Time& x, const Time& y)
{
    if (x.days > y.days)
    {
        return true;
    }
    else if (x.days < y.days)
    {
        return false;
    }
    else if (x.hours > y.hours)
    {
        return true;
    }
    else if (x.hours < y.hours)
    {
        return false;
    }
    else if (x.minutes > y.minutes)
    {
        return true;
    }
    else if (x.minutes < y.minutes)
    {
        return false;
    }
    else if (x.seconds > y.seconds)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool operator<=(const Time& x, const Time& y)
{
    return x < y || x == y;
}

bool operator>=(const Time& x, const Time& y)
{
    return x > y || x == y;
}

bool operator==(const Time& x, const Time& y)
{
    if (x.days == y.days && x.hours == y.hours 
        && x.minutes == y.minutes && x.seconds == y.seconds)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool operator!=(const Time& x, const Time& y)
{
    return !(x == y);
}


Time operator+(const Time& x, const Time& y)
{
    Time z;
    z.Set(x.days + y.days, x.hours + y.hours,
        x.minutes + y.minutes, x.seconds + y.seconds);
    return z;
}

Time operator-(const Time& x, const Time& y)
{
    Time z;
    z.Reduce(x.days - y.days, x.hours - y.hours,
        x.minutes - y.minutes, x.seconds - y.seconds);
    return z;
}

Time& Time::operator++() //pre
{
    Set(days, hours, minutes, ++seconds);
    return *this;
}

Time Time::operator++(int) // post
{
    Time temp = *this;
    Set(days, hours, minutes, ++seconds);
    return temp;
}

Time& Time::operator--() // pre (change THEN display changed)
{
    Reduce(days, hours, minutes, --seconds);
    return *this;
}

Time Time::operator--(int) //post (display THEN change)
{
    Time temp = *this;
    Reduce(days, hours, minutes, --seconds);
    return temp;
}

void Time::PrintTwoDigit(ostream& o, int i) const
{
    if (i < 10 && i >= 0)
    {
        o << "0";
    }
    o << i;
}
ostream& operator<<(ostream& o, const Time& t)
{
    o << t.days << "~";
    t.PrintTwoDigit(o, t.hours);
    o << ":";
    t.PrintTwoDigit(o, t.minutes);
    o << ":";
    t.PrintTwoDigit(o, t.seconds);
    return o;
}

istream& operator>>(istream& i, Time& t)
{
    char tChar;
    i >> t.days >> tChar >> t.hours >> tChar >> t.minutes >> tChar >> t.seconds;
    t.Set(t.days, t.hours, t.minutes, t.seconds);
    return i;
}

void Time::Reduce(int d, int h, int m, int s)
{
    while (s < 0) 
    {
        m--;
        s+=60;
    }
    while (m < 0) 
    {
        h--;
        m+=60;
    }
    while (h < 0) 
    {
        d--;
        h+=24;
    }
    if (d < 0)
    {
        Set(0, 0, 0, 0);
        return;
    }
    Set(d, h, m, s);
}
void Time::Set(int d, int h, int m, int s)
{
    if (d < 0 || h < 0 || m < 0 || s < 0)
    {
        seconds = 0;
        minutes = 0;
        hours = 0;
        days = 0;
    }
    while (s > 59)
    {
        m++;
        s -= 60;
    }
    while (m > 59)
    {
        h++;
        m -= 60;
    }
    while (h > 23)
    {
        d++;
        h -= 24;
    }
    seconds = s;
    minutes = m;
    hours = h;
    days = d;
}