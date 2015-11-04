#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include "playlist.h"

using namespace std;

Playlist::Playlist()
{
    currentSize = 0;
    maxSize = 5;
    songlist = new Song[maxSize];
}

Playlist::~Playlist()
{
    delete[] songlist;
}

void Playlist::Display() const
{
    cout << endl;
    if (currentSize == 0)
    {
        cout << "No songs currently in playlist" << endl;        
    }
    else 
    {
        cout << "*Title*                             ";
        cout << "*Artist*             *Style*   *Size (MB)*";
        cout << endl << endl;
        for (int i = 0; i < currentSize; i++)
        {
            songlist[i].Display();
        }
    }
    cout << endl;
    cout << "Number of songs = " << currentSize << endl;
    cout << "Total playlist size = ";
    cout << fixed << setprecision(2) << GetPlaylistSize()/1000.0;
    cout << " MB" << endl << endl;
}

void Playlist::Search(const char* search) const
{
    bool foundResults = false;
    cout << endl;
    for (int i = 0; i < currentSize; i++)
    {
        if (strcmp(songlist[i].GetArtist(), search) == 0 || strcmp(songlist[i].GetTitle(), search) == 0) 
        {
            if (!foundResults && strcmp(songlist[i].GetTitle(), search) == 0)
            {
                cout << "Song Found:" << endl;
            }
            songlist[i].Display();
            foundResults = true;
        }
    }
    if (!foundResults)
    {
        cout << endl << search << ": Not Found" << endl;
    }
    cout << endl;
}   

void Playlist::Display(const Style style) const
{
    int catSize = 0;
    int catCount = 0;
    cout << endl;
    for (int i = 0; i < currentSize; i++)
    {
        if (songlist[i].GetCategory() == style)
        {
            songlist[i].Display();
            catSize += songlist[i].GetSize();
            ++catCount;
        }
    }
    cout << endl;
    cout << "Total songs in this category = " << catCount << endl;
    cout << "Total file size = ";
    cout << fixed << setprecision(2) << catSize / 1000.0;
    cout << " MB" << endl << endl;
}
void Playlist::Add(const char* title, const char* artist, const Style style, const int size) 
{
    if (currentSize >= maxSize)
    {
        ResizeList(maxSize + 5);
    }
    songlist[currentSize].Set(title, artist, style, size);
    currentSize += 1;
}

void Playlist::Sort(const char sorttype)
{
    Song temp;
    char temp1[36];
    char temp2[36];
    for (int i = 0; i < currentSize - 1; i++)
    {
        for (int j = 0; j < currentSize - 1; j++)
        {
            if (sorttype == 'T')
            {
                strcpy(temp1, songlist[j].GetTitle());
                strcpy(temp2, songlist[j + 1].GetTitle());
            }
            else if (sorttype == 'A')
            {
                strcpy(temp1, songlist[j].GetArtist());
                strcpy(temp2, songlist[j + 1].GetArtist());
            }
            if (strcmp(temp1,temp2) > 0)
            {
                temp = songlist[j];
                songlist[j] = songlist[j + 1];
                songlist[j + 1] = temp;
            }
        }
    }
    cout << endl << "Sort complete" << endl << endl;
}

bool Playlist::Delete(const char* songtitle)
{
    for (int i = 0; i < currentSize; i++)
    {
        if (strcmp(songlist[i].GetTitle(), songtitle) == 0)
        {
           
            for (int j = i; j < currentSize; j++)
            {
                songlist[j] = songlist[j + 1]; 
            }
            if (currentSize <= maxSize - 5)
            {
                ResizeList(maxSize - 5);
            }
            currentSize -= 1;
            return true;
        }
    }
    return false;
}

int Playlist::GetPlaylistSize() const
{
    int sum = 0;
    for (int i = 0; i < currentSize; i++)
    {
        sum += songlist[i].GetSize();
    }
    return sum;
}

void Playlist::ResizeList(int listsize)
{
    maxSize = listsize;
    cout << endl << "** Array being resized to " << maxSize << " allocated slots" << endl;
    Song* temp = new Song[maxSize];
    for (int i = 0; i < currentSize; i++)
    {
        temp[i] = songlist[i];
    }
    delete[] songlist;
    songlist = temp;
}
