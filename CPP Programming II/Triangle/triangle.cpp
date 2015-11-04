#include <iostream>
#include <iomanip>
#include <cmath>
#include "triangle.h"

using namespace std;

Triangle::Triangle(int len, char b, char f)
{
    if (len < 1)
    {
         len = 1;
    }
    else if (len > 39)
    {
        len = 39;
    }
    length = len;
    SetFill(f);
    SetBorder(b);
}

void Triangle::Grow()
//increase the size of the triangle by 1
{
    if (length < 39)
    {
        ++length;
    }
}


void Triangle::Shrink()
//decrease the size of the triangle by 1
{
    if (length > 1)
    {
        --length;
    }
}

void Triangle::SetBorder(char b)
//set the border to the character acsii 33 - acsii 126
{
    if (IsGoodAscii(b))
    {
        border = b;
    }
    else
    {
        border = '#';
    }
}

void Triangle::SetFill(char f)
//set the border to the character acsii 33 - acsii 126
{
    if (IsGoodAscii(f))
    {
        fill = f;
    }
    else
    {
        fill = '*';
    }
}

bool Triangle::IsGoodAscii(char input) const
{
    return !(input < '!' || input > '~');
}

int Triangle::GetSize() const
{
    return length;
}

int Triangle::Perimeter() const
{
    return length * 3;
}

double Triangle::Area() const
{
    return pow(length, 2) * sqrt(3) / 4;
}

void Triangle::Draw() const
{
    for (int i = 0; i < length; i++)
    {          
        for (int j = i + 2; j <= length; j++) 
        {
            cout << " ";
        }
        for (int k = 0; k <= i; k++) 
         {
             if  (k == 0 || (i == length - 1 && k != i))
             {
                 cout << border << " ";
             }
             else if (k == i)
             {
                 cout << border;
             }                 
             else 
             {
                 cout << fill << " ";
             }
         }
         cout << endl;
    }
}

void Triangle::Summary() const
{
    cout << "Size of triangle's side = " << length << " units." << endl;
    cout << "Perimeter of triangle = " << Perimeter() << " units." <<  endl;
    cout << "Area of triangle = " << fixed << setprecision(2) <<  Area() << " units." << endl;
    cout << "Triangle looks like:" << endl;
    Draw();
}
