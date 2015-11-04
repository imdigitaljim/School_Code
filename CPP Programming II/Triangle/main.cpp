// Bob Myers
// driver.cpp -- driver program to demonstrate the behavior of
//    the Triangle class

#include <iostream>
#include <iomanip>
#include "triangle.h"

using namespace std;

int main() 
{
    // set decimal outputs to 2 decimal places
    cout << setiosflags( ios::fixed | ios::showpoint )
         << setprecision( 2 );

  
    // create some Triangles
    Triangle t1( -5 ), t2( 7, '^' ), t3( 12, 'X', 'O' ), t4( 50 , '$' , 'o');
    // display original Triangles

    cout << "t1 has size = " << t1.GetSize() << " units.\n";
    t1.Draw();
    cout << "\nt2 has size = " << t2.GetSize() << " units.\n";
    t2.Draw();
    cout << "\nt3 has size = " << t3.GetSize() << " units.\n";
    t3.Draw();
    cout << "\nt4 has size = " << t4.GetSize() << " units.\n";
    t4.Draw();
    cout << '\n';

    t1.Shrink(); // demonstrate shrink
    t2.Shrink();
    t3.Grow(); // and grow
    t4.Grow();
    cout << "t1 now has size = " << t1.GetSize() << " units.\n";
    cout << "t2 now has size = " << t2.GetSize() << " units.\n";
    cout << "t3 now has size = " << t3.GetSize() << " units.\n";
    cout << "t4 now has size = " << t4.GetSize() << " units.\n";

    // demonstrate perimeter
    cout << "t2 has perimeter = " << t2.Perimeter() << " units.\n"; 
    cout << "t3 has perimeter = " << t3.Perimeter() << " units.\n"; 
    // and area
    cout << "t2 has area = " << t2.Area() << " square units.\n\n"; 
    cout << "t3 has area = " << t3.Area() << " square units.\n\n"; 

    t1.Draw();
    t1.Grow();               // show that fill character
    cout << "t1 grows:\n";   // appears only when size
    t1.Draw();               // is at least 3
    t1.Grow();
    cout << "... and grows:\n";
    t1.Draw();
    cout << '\n';

    t1 = t2; // demonstrate the default overload of the
    // assignment operator
    cout << "t1 now has size = " << t1.GetSize() << " units.\n";
    t1.Draw(); 

    // demonstrate the changing of border and fill characters
    t2.SetBorder('@');
    t2.SetFill('-');
    cout << "t2 now looks like:\n";
    t2.Draw();
    cout << '\n';
    t2.SetBorder('\n'); // illegal border
    t2.SetFill('\a'); // illegal fill
    cout << "t2 now looks like:\n";
    t2.Draw();
    cout << '\n';

    cout << "\nHere is a summary on t3:\n"; // demonstrate summary
    t3.Summary();

    cin.get();
    return 0;
}
