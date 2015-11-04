#include <iostream>

using namespace std;

int main() {
	double wallWide;
	double heightRoof;
	double baseRoof;
	double windowWidth;
	double windowHeight;
	

	cout << "How wide is the wall (in feet)?";
	cin >> wallWide;
	cout << "and how high is the wall to the bottom of the roof?";
	cin >> baseRoof;
	cout << "and how high is the wall to the top of the roof?";
	cin >> heightRoof;
	cout << "How wide is the window(in feet)?";
	cin >> windowWidth;
	cout << "and what is the window's height?";
	cin >> windowHeight;
	
	double triangleArea;
	double squareArea;
	double windowArea;
	double paintTotalArea;
	double paintCan;

	paintTotalArea = (wallWide * baseRoof) + .5 * (heightRoof - baseRoof) * wallWide - (windowWidth * windowHeight);
	//Paint Can Utilization = 400 Square Feet 
	paintCan = paintTotalArea / 400;



	cout << "A side wall that is" << endl
		<< " " << wallWide << "' wide and" << endl
		<< " " << baseRoof << "' tall to the roof bottom and" << endl
		<< " " << heightRoof << "'tall to the roof top," << endl
		<< "containing a window that is" << endl
		<< " " << windowWidth << "'wide and" << endl
		<< " " << windowHeight << "'tall," << endl
		<< "has " << paintTotalArea << " square feet of paintable wall" << endl
		<< "and would require " << paintCan << " cans of paint" << endl
		<< "(assuming that each can will cover 400 square feet of wall)." << endl << endl
		<< "Thanks for using Paint Calculator 2013. Goodbye!!" << endl;
	cin.get();
	cin.get();
	return 0;

}