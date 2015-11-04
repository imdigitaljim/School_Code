// Sample main program to test a few Distance class features
//  Write your own calls to test more thoroughly!!
// Author:  Bob Myers

#include <iostream>
#include "distance.h"

using namespace std;

int main()
{
    Distance d1(1,6,0,9), d2(2,5,2,7), d3(1234567), d4(1,1,1,1), d5(1,500,2,5);
    cout << "d1 = " << d1 << '\n';
    cout << "d2 = " << d2 << '\n';
    cout << "d3 = " << d3 << '\n';
    cout << "d4 = " << d4 << '\n';
    cout << "d5 = " << d5 << '\n';


    cout << "\n\n"; 
    cout << d1 << " + " << d2 << " = " << d1 + d2 << '\n';
    cout << d1 << " - " << d2 << " = " << d1 - d2 << "\n\n";

    if (d1 < d2) cout << d1 << " <  " << d2 << " is TRUE\n";
    if (d1 > d2) cout << d1 << " >  " << d2 << " is TRUE\n";
    if (d1 <= d2) cout << d1 << " <= " << d2 << " is TRUE\n";
    if (d1 >= d2) cout << d1 << " >= " << d2 << " is TRUE\n";
    if (d1 == d2) cout << d1 << " == " << d2 << " is TRUE\n";
    if (d1 != d2) cout << d1 << " != " << d2 << " is TRUE\n\n";

    cout << d5 << " * 3 = " << d5 * 3 << '\n';
    cout << d5 << " * 5 = " << d5 * 5 << '\n';

    cout << "Enter first Distance object (MILES,YDS,FT,IN):  ";
    cin >> d1;

    cout << "Enter second Distance object (MILES,YDS,FT,IN):  ";
    cin >> d2;

    if (d1 < d2) cout << d1 << " <  " << d2 << " is TRUE\n";
    if (d1 > d2) cout << d1 << " >  " << d2 << " is TRUE\n";
    if (d1 <= d2) cout << d1 << " <= " << d2 << " is TRUE\n";
    if (d1 >= d2) cout << d1 << " >= " << d2 << " is TRUE\n";
    if (d1 == d2) cout << d1 << " == " << d2 << " is TRUE\n";
    if (d1 != d2) cout << d1 << " != " << d2 << " is TRUE\n\n";

    cout << "Enter first Distance object (MILES,YDS,FT,IN):  ";
    cin >> d1;

    cout << "Enter second Distance object (MILES,YDS,FT,IN):  ";
    cin >> d2;


    if (d1 < d2) cout << d1 << " <  " << d2 << " is TRUE\n";
    if (d1 > d2) cout << d1 << " >  " << d2 << " is TRUE\n";
    if (d1 <= d2) cout << d1 << " <= " << d2 << " is TRUE\n";
    if (d1 >= d2) cout << d1 << " >= " << d2 << " is TRUE\n";
    if (d1 == d2) cout << d1 << " == " << d2 << " is TRUE\n";
    if (d1 != d2) cout << d1 << " != " << d2 << " is TRUE\n\n";

    cout << "d1++ = " << d1++ << '\n';
    cout << "d2-- = " << d2-- << '\n';
    cout << "d1 = " << d1 << '\n';
    cout << "d2 = " << d2 << '\n';

    cout << "++d1 = " << ++d1 << '\n';
    cout << "--d2 = " << --d2 << '\n';
    cout << "d1 = " << d1 << '\n';
    cout << "d2 = " << d2 << '\n';
     
     
}
