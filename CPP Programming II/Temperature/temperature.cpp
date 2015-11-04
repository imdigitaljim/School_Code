#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include "temperature.h"

using namespace std;


Temperature::Temperature()
{
    format = 'D';
    Set(0,'C');
}

Temperature::Temperature(double t, char s)
{
    format = 'D';
    if (!Set(t, s))
    {
        Set(0,'C');
    }
}

void Temperature::Input()
{
    double tempIn;
    char scaleIn;
    cout << "Input Temperature (degrees scale): ";
    cin >> tempIn >> scaleIn;
    cout << endl;
    while (!Set(tempIn,scaleIn))
    {
        cout << "Invalid Temperature. Try again:";       
        cout << endl;
        cin >> tempIn >> scaleIn;
    }
}

void Temperature::Show() const
{
    streamsize ss = cout.precision();
    switch(format)
    {
    case 'L':
        cout << temperature << " "; 
        if (scale == 'C')
        {
            cout << "Celsius";
        }
        else if (scale == 'F')
        {
            cout << "Fahrenheit";
        }
        else if (scale == 'K')
        {
            cout << "Kelvin";
        }
        break;
    case 'P':
        cout << fixed << setprecision(1) << temperature << " " << scale;
        break;
    default:
        cout  <<  temperature << " " << scale;
        break;
    }
    cout << resetiosflags(ios::fixed) << setprecision(ss) << endl;
}

void Temperature::Increment(int i, char s)
{
    if (i > 0)
    {
        char originalScale = scale;
        Convert(s);
        Set(temperature + i, s);
        Convert(originalScale);
    }
}

bool Temperature::SetFormat(char f)
{
    char newFormat = toupper(f);
    if (newFormat == 'D' || newFormat == 'P' || newFormat == 'L')
    {
        format = newFormat;
        return true;
    }
    return false;
}

bool Temperature::Set(double t, char s)
{
    switch (toupper(s))
    {
    case 'F':
        if (t < -459.67)
        {
            return false;    
        }
        break;
    case 'C':
        if (t < -273.15)
        {
            return false;
        }
        break;
    case 'K':
        if (t < 0)
         {
             return false;
         }   
        break;
    default:
        return false;
    }
    scale = toupper(s);
    temperature = t;
    return true;

}

bool Temperature::Convert(char s)
{
    switch (toupper(s))
    {
    case 'C':                      
        if (scale == 'F')
        {
            temperature = (temperature - 32) * 5 / 9;
        }
        else if (scale == 'K')
        {
            temperature -= 273.15;
        }
        break;
    case 'F':
        if (scale == 'C')
        {
            temperature = (temperature * 1.8) + 32; 
        }
        else if (scale == 'K')
        {
            temperature = (temperature - 273.15) * 1.8 + 32;
        }
        break;
    case 'K':
        temperature = DegreesInKelvin();
        break;
    default:
        return false;
    }
    scale = toupper(s);
    return true;
}

double Temperature::GetDegrees() const
{
    return temperature;
}

char Temperature::GetScale() const
{
    return scale;
}

double Temperature::DegreesInKelvin() const
{
    double conversion = temperature;
    if (scale == 'C')
    {
        conversion = temperature + 273.15;
    }
    else if (scale == 'F')
    {
        conversion = ((temperature - 32) / 1.8) + 273.15;
    }
    return conversion;
}

int Temperature::Compare(const Temperature& t) const
{
    //if the parameter is colder return 1;
    //if the caller is colder return -1;
    //else equal
    if (t.DegreesInKelvin() < DegreesInKelvin())
    {
        return 1;
    }
    else if (t.DegreesInKelvin() > DegreesInKelvin())
    {
        return -1;
    }
    else 
    {
        return 0;
    }
}

