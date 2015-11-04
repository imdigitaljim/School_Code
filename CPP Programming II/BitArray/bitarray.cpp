#include <iostream>
#include <cmath>
#include "bitarray.h"

using namespace std;

ostream& operator<< (ostream& os, const BitArray& a)
{
    int length = a.Length();
    os << "(";
    for (int i = 0; i < length; i++)
    {
        os << a.Query(i);
    }
    os << ")";
    return os;
}

bool operator== (const BitArray& x, const BitArray& y)
{
    if (x.arraySize != y.arraySize)
    {
        return false;
    }
    else 
    {
        for (int i = 0; i < x.arraySize; i++)
        {
            if (x.barray[i] != y.barray[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool operator!= (const BitArray& x, const BitArray& y)
{
    return !(x == y);
}

BitArray::BitArray(unsigned int x) : charSize(sizeof(unsigned char) * 8)
{
    arraySize = ceil(x / (1.0 * charSize));
    barray = new unsigned char[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        barray[i] = 0;
    }
}

BitArray::BitArray(const BitArray& x) : charSize(sizeof(unsigned char) * 8)
{
    arraySize = x.arraySize;
    barray = new unsigned char[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        barray[i] = x.barray[i];
    }
}

BitArray::~BitArray()
{
    delete[] barray;
}

BitArray& BitArray::operator=(const BitArray& x)
{
    if (this != &x)
    {
        delete[] barray;
        arraySize = x.arraySize;
        barray = new unsigned char[arraySize];
        for (int i = 0; i <= arraySize; i++)
        {
            barray[i] = x.barray[i];
        }
    }
    return *this;
}

unsigned int BitArray::Length() const
{
    return arraySize * (charSize);
}

void BitArray::Set(unsigned int index) // == 1 
{
    barray[index / (charSize)] |= (Mask(index));
}

void BitArray::Unset(unsigned int index) // == 0
{
    barray[index / (charSize)] &= ~(Mask(index));  
}

/*

0010 1111 barray
0000 0001 1
0000 1000 1<<shift
1111 0111 ~(1<<shift)

0010 1111
1111 0111 &
0010 0111

*/

void BitArray::Flip(unsigned int index) 
{
    barray[index / (charSize)] ^= (Mask(index));
}

bool BitArray::Query(unsigned int index) const
{
    return barray[index / (charSize)] & (Mask(index)); 
}

int BitArray::Mask(unsigned int index) const
{
    return 1 << index % (charSize);
}
