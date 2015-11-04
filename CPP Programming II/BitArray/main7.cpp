#include <iostream>

using namespace std;

#include "sieve.h"
#include "bitarray.h"

int main()
{
    unsigned int i, max, counter = 0;
    cout << "\nEnter a positive integer for the maximum value: ";
    cin >> max;

    BitArray ba(max);

    Sieve(ba);                    // find the primes (marking the bits)

    cout << "The bit array looks like this (1byte min): " << endl;
    cout << ba << endl;

    cout << "\nPrimes less than " << max << ':' << '\n';
    for (i = 0; i < max; i++)
    {    
        if (ba.Query(i))
        {
            counter++;
            cout << i;
            if (counter % 8 == 0)
            {
                cout << '\n';
                counter = 0;
            }
            else
                cout << '\t';
        }
    }

    cout << "\nGoodbye!\n";
    cin.get();
    cin.get();
    return 0;

}

