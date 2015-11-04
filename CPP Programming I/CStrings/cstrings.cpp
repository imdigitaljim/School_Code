#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>

using namespace std;

int VowelCount(const char[]);
int ConsonantCount(const char[]);
void LowerCase(char[]);
void UpperCase(char[]);
void DisplayMenu();
int main()
{

	char userSelection;

	char text[99];
	cout << "Input a line of text, up to 100 characters:" << endl;
	cin.getline(text, 99);
	DisplayMenu();
	while (true)
	{
		cout << endl << "Enter your menu selection: ";  
		cin >> userSelection;
		cin.ignore(); // ignores the newline /n left after cin >> userSelection 
		//so the next getline can properly run

		switch (toupper(userSelection)){

		case 'A': 
			cout << "The number of vowels: "<< VowelCount(text) << endl;
			break;
		case 'B':
			cout << "The number of consonants: " << ConsonantCount(text) << endl;
			break;
		case 'C':
			UpperCase(text);
			break;
		case 'D':
			LowerCase(text);
			break;
		case 'E':
			cout << "The string:" << endl << text;
			break;
		case 'F':
			cout << "Input a line of text, up to 100 characters:" << endl;
			cin.getline(text, 99);
			break;
		case 'M':
			DisplayMenu();
			break;
		case 'X':
			cout << "Goodbye" << endl;
			return false;
		default:
			break;

		}
	}
}


int VowelCount(const char a[])
{
	int vowel = 0;

	for (size_t i = 0; i < strlen(a); i++) // size_t for array related counters ie from the strlen
	{
		char c = toupper(a[i]);
		if (c == 'A')
		{
			vowel++;
		}
		else if (c == 'E')
		{
			vowel++;
		}
		else if (c == 'I')
		{
			vowel++;
		}
		else if (c == 'O')
		{
			vowel++;
		}
		else if (c == 'U')
		{
			vowel++;
		}
	}

	return vowel;
}

int ConsonantCount(const char a[])
{
	int consonant = strlen(a);
	for (size_t i = 0; i < strlen(a); i++)
	{
		char c = toupper(a[i]);
		if (!isalpha(c))
		{
			consonant--;
		}
		else if (c == 'A')
		{
			consonant--;
		}
		else if (c == 'E')
		{
			consonant--;
		}
		else if (c == 'I')
		{
			consonant--;
		}
		else if (c == 'O')
		{
			consonant--;
		}
		else if (c == 'U')
		{
			consonant--;
		}

	}

	return consonant;
}

void LowerCase(char a[])
{
	for (size_t i = 0; i < strlen(a); i++)
	{
		a[i] = tolower(a[i]);
	}

}

void UpperCase(char a[])
{
	for (size_t i = 0; i < strlen(a); i++)
	{
		a[i] = toupper(a[i]);
	}
}

void DisplayMenu()
{
	cout << "A)  Count the number of vowels in the string"  << endl
		<< "B)  Count the number of consonants in the string" << endl
		<< "C)  Convert the string to uppercase" << endl
		<< "D)  Convert the string to lowercase" << endl
		<< "E)  Display the current string" << endl
		<< "F)  Enter another string" << endl
		<< endl
		<< "M)  Display this menu" << endl
		<< "X)  Exit the program" << endl;
}

