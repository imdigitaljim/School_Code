#include <iostream>

using namespace std;

int Seconds(int,int,int);

int main(){

	// array size of 3
	// could alternatively do clock[6] and use for all
	int clockOne[3];
	int clockTwo[3];

	int totalOne;
	int totalTwo;

	cout << "Input first clock time..." << endl
		<< "Hours: ";
	cin >> clockOne[0];
	cout << endl << "Minutes: ";
	cin >> clockOne[1];
	cout << endl << "Seconds: ";
	cin >> clockOne[2];

	cout << endl << "Input second clock time..." << endl
		<< "Hours: ";
	cin >> clockTwo[0];
	cout << endl << "Minutes: ";
	cin >> clockTwo[1];
	cout << endl << "Seconds: ";
	cin >> clockTwo[2];

	totalOne = Seconds(clockOne[0], clockOne[1], clockOne[2]);
	totalTwo = Seconds(clockTwo[0], clockTwo[1], clockTwo[2]);

	cout << "It's been " << totalOne << " seconds since the first clock struck 12:00" << endl;
	cout << "It's been " << totalTwo << " seconds since the first clock struck 12:00" << endl;
	cout << "The two times are " << abs(totalOne - totalTwo) << " seconds apart" << endl;

	system("pause");
		return 0;


}

int Seconds(int h, int m, int s){

	int total;
	if (h < 12){
		total = m * 60 + s;
	}
	else { 
		total = (h - 12) * 3600 + m * 60 + s;

	}
	return total;
}

/*#include <iostream>

using namespace std;

int seconds(int, int, int);
int getClockTime();

int main(){
	cout << "Input first clock time..." << endl;
	int firstClock = getClockTime();
	cout << "Input second clock time..." << endl;
	int secondClock = getClockTime();

	cout << "It's been " << firstClock << " seconds since the first clock struck 12:00" << endl;
	cout << "It's been " << secondClock << " seconds since the second clock struck 12:00" << endl;
	
	int diff = firstClock - secondClock;
	if(diff < 0){
		diff = -diff;
	}
	cout << "The two times are " << diff << " seconds apart." <<endl;
	
	system("pause");
	return 0;
}

int getClockTime(){
	int x, y, z;
	cout << "Hours: ";
	cin >> x;
	cout << "Minutes: ";
	cin >> y;
	cout << "Seconds: ";
	cin >> z;
	return seconds(x, y, z);
}

int seconds(int h, int m, int s){
	return (h % 12) * 3600 + m * 60 + s;
}

*/