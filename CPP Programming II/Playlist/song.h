// Bob Myers
//
// song.h -- header file for the Song class
//
// An object of type Song will store information about a single
// digitally recorded song file.  

// The variable "category" stores the category of the song
//  (one of the six items in the enumerated type Style).

#ifndef _SONG_H
#define _SONG_H

enum Style {POP, ROCK, ALTERNATIVE, COUNTRY, HIPHOP, PARODY};

class Song
{
public:
    Song();// default constructor, sets up blank song object

    void Set(const char* t, const char* a, Style st, int sz);

    // the Set function should allow incoming data to be received through
    //  parameters and loaded into the member data of the object.  (i.e.
    //  this function "sets" the state of the object to the data passed in).
    //  The parameters t, a, st, and sz represent the title, artist, style, 
    //  and size of the song file, respectively.

    const char* GetTitle() const;// returns the title stored in the object
    const char* GetArtist() const;// returns the artist
    int GetSize() const;// returns the file size in kilobytes
    Style GetCategory() const;// returns the song category

    void Display() const;// described below

private:
    char title[36];// may assume title is 35 characters or less
    char artist[21];// may assume artist name is 20 characters or less
    Style category;// style of the given song
    int size;// file size, stored in kilobytes
};

/* Display() function

The member function Display() should print out a Song object on one line 
(use no more than 80 characters per line) as follows, in an organized 
manner. Size should be printed in Megabytes (use 1000 kilobytes = 1 MB 
for this calculation), to 1 decimal place.  The category abbreviations 
used should be: Pop, Rock, Alt, Ctry, HH, Par

Title                   Artist       Style   Size (MB)

Examples:
Pictures of You                    The Cure            Alt       4.4
Bohemian Rhapsody                  Queen               Rock      5.7
What Does the Fox Say              Ylvis               Par      12.6

*/ 

#endif
