#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){

	int daysWorked;
	double earning;
	double salary = 0;

	cout << "Please enter the number of days worked: ";
	cin >> daysWorked;

	cout << "Day             Amount Earned" << endl
		<< "--------------------------------------" << endl;

	for (int i = 0; i < daysWorked; i++){
		earning = pow(2, i) * .01;
		if (i < 9){
			cout << i + 1 << setw(17) << "$ " <<
				fixed << setprecision(2) << earning << endl;
		}
		else {
			cout << i + 1 << setw(16) << "$ " <<
				fixed << setprecision(2) << earning << endl;

		}

		salary += earning;

		
	}



	cout << endl << "Total earnings: $ " << setprecision(2) << salary << endl;

	system("pause");
	return 0;
}