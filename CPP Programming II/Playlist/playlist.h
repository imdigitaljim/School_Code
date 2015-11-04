#ifndef _H_MYPLAYLIST_
#define _H_MYPLAYLIST_
#include "song.h"

class Playlist
{

public:
    Playlist();
    ~Playlist();

    void Search(const char*) const; //provides a display from the given information
    void Display(const Style) const;
    void Display() const;
    void Add(const char*, const char*, const Style, const int); //adds song entries
    void Sort(const char);
    bool Delete(const char*); //removes song entries
    int GetPlaylistSize() const; //returns the playlist size;

private:
    void ResizeList(int);
    Song* songlist;
    int maxSize;
    int currentSize;
};
#endif
