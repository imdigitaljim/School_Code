/////////////////////////////////////////////////////////
// Bob Myers
//
// sample.cpp -- sample test program starter for Temperature class
/////////////////////////////////////////////////////////

#include <iostream>
#include "temperature.h"

using namespace std;

int main()
{
    Temperature t1(0, 'C');
    Temperature t2(-1, 'c');
    Temperature t3(-100, 'C');
    Temperature t4(-273.15, 'C'); // C breaks at -273.15
    Temperature t5(0, 'F'); // F breaks at -459.67
    Temperature t6(-1, 'f');
    Temperature t7(-100, 'F'), t8(-459.67, 'F');
    Temperature t9(0, 'K'), t10(0, 'k'), t11(300, 'K'), t12(5900, 'K'); // K
                                                                          // breaks
                                                                          // at 0
    

    t1.Input();
    // display dates to the screen
    cout << "\nTemperature t1 is: ";
    t1.Show();
    cout << "\nTemperature t2 is: ";
    t2.Show();
    // display dates to the screen
    cout << "\nTemperature t3 is: ";
    t3.Show();
    cout << "\nTemperature t4 is: ";
    t4.Show();
    // display dates to the screen
    cout << "\nTemperature t5 is: ";
    t5.Show();
    cout << "\nTemperature t6 is: ";
    t6.Show();
    // display dates to the screen
    cout << "\nTemperature t7 is: ";
    t7.Show();
    cout << "\nTemperature t8 is: ";
    t8.Show();
    // display dates to the screen
    cout << "\nTemperature t9 is: ";
    t9.Show();
    cout << "\nTemperature t10 is: ";
    t10.Show();
    // display dates to the screen
    cout << "\nTemperature t11 is: ";
    t11.Show();
    cout << "\nTemperature t12 is: ";
    t12.Show();
   cout << "SetFormat=======================================================" << endl;
    t1.SetFormat('D');
    t2.SetFormat('P');
    t3.SetFormat('L');
    t4.SetFormat('s'); 
    t5.SetFormat('D');
    t6.SetFormat('P');
    t7.SetFormat('l');
    t8.SetFormat('s');
    t9.SetFormat('D');
    t10.SetFormat('P');
    t11.SetFormat('L');
    t12.SetFormat('s');

 
   // display dates to the screen
    cout << "\nTemperature t1 is: ";
    t1.Show();
    cout << "\nTemperature t2 is: ";
    t2.Show();
    // display dates to the screen
    cout << "\nTemperature t3 is: ";
    t3.Show();
    cout << "\nTemperature t4 is: ";
    t4.Show();
    // display dates to the screen
    cout << "\nTemperature t5 is: ";
    t5.Show();
    cout << "\nTemperature t6 is: ";
    t6.Show();
    // display dates to the screen
    cout << "\nTemperature t7 is: ";
    t7.Show();
    cout << "\nTemperature t8 is: ";
    t8.Show();
    // display dates to the screen
    cout << "\nTemperature t9 is: ";
    t9.Show();
    cout << "\nTemperature t10 is: ";
    t10.Show();
    // display dates to the screen
    cout << "\nTemperature t11 is: ";
    t11.Show();
    cout << "\nTemperature t12 is: ";
    t12.Show();
   cout << " Convert to F==================================================" << endl;
    t1.Convert('F');
    t2.Convert('F');
    t3.Convert('F');
    t4.Convert('F');
    t5.Convert('F');
    t6.Convert('F');
    t7.Convert('F');
    t8.Convert('F');
    t9.Convert('F');
    t10.Convert('F');
    t11.Convert('F');
    t12.Convert('F');
   
   // display dates to the screen
    cout << "\nTemperature t1 is: ";
    t1.Show();
    cout << "\nTemperature t2 is: ";
    t2.Show();
    // display dates to the screen
    cout << "\nTemperature t3 is: ";
    t3.Show();
    cout << "\nTemperature t4 is: ";
    t4.Show();
    // display dates to the screen
    cout << "\nTemperature t5 is: ";
    t5.Show();
    cout << "\nTemperature t6 is: ";
    t6.Show();
    // display dates to the screen
    cout << "\nTemperature t7 is: ";
    t7.Show();
    cout << "\nTemperature t8 is: ";
    t8.Show();
    // display dates to the screen
    cout << "\nTemperature t9 is: ";
    t9.Show();
    cout << "\nTemperature t10 is: ";
    t10.Show();
    // display dates to the screen
    cout << "\nTemperature t11 is: ";
    t11.Show();
    cout << "\nTemperature t12 is: ";
    t12.Show();
   cout << "  Incrememt by 100 C======================================================" << endl;
    
   t1.Increment(100, 'C');
   t2.Increment(100, 'C');
   t3.Increment(100, 'C');
   t4.Increment(100, 'c');
   t5.Increment(100, 'c');
   t6.Increment(100, 'c');
   t7.Increment(100, 'c');
   t8.Increment(100, 'c');
   t9.Increment(100, 'c');
   t10.Increment(100, 'c');
   t11.Increment(100, 'c');
   t12.Increment(100,  'c');
                                  
   
   // display dates to the screen
    cout << "\nTemperature t1 is: ";
    t1.Show();
    cout << "\nTemperature t2 is: ";
    t2.Show();
    // display dates to the screen
    cout << "\nTemperature t3 is: ";
    t3.Show();
    cout << "\nTemperature t4 is: ";
    t4.Show();
    // display dates to the screen
    cout << "\nTemperature t5 is: ";
    t5.Show();
    cout << "\nTemperature t6 is: ";
    t6.Show();
    // display dates to the screen
    cout << "\nTemperature t7 is: ";
    t7.Show();
    cout << "\nTemperature t8 is: ";
    t8.Show();
    // display dates to the screen
    cout << "\nTemperature t9 is: ";
    t9.Show();
    cout << "\nTemperature t10 is: ";
    t10.Show();
    // display dates to the screen
    cout << "\nTemperature t11 is: ";
    t11.Show();
    cout << "\nTemperature t12 is: ";
    t12.Show();
   cout << " Increment 100 K=====================================================" << endl;
   
   t1.Increment(100, 'K');
   t2.Increment(100, 'K');
   t3.Increment(100, 'K');
   t4.Increment(100, 'K');
   t5.Increment(100, 'K');
   t6.Increment(100, 'K');
   t7.Increment(100, 'K');
   t8.Increment(100, 'K');
   t9.Increment(100, 'K');
   t10.Increment(100, 'K');
   t11.Increment(100, 'K');
   t12.Increment(100, 'K');
                                  
   
   // display dates to the screen
    cout << "\nTemperature t1 is: ";
    t1.Show();
    cout << "\nTemperature t2 is: ";
    t2.Show();
    // display dates to the screen
    cout << "\nTemperature t3 is: ";
    t3.Show();
    cout << "\nTemperature t4 is: ";
    t4.Show();
    // display dates to the screen
    cout << "\nTemperature t5 is: ";
    t5.Show();
    cout << "\nTemperature t6 is: ";
    t6.Show();
    // display dates to the screen
    cout << "\nTemperature t7 is: ";
    t7.Show();
    cout << "\nTemperature t8 is: ";
    t8.Show();
    // display dates to the screen
    cout << "\nTemperature t9 is: ";
    t9.Show();
    cout << "\nTemperature t10 is: ";
    t10.Show();
    // display dates to the screen
    cout << "\nTemperature t11 is: ";
    t11.Show();
    cout << "\nTemperature t12 is: ";
    t12.Show();
   cout << " COMPARE=================================================" << endl;
    cout << t1.GetScale() << " " << t1.GetDegrees() << endl;    
   // display dates to the screen
    cout << "\nTemperature t1 t2 is: ";

    cout << t1.Compare(t2);
    cout << "\nTemperature t2 t1 is: ";
    cout << t2.Compare(t1);
    // display dates to the screen
    cout << "\nTemperature t3 t4 is: ";
    cout << t3.Compare(t4);
    cout << "\nTemperature t4 t3 is: ";
    cout << t4.Compare(t3);
    // display dates to the screen
    cout << "\nTemperature t5 t6 is: ";
    cout << t5.Compare(t6);
    cout << "\nTemperature t6 t5 is: ";
    cout << t6.Compare(t5);
    // display dates to the screen
    cout << "\nTemperature t7 t8 is: ";
    cout << t7.Compare(t8);
    cout << "\nTemperature t8 t7 is: ";
    cout << t8.Compare(t7);
    // display dates to the screen
    cout << "\nTemperature t9 t10 is: ";
    cout << t9.Compare(t10);
    cout << "\nTemperature t10 t9 is: ";
    cout << t10.Compare(t9);
    // display dates to the screen
    cout << "\nTemperature t11 t12 is: ";
    cout << t11.Compare(t12);
    cout << "\nTemperature t12 t11 is: ";
    cout <<  t12.Compare(t11);
    cout << endl <<  "=====================================================" << endl;


}
