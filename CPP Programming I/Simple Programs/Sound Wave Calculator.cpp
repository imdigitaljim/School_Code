#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


int main(){

	// Medium  Speed
	//Air 1,100 feet per second
	//Water 4,900 feet per second
	//Steel 16,400 feet per second

	double soundWave;
	char selection;
	const int a = 1100;
	const int w = 4900;
	const int s = 16400;
	double travelSpeed;
	string question = "How far will the sound wave travel (in feet)?";
	string response = "The sound wave will travel ";
	cout << "\nWelcome to Sound Wave Calculator\n\nSelect the medium the sound wave will travel through.\n\tA\tAir\n\tW\tWater\n\tS\tSteel\n";

	cin >> selection;
	selection = tolower(selection);
	if (selection == 'a' || selection == 'w' || selection == 's'){


		//fixed means it wont be scientific notation
		//setfill 0 means it will show 0's still in the rounding
		//setw(int) <= setwidth 
		//setw('0') <= setting width 48 spaces because char 0 is #48
		// you can use ints to define a char using ascii table
		// char x = '0' + '0' + 1;
		// x would be a from 97 in ascii
		switch (selection){
		case 'a':
			cout << question;
			cin >> soundWave;
			travelSpeed = soundWave / a ;
			cout << response << fixed << setprecision(4) << setfill('0') << travelSpeed << " seconds.";
			break;
		case 'w':
			cout << question;
			cin >> soundWave;
			travelSpeed = soundWave / w ;
			cout << response << fixed << setprecision(4) << setfill('0') << travelSpeed << " seconds.";

			break;

		case 's':
			cout << question;
			cin >> soundWave;
			travelSpeed = soundWave / s;
			cout << response << fixed << setprecision(4) << setfill('0') << travelSpeed << " seconds.";

			break;

		}
	}
	else {
		cout << "Illegal Entry.. Aborting Program.";
	}
	cin >> soundWave;


}