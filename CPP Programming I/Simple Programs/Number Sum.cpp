#include <iostream>

using namespace std;

int main(){
	int integer;
	int sum = 0;
	bool zeroEntry = false;


	while (!zeroEntry)
	{
		cout << "Please enter an integer (0 to quit):";
		cin >> integer;
		if (integer == 0)
		{
			zeroEntry = true;
		}
		integer = abs(integer);
		while (integer >= 1){
			sum += integer % 10;
			integer /= 10;
		}
		cout << "The sum of the digits is " << sum << endl;
		sum = 0;
	}
	cout << "Goodbye";




	system("pause");
	return 0;
}

/*

#include <iostream>

using namespace std;

int SumDigits(int);

int main(){
int input = 0;
while (true)
{
cout << "Please enter an integer (0 to quit):";
cin >> input;
if(input == 0){
break;
}
cout << "The sum of the digits is " << SumDigits(input) << endl;
}
cout << "Goodbye" << endl;
system("pause");
return 0;
}

int SumDigits(int x){
int sum = 0;
if (x < 0)
x = -x;

while (x > 0){
sum += x % 10;
x /= 10;
}
return sum;
}


*/