//   bitarray.h
//
//   BitArray class declaration

#ifndef _BITARRAY_H
#define _BITARRAY_H

#include <iostream>
using namespace std;

class BitArray
{
   friend ostream& operator<< (ostream&, const BitArray&);
   friend bool operator== (const BitArray&, const BitArray&);
   friend bool operator!= (const BitArray&, const BitArray&);

public:
   BitArray(unsigned int);      // Construct a vector with specified length
   BitArray(const BitArray&);   // copy constructor
   ~BitArray();                 // destructor

   BitArray& operator= (const BitArray& a);  // assignment operator

   unsigned int Length() const;      // return length of bitvector

   void Set   (unsigned int);        // make bit = 1
   void Unset (unsigned int);        // make bit = 0
   void Flip  (unsigned int);        // change bit value
   bool Query (unsigned int) const;  // return bit value

private:
   unsigned char* barray;			// pointer to the bit array
   int arraySize;
   int Mask(unsigned int) const;
   const int charSize;
};

#endif
