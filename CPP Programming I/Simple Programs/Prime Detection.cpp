#include <iostream>

using namespace std;

bool isPrime(int);


int main(){
	int input;
	int newLine = 0;
	cout << "Please input a positive integer: ";
	cin >> input;
	cout << endl << "The prime numbers less than or equal to "
		<< input << "are:" << endl;

	for (int i = 2; i <= input; i++){

		if (isPrime(i)){
			if (newLine % 8 == 0)
			{
				cout << endl;
			}
			cout << i << "\t";
			newLine++;
			
		}

	}
	cout << endl;
	system("pause");
	return 0;
}

bool isPrime(int p){
	for (int j = 2; j < p; j++){
		if (p%j == 0){
			return false;
		}

	}
	return true;
}
/*
#include <iostream>
#include <iomanip>

using namespace std;

bool isPrime(int);
void printPrime(int, int &);

int main(){
int c = 0;
int input = 0;
cout << "Please input a positive number: ";
cin >> input;
cout << "The prime numbers less than or equal to " << input << " are:" << endl;

if( input > 2){
printPrime(2, c);
}

for(int i = 3; i <= input; i+=2){
if(isPrime(i)){
printPrime(i, c);
if(c % 8 == 0){
cout << endl;
}
}
}
cout << endl;
system("pause");
return 0;
}
void printPrime(int x, int & y){
cout << setw(8) << left << x;
y++;
}

bool isPrime(int x){
// Both of these edge cases are never called for this program
// but this is written to be more general use, as this particular main never calls, 1, 2, or `even` numbers
if(x == 1 || x == 2) // edge case
return true;
if(x % 2 == 0)	// even cases
return false;

for(int i = 3; i < x; i+=2){ // odd cases
if(x % i == 0){
return false;
}
}
return true;
}
*/