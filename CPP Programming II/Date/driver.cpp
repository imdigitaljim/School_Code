/////////////////////////////////////////////////////////
// Bob Myers
//
// sample.cpp -- sample test program starter for Date class
/////////////////////////////////////////////////////////

#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    Date d1(5, 17, 2002);
    Date d2(12, 31, 2000); // should default to 1/1/2000
    d1.Show();
    d1.SetFormat('J');
    d1.Show();
    cout << endl;
    d2.Show();
    d2.SetFormat('J');
    d2.Show();

    // display dates to the screen



    cin.get();
    cin.get();
}