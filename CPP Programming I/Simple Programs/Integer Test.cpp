#include <iostream>

using namespace std;

int main(){
	int intOne;
	int intTwo;
	bool oneBig = true;
	int sum = 0;

	cout << "Input two integers:\nInteger One: ";
	cin >> intOne;
	cout << "Integer Two: ";
	cin >> intTwo;

	if (intTwo > intOne){
		oneBig = false;
	}

	if (oneBig == true){

		for (int i = intTwo; i < intOne; i++){
			cout << i << " + ";
			sum = sum + i;
		}
		sum = sum + intOne;
		cout << intOne << " = " << sum;
	}

	else {
		for (int i = intOne; i < intTwo; i++){
			cout << i << " + ";
			sum = sum + i;
		}
		sum = sum + intTwo;
		cout << intTwo << " = " << sum;

	}




	cin.ignore();
	cin.get();
	return 0;
}