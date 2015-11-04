#ifndef _SIEVE_H
#define _SIEVE_H

#include <cmath>
#include "bitarray.h"

using namespace std;

void Sieve(BitArray& bit) // 1 is prime; 0 is not
{
    int length = bit.Length();
    int square = ceil(sqrt(length));
    for (int i = 0; i < length; i++)
    {
        bit.Set(i);
    }
    bit.Unset(0);
    bit.Unset(1);
    for (int i = 2; i <= square; i++)
    {
        if (bit.Query(i))
        {
            for (int j = i * i; j < length; j+= i)
            {
                bit.Unset(j);
            }
        }
    }
};

#endif