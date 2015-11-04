#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include "song.h"

using namespace std;

Song::Song()
{
    memset(title, 0, 35);
    memset(artist, 0, 21);
    category = POP;
    size = 0;
}

void Song::Set(const char* t, const char* a, Style st, int sz)
{
    strcpy(title, t);
    strcpy(artist, a);
    category = st;
    size = sz;
}

const char* Song::GetTitle() const
{
    return title;
}

const char* Song::GetArtist() const
{
    return artist;
}

int Song::GetSize() const
{
    return size;
}

Style Song::GetCategory() const
{
    return category;
}

void Song::Display() const
{
    cout << setw(36) << left << title;
    cout << setw(21) << left << artist;
    cout << setw(7) << left;
    switch (category)
    {
    case POP: cout << "Pop"; break;
    case ROCK: cout << "Rock"; break;
    case ALTERNATIVE: cout << "Alt";  break;
    case COUNTRY: cout << "Ctry"; break;
    case HIPHOP: cout << "HH"; break;
    case PARODY: cout << "Par"; break;
    } 
    cout << setw(12) << right << setprecision(1) << fixed << size / 1000.0;
    cout << endl;
}
