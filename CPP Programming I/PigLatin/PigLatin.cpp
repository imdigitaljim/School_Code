#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX = 43;
char* ToPigLatin(char*);
bool IsVowel(const char);

int main()
{
	// creation of 5 character strings, each length MAX
	char word[5][MAX];
	int i;				// loop counter
	cout << "Input 5 words: ";
	for (i = 0; i < 5; i++)
		cin >> word[i];

	cout << "\nPig Latin version of the 5 words:\n";
	for (i = 0; i < 3; i++)
	{
		ToPigLatin(word[i]);
		cout << word[i] << ' ';
	}
	// Note that the above outputs illustrate that the original
	//  string itself has been converted.  The outputs below illustrate
	//  that a pointer to this string is also being returned from the 
	//  function.

	 cout << ToPigLatin(word[3]) << ' '
	<< ToPigLatin(word[4]) << '\n';
	return 0;
}

char* ToPigLatin(char* word)
{
	int wordEnd;
	int consonantEnd;
	char letterMove[MAX];
	char consonants[MAX];

	for (int i = 0; i < MAX; i++)
	{
		if (!isalpha(word[i]))
		{
			wordEnd = i;
			word[i] = ' ';
		}
	}
	if (IsVowel(word[0]) || word[0] == 'y' || word[0] == 'Y')
	{
		word[wordEnd] = 'w';
		word[wordEnd+1] = 'a';
		word[wordEnd+2] = 'y';
	}

	/*
	else
	{
		for (int i = 0; i < wordEnd; i++)
		{
			if (IsVowel(word[i]))
			{
				consonantEnd = i;
				i = wordEnd;
			}
			else 
			{
				consonants[i] = word[i];
			}
		}

		for (int i = 0; i < (wordEnd - consonantEnd); i++)
		{
			letterMove[i] = word[consonantEnd+i];
			word[consonantEnd+i] = consonants[i];
		}

	}
	*/
	return 0;
}

bool IsVowel(const char c)
{
	char letter = toupper(c);
	if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U')
	{
		return true;
	}
	return false;
}

/*
For our purposes, we will use the following as the rules for translation of a word into "Pig Latin":
A word is a consecutive sequence of letters (a-z, A-Z) or apostrophes. 
You may assume that the input to the function will only be a single "word". 
Examples: Zebra , doesn't , apple

If a word starts with a vowel, the Pig Latin version is the original word with "way" added to the end

If a word starts with a consonant, or a series of consecutive consonants, the Pig Latin version transfers all consonants
up to the first vowel to the end of the word, and adds "ay" to the end.

The letter 'y' should be treated as a consonant if it is the first letter of a word, but treated as a vowel otherwise.

If the original word is capitalized, the new Pig Latin version of the word should be capitalized in the first letter 
(i.e. the previous capital letter may not be capitalized any more).

*/