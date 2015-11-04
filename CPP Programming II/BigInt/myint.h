#ifndef _H_MYINT
#define _H_MYINT
#include <iostream>

using namespace std;

class MyInt
{
    friend ostream& operator<<(ostream&, const MyInt&);
    friend istream& operator>>(istream&, MyInt&);
    friend bool operator>(const MyInt&, const MyInt&);
    friend bool operator<(const MyInt&, const MyInt&);
    friend bool operator>=(const MyInt&, const MyInt&);
    friend bool operator<=(const MyInt&, const MyInt&);
    friend bool operator==(const MyInt&, const MyInt&);
    friend bool operator!=(const MyInt&, const MyInt&);
    friend MyInt operator+(const MyInt&, const MyInt&);
    friend MyInt operator-(const MyInt&, const MyInt&);
    friend MyInt operator*(const MyInt&, const MyInt&);
    friend MyInt operator/(const MyInt&, const MyInt&);
    friend MyInt operator%(const MyInt&, const MyInt&);

public:
    MyInt(int n = 0);// first constructor
    MyInt(const char*);
    MyInt(const MyInt&);  
    ~MyInt();
  
    MyInt& operator= (const MyInt&);
    MyInt& operator++();
    MyInt operator++(int);
private:
    void Divide(const MyInt&, MyInt&, MyInt&) const;
    void Resize();
    void TrimZero();
    int currentSize;
    int maxSize;
    char* myInteger;
};

#endif
