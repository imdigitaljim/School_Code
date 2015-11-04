
#include <iostream>
#include <cstring>
#include <cctype>
#include "stack.h"

using namespace std;

int main()
{
    Stack <char> firstHalf;
    char phrase[100];
    char holder;
    bool isPalindrome = true;
    cout << "Please enter a string:" << endl;
    cin.getline(phrase, 100);
    int length = strlen(phrase);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(phrase[i]))
        {
            firstHalf.push(tolower(phrase[i]));
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (isalpha(phrase[i]))
        {
            firstHalf.pop(holder);
            if (holder != tolower(phrase[i]))
            {
                isPalindrome = false;
                break;
            }
        }
    }
    if (isPalindrome)
    {
        cout << endl << endl << '"' << phrase 
            << '"' << " IS a palindrome" << endl;
    }
    else   
    {
        cout << endl << endl << '"' << phrase 
            << '"' << " is NOT a palindrome" << endl;
    }
	cin.get();
    return 0;
}
