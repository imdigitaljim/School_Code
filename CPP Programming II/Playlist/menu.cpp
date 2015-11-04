#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include "playlist.h"

using namespace std;

void DisplayMenu();
Style GetCategory();

int main()
{
    Playlist myList;

    //temp variables for inputs
    char tempTitle[36];
    char tempArtist[21];
    int tempSize;
    Style tempCategory;
    char menuInput;
    char caseInput;

    cout << "*** Welcome to Playlist Manager ***" << endl;    
    DisplayMenu();

    do{
        cout << "> ";
        cin >> menuInput;
        cin.ignore();
        switch(toupper(menuInput))
        {
        case 'A':  //add song
            cout << "Enter title: ";
            cin.getline(tempTitle, 36);
            cout << "Enter artist: ";
            cin.getline(tempArtist, 21);
            tempCategory = GetCategory();
            cout << "Enter size: ";
            cin >> tempSize;
            while(tempSize <= 0)
            {
                cout << "Must enter a positive size. Please re-enter" << endl;
                cout << "Enter size: ";
                cin >> tempSize;
            }
            myList.Add(tempTitle, tempArtist, tempCategory, tempSize);
            cout << endl;
            break;
        case 'F':  //find song
            cout << "Enter search string (title or artist): ";
            cin.getline(tempTitle, 36); //title or artist
            myList.Search(tempTitle);
            break;
        case 'D':  //delete song
            cout << "Enter title to delete: ";
            cin.getline(tempTitle, 36); //title
            if (myList.Delete(tempTitle))
            {
                cout << endl << "Song removed!" << endl << endl;   
            }
            else
            {
                cout << endl;
                cout << tempTitle << " not found in the playlist" << endl;
                cout << "* No deletion performed *" << endl << endl;
            }
            break;
        case 'S':  //print complete playlist
            myList.Display();
            break; 
        case 'C':  //category specific listing
            tempCategory = GetCategory(); 
            myList.Display(tempCategory);
            break;
        case 'Z':  //print total file storage
            cout << "Total size of playlist = " << myList.GetPlaylistSize() << " kilobytes" << endl << endl;
            break;
        case 'O':  //sort playlist alphabetic OR lexicographic
            cout << "Sort by (T)itle or (A)rtist? > ";
            cin >> caseInput;
            caseInput = toupper(caseInput);
            if (caseInput == 'T' || caseInput == 'A')
            {
                myList.Sort(caseInput);
            }
            else 
            {
                cout << endl << "** Invalid Sort Option" << endl;
            }
            break;
        case 'M':  //reprint menu
            DisplayMenu();
            break;
        case 'X':  //exit program
            cout << endl << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid menu choice. Try again." << endl; 
            break;
        }
    }while(true);
    return 0;
}

void DisplayMenu()
{
    cout << endl;
    cout << "\t\t*** PLAYLIST MENU ***" << endl;
    cout << "\tA \tAdd a song to playlist" << endl;
    cout << "\tF \tFind a song in the playlist" << endl;
    cout << "\tD \tDelete a song" << endl;
    cout << "\tS \tShow the playlist" << endl;
    cout << "\tC \tList songs from one Category" << endl;
    cout << "\tZ \tTotal playlist size" << endl;
    cout << "\tO \tSort playlist" << endl;
    cout << "\tM \tShow this Menu" << endl;
    cout << "\tX \teXit Program" << endl;
}

Style GetCategory()
{
    char input;
    while (true)
    {
        cout << "Enter Category - ";
        cout <<"(P)op, (R)ock, (A)lternative, ";
        cout <<"(C)ountry, (H)iphop, or Parod(Y): ";
        input = cin.get();
        switch (toupper(input))
        {
        case 'P': return POP;    
        case 'R': return ROCK;
        case 'A': return ALTERNATIVE;
        case 'C': return COUNTRY;
        case 'H': return HIPHOP;
        case 'Y': return PARODY;
        default:
            cout << "Invalid Category entry.  Please re-enter" << endl;
            break;
        }   
    }
    return POP;
}

