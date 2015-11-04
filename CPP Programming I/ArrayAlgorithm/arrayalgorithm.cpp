#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;
void PrintArray (const int arr[], const int size);
void FillArray(int arr[], const int size);
void Insert(int a[], const int size, const int value, const int index);
void Delete(int a[], const int size, int index);
void Reverse(int a[], const int size);
void DisplayMenu();
int HowMany(int a[], const int size, int value);
int SumOdds(int a[], const int size, const int oddCount);

int main(){
	const int SIZE = 15;
	int myArray[SIZE];
	int count = 0;
	memset(myArray, 0, sizeof(myArray));
	char c;
	int inputValue, inputIndex;
	DisplayMenu();
	while (true){
		cout << "Enter your menu selection:";
		cin >> c;
		c = tolower(c);
		switch (c){
		case 'p':
			PrintArray(myArray,SIZE);
			break;
		case 'f':
			FillArray(myArray,SIZE);
			break;
		case 'i':
			cout << "Enter the value for entry: " << endl;
			cin >> inputValue;
			cout << "Enter the position in the array: " << endl;
			cin >> inputIndex;
			Insert(myArray, SIZE, inputValue, inputIndex);
			break;
		case 'd':
			cout << "Enter the position in the array: " << endl;
			cin >> inputIndex;
			Delete(myArray, SIZE, inputIndex);
			break;
		case 'r':
			Reverse(myArray, SIZE);
			break;
		case 'h':
			cout << "Enter the value for entry: " << endl;
			cin >> inputValue;
			count = HowMany(myArray, SIZE, inputValue);
			cout << "The value " << inputValue << " appears in the list " << count << " times" << endl;
			break;
		case 's':
			cout << "How many odd numbers do you want to add?" << endl;
			cin >> inputValue;
			count = SumOdds(myArray, SIZE,inputValue);
			cout << "The sum of the first " << inputValue << " odd numbers is: " << count << endl;
			break;
		case 'm':
			DisplayMenu();
			break;
		case 'q':
		    PrintArray(myArray,SIZE);
			return 0;
		default:
			break;
		}
	}
}
void DisplayMenu()
{
	cout << "      ** Given features  **" << endl
		<< "P      Print the array contents" << endl
		<< "F      Fill the array (user entry)" << endl
		<< endl 
		<< "       ** Function Tests **" << endl
		<< "I      Insert" << endl
		<< "D      Delete" << endl
		<< "R      Reverse" << endl
		<< "H      HowMany" << endl
		<< "S      SumOdds" << endl
		<< endl
		<< "M      Print this menu" << endl
		<< "Q      Quit this program" << endl;
}

void Insert(int a[], const int size, const int value, const int index)
{
	if (index > size - 1)
	{
		return;
	}
	else
	{
		int j = a[index]; //j = 6
		a[index] = value; //a[5] = 100
		for (int i = index; i < size; i++)
		{ 
			int k = a[i+1]; // k = a[6] = 7 // k = a[7] = 8
			a[i+1] = j; //a[6] = 6 // a[7] = 7
			j = k; // j = 7 // j = 8
		}
	}
}

void Delete(int a[], const int size, const int index)
{
	if (index > size - 1)
	{
		return;
	}
	else
	{
		for (int i = index; i < size; i++)
		{
			int j = a[i + 1];
			a[i] = j;
		}
		a[size-1] = 0;
	}
}

void Reverse(int a[], const int size)
{
	int j = 0, k = 0;
	while (k < size - 1)
	{
		k++;
	}
	while(k > j)
	{
		int y = a[j];
		int z = a[k];
		a[j] = z;
		a[k] = y;
		j++;
		k--;
	} 
}

int HowMany(int a[], const int size, int value)
{
	int n = 0;
	for (int i = 0; i < size; i++){
		if (a[i] == value){
			n++;
		}
	}
	return n;
}

int SumOdds(int a[], const int size, const int oddCount)
{
	int sum = 0, m = 0;
	for (int i = 0; i < size; i++)
	{
		if (m < oddCount){
			if (a[i] % 2 != 0)
			{
				m++;
				sum+= a[i];
			}
		}
	}
	return sum;
}

void PrintArray(const int arr[], const int size)
{
	cout << "\nThe array:\n { ";
	for (int i = 0; i < size-1; i++)	// print all but last item
		cout << arr[i] << ", ";

	cout << arr[size-1] << " }\n";	// print last item
}

void FillArray(int arr[], const int size)
{
	cout << "Please enter " << size 
		<< " integers to load into the array\n> ";

	for (int i = 0; i < size; i++)
		cin >> arr[i];			// enter data into array slot
}
