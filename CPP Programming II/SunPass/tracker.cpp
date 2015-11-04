#include "vehicles.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	bool isActive = true;
	const int unitMax = 100;
	const int idMax = 20;
	char serial[idMax];
	char licenseDOT[idMax];
	unsigned int capacity[4];
	int volume;
	int tonnage = 0;
	double tollsTotal = 0;
	int unitCount = 0;
	int adjustAmount = 0;
	int autoType[7] = { 0 };
	Vehicle *segment[unitMax];
	while (isActive)
	{
		cin >> volume;
		if (volume > unitMax || volume < 1 || unitCount + volume > unitMax)
		{
			isActive = false;
			break;
		}
		adjustAmount = unitCount + volume;
		for (int i = unitCount; i < adjustAmount; i++)
		{
			cin >> serial >> capacity[0];
			switch (segment[i]->SnDecode(serial))
			{
			case vehicle:
				segment[i] = new Vehicle(serial, capacity[0]);
				autoType[0]++;
				tollsTotal += segment[i]->Toll();
				break;
			case car:
				segment[i] = new Car(serial, capacity[0]);
				autoType[1]++;
				tollsTotal += segment[i]->Toll();
				break;
			case truck:
				cin >> licenseDOT;
				segment[i] = new Truck(serial, capacity[0], licenseDOT);
				autoType[2]++;
				tollsTotal += segment[i]->Toll();
				break;
			case van:
				cin >> licenseDOT >> capacity[1] >> capacity[2] >> capacity[3];
				segment[i] = new Van(serial, capacity[0], licenseDOT, capacity[1], capacity[2], capacity[3]);
				tonnage += segment[i]->LoadCapacity();
				autoType[3]++;
				tollsTotal += segment[i]->Toll();
				break;
			case tanker:
				cin >> licenseDOT >> capacity[1] >> capacity[2];
				segment[i] = new Tanker(serial, capacity[0], licenseDOT, capacity[1], capacity[2]);
				tonnage += segment[i]->LoadCapacity();
				autoType[4]++;
				tollsTotal += segment[i]->Toll();
				break;
			case flatbed:
				cin >> licenseDOT >> capacity[1] >> capacity[2];
				segment[i] = new Flatbed(serial, capacity[0], licenseDOT, capacity[1], capacity[2]);
				tonnage += segment[i]->LoadCapacity();
				autoType[5]++;
				tollsTotal += segment[i]->Toll();
				break;
			default:
				segment[i] = new Vehicle(serial, capacity[0]);
				autoType[6]++;
				tollsTotal += segment[i]->Toll();
				break;
			}
			unitCount++;
		}

	}
	cout << endl << "*****Summary*****" << endl << endl;
	cout << "Cars: " << autoType[1] << endl;
	cout << "Vans: " << autoType[3] << endl;
	cout << "Tankers: " << autoType[4] << endl;
	cout << "Flatbeds: " << autoType[5] << endl;
	cout << "Vehicle Decode Errors: " << autoType[6] << endl;
	cout << "Total Segment Trucks: " << autoType[2] + autoType[3] + autoType[4] + autoType[5] << endl;
	cout << "Total Segment Vehicles: " << autoType[0] + autoType[1] + autoType[2] + autoType[3] +
		autoType[4] + autoType[5] + autoType[6] << endl << endl;
	cout << "Total Segment Tonnage: " << setprecision(2) << fixed << tonnage << endl;
	cout << "Total Segment Tolls: " << setprecision(2) << fixed << tollsTotal << endl;
	cout << endl << "*****ALL Vehicle Data*****" << endl << endl;
	for (int i = 0; i < unitCount; i++)
	{
		cout << endl << endl << segment[i]->ShortName() << " " << segment[i]->SerialNumber() << " ";
		cout << segment[i]->PassengerCapacity() << " " << segment[i]->LoadCapacity() << " ";
		cout << segment[i]->Toll() << endl;
		delete segment[i];
	}
	return 0;
}















