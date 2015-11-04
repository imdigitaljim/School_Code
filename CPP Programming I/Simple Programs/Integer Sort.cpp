#include <iostream>

using namespace std;

int main(){

	int integerOne;
	int integerTwo;
	int integerThree;

	cout << "Input integer 1:";
	cin >> integerOne;
	cout << "Input integer 2:";
	cin >> integerTwo;
	cout << "Input integer 3:";
	cin >> integerThree;


	if (integerOne <= integerTwo && integerOne <= integerThree)
	{
		cout << integerOne << " <= ";
		if (integerTwo <= integerThree)
		{
			cout << integerTwo << " <= " << integerThree;
		}
		else{
			cout << integerThree << " <= " << integerTwo;
		}

	}
	if (integerTwo <= integerOne && integerTwo <= integerThree)
	{
		cout << integerTwo << " <= ";
		if (integerOne <= integerThree)
		{
			cout << integerOne << " <= " << integerThree;
		}
		else{
			cout << integerThree << " <= " << integerOne;
		}

	}



	if (integerThree <= integerTwo && integerThree <= integerOne)
	{
		cout << integerThree << " <= ";
		if (integerOne <= integerTwo)
		{
			cout << integerOne << " <= " << integerTwo;
		}
		else {
			cout << integerTwo << " <= " << integerOne;
		}
	}





	cin >> integerOne;
	return 0;
}