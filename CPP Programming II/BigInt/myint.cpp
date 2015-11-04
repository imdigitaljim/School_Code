#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include "myint.h"

using namespace std;

int C2I(char c)
// converts character into integer (returns -1 for error)
{
    if (c < '0' || c > '9')return -1;// error
    return (c - '0');// success
}

char I2C(int x)
// converts single digit integer into character (returns '\0' for error)
{
    if (x < 0 || x > 9)return '\0';// error
    return (static_cast<char>(x) + '0'); // success
}

MyInt::MyInt(int n)
{
    currentSize = 1;
    int temp = n / 10;
    while (temp > 0)
    {
        temp /= 10;
        currentSize += 1;
    }
    maxSize = currentSize + 5;
    myInteger = new char[maxSize];
    memset(myInteger, 0, maxSize);
    if (n > 0)
    {
        for (int i = 0; i < currentSize; i++)
        {
            myInteger[i] = n % 10;
            n /= 10;
        }
    }
    else 
    {
        myInteger[0] = 0;
    }
	TrimZero();
}

MyInt::MyInt(const char* n)
{
    currentSize = strlen(n);
    maxSize = currentSize + 5;
    myInteger = new char[currentSize + 5];
    memset(myInteger, 0, maxSize);
    for (int i = 0; i < currentSize; i++)
    {
        if (!isdigit(n[currentSize - 1 - i]))
        {
            myInteger[0] = 0;
            currentSize = 1;
            Resize();
            break;
        }
        myInteger[i] = C2I(n[currentSize - 1 - i]);
    }
	TrimZero();
}

MyInt::~MyInt()
{
    delete[] myInteger;
}

MyInt::MyInt(const MyInt& n)
{
    currentSize = n.currentSize;
    maxSize = n.maxSize;
    myInteger = new char[maxSize];
    memset(myInteger, 0, maxSize);
    for (int i = 0; i < currentSize; i++)
    {
        myInteger[i] = n.myInteger[i];
    }
}

void MyInt::Resize()
{
    maxSize = currentSize + 5;
    char* temp = new char[maxSize];
    memset(temp, 0, maxSize);
    for (int i = 0; i < currentSize; i++)
    {
        temp[i] = myInteger[i];
    }
    delete[] myInteger;
    myInteger = temp;
}

MyInt& MyInt::operator=(const MyInt& n)
{
    if (this != &n)
    {
        delete[] myInteger;
        currentSize = n.currentSize;
        maxSize = n.maxSize;
        myInteger = new char[maxSize];
        memset(myInteger, 0, maxSize);
        for (int i = 0; i < currentSize; i++)
        {
            myInteger[i] = n.myInteger[i];
        }
    }
       return *this;
}

ostream& operator<<(ostream& out, const MyInt& n)
{
    for (int i = 0; i < n.currentSize; i++)
    {
        out << I2C(n.myInteger[n.currentSize - 1 - i]); 
    }
    return out;
}

istream& operator>>(istream& instream, MyInt& n)
{
    n.currentSize = 0;
    n.Resize();
    while(isspace(instream.peek()))
    {
        instream.ignore();
    }
    while(isdigit(instream.peek()))
    {
        n.currentSize += 1;   
        if (n.currentSize >= n.maxSize)
        {
            n.Resize();
        }
        n.myInteger[n.currentSize - 1] = C2I(instream.get());
    }
    for (int i = 0; i < n.currentSize / 2; i++)
    {
        swap(n.myInteger[i], n.myInteger[n.currentSize - 1 - i]);
    }
    return instream;
}

void MyInt::TrimZero()
{
    while (myInteger[currentSize - 1] == 0 && currentSize > 1) 
    {
        currentSize -= 1;
    }
    Resize();
}

bool operator<(const MyInt& x, const MyInt& y)
{
    if (x.currentSize < y.currentSize)
    {
        return true;
    }
    if (x.currentSize == y.currentSize)
    {
        for (int i = 0; i < x.currentSize; i++)
        {
            if (x.myInteger[x.currentSize - 1 - i] < y.myInteger[y.currentSize - 1 - i])
            {
                return true;
            }
            if (x.myInteger[x.currentSize - 1 - i] > y.myInteger[y.currentSize - 1 - i])
            {
                return false;
            }
        }
    }
    return false;
}

bool operator>(const MyInt& x, const MyInt& y)
{
    return y < x;
}

bool operator>=(const MyInt& x, const MyInt& y)
{
    return !(x < y);
}

bool operator<=(const MyInt& x, const MyInt& y)
{
    return !(y < x);
}

bool operator==(const MyInt& x, const MyInt& y)
{
    return !(x < y) && !(y < x);
}

bool operator!=(const MyInt& x, const MyInt& y)
{
    return !(x == y);
}

