#include <iostream>

using namespace std;

int main(){
	int input;
	int posCounter = 0;
	int negCounter = 0;
	int sumTotal = 0;
	int totalCounter = 0;
	double average;
	bool zeroEntry = false;

	while (!zeroEntry)
	{
		cout << "Input integer (0 to stop):";
		cin >> input;
		if (input > 0){
			posCounter++;
			totalCounter++;
			sumTotal += input;
		}
		if (input < 0){
			negCounter++;
			totalCounter++;
			sumTotal += input;
		}
		if (input == 0) {
			zeroEntry = true;
		}
	}

	average = (double)sumTotal / totalCounter;
	cout << "# of negatives = " << negCounter << endl;
	cout << "# of positives = " << posCounter << endl;
	cout << "Sum = " << sumTotal << endl;
	cout << "Average = " << average << endl;

	system("pause");
}