MyInt operator+(const MyInt& x, const MyInt& y)
{
    MyInt temp;
    int adder = 0;
    temp.currentSize = 0;  
    while (x.currentSize > temp.currentSize || y.currentSize > temp.currentSize)
    {
        adder /= 10;
        if (x.currentSize > temp.currentSize)
        {
            adder += x.myInteger[temp.currentSize];
        }
        if (y.currentSize > temp.currentSize)
        {
            adder += y.myInteger[temp.currentSize];
        }
        temp.myInteger[temp.currentSize] = adder % 10;
        temp.currentSize++;
        if (temp.currentSize >= temp.maxSize)
        {
            temp.Resize();
        }
        if ((x.currentSize <= temp.currentSize && y.currentSize <= temp.currentSize) && adder / 10 > 0)
        {
            adder /= 10;
            temp.myInteger[temp.currentSize] = adder %10;
            temp.currentSize++;
        }
    }
    temp.TrimZero();
    return temp;
}

MyInt operator-(const MyInt& x, const MyInt& y)
{
    MyInt temp;
    int digit = 0;
    temp.currentSize = 0;
    while (x.currentSize > temp.currentSize || y.currentSize > temp.currentSize)
    {
        //get the digits - starting with least significant
        if (x.currentSize > temp.currentSize)
        {
            digit += x.myInteger[temp.currentSize]; 
        }
        if (y.currentSize > temp.currentSize)
        {
            digit -= y.myInteger[temp.currentSize];
        }
        //analyze the difference
        if (digit >= 0)
        {
            temp.myInteger[temp.currentSize] = digit % 10;
            temp.currentSize++;
            digit = 0;
        }
        //pass the carry
        else 
        {
            temp.myInteger[temp.currentSize] = (digit + 10) % 10;
            digit = -1;
            temp.currentSize++;
        }
        //reset to 0 if negative
        if ((x.currentSize <= temp.currentSize && y.currentSize <= temp.currentSize) && digit == -1)
        {
            temp.myInteger[0] = 0;
            temp.currentSize = 1;
            temp.maxSize = 1;
            break;
        }
        if (temp.currentSize >= temp.maxSize)
        {
            temp.Resize();
        }
    }
    temp.TrimZero();
    return temp;
}

MyInt operator*(const MyInt& x, const MyInt& y)
{
    MyInt temp;
    MyInt temp2;
    temp.currentSize = x.currentSize + y.currentSize;
    temp.Resize();
    memset(temp.myInteger, 0, temp.maxSize);
    int multi = 0;
    for (int i = 0; i <= x.currentSize; i++)
    {
        temp2.currentSize = i;
        temp2.Resize();
        memset(temp2.myInteger, 0, temp2.maxSize);
        for (int j = 0; j <= y.currentSize; j++)
        {
            multi /= 10;
            multi += y.myInteger[j] * x.myInteger[i];
            temp2.myInteger[temp2.currentSize] = multi % 10;
            ++temp2.currentSize;
            if (temp2.currentSize >= temp2.maxSize)
            {
                temp2.Resize();
            }
        }
        temp = temp + temp2;
    }    
    temp.TrimZero();
    return temp;
}

MyInt operator/(const MyInt& x, const MyInt& y)
{
    MyInt q;
    MyInt r;

    if (x == 0 || y == 0 || x < y)
    {
        return q = 0;
    }
    x.Divide(y, q, r);
    for (int i = 0; i < q.currentSize / 2; i++)
    {
        swap(q.myInteger[i], q.myInteger[q.currentSize - 1 - i]);
    }
    q.TrimZero();
    return q;

}

void MyInt::Divide(const MyInt& y, MyInt& q, MyInt& r) const
{
    MyInt temp;
    int counter = y.currentSize;
    int digit = 0;
    q.currentSize = 0;
    temp.currentSize = y.currentSize;
    temp.Resize();
    memset(temp.myInteger, 0, temp.maxSize);
    
    for (int i = 0; i < y.currentSize; i++)
    {
        temp.myInteger[temp.currentSize - 1 - i] = myInteger[currentSize - 1 - i];
    }
    do
    {
        digit = 0;
        while (y * (digit + 1) <= temp)
        {
            ++digit;
            if (digit >= 10)
            {
                digit = 0;
                break;
            } 

        }
        q.myInteger[q.currentSize] = digit;
        temp = temp - (y * digit);
         if (counter < currentSize)
        {
            temp = temp * 10;
            temp.myInteger[0] = myInteger[currentSize - 1 - counter];
        }
 
        ++counter;
        ++q.currentSize;
        
    }while (counter <= currentSize);
    r = temp;
}

MyInt operator%(const MyInt& x, const MyInt& y)
{
    MyInt q;
    MyInt r;
    if (x == 0 || y == 0)
    {
        return r = 0;
    }
    else if (x < y)
    {
        return x;
    }
    x.Divide(y, q, r);
    r.TrimZero();
    return r;
}

MyInt MyInt::operator++(int) // post
{
    MyInt temp = *this;
    *this = *this + 1;
    return temp;
}

MyInt& MyInt::operator++() // pre
{
    *this = *this + 1;
    return *this;
}


