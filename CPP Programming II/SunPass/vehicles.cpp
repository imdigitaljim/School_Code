#define _CRT_SECURE_NO_WARNINGS
#include "vehicles.h"
#include <iostream>


using namespace std;


Vehicle::Vehicle(const char* serial, unsigned int capacity): tollMin(2.00)
{
	int size = strlen(serial);
	serialNumber_ = new char[size + 1];
	strcpy(serialNumber_, serial);
	PassengerCapacity_ = capacity;
	serialNumber_[size] = '\0';
}
Truck::Truck(const char* serial, unsigned int capacity, const char* license) 
    : Vehicle(serial, capacity), truckToll(10.00)
{
	int size = strlen(serial);
	DOTLicense_ = new char[size + 1];
	strcpy(DOTLicense_, license);
	PassengerCapacity_ = capacity;
	DOTLicense_[size] = '\0';
}
Car::Car(const char* serial, unsigned int capacity) : Vehicle(serial, capacity)
{
}
Flatbed::Flatbed(const char* serial, unsigned int capacity, const char* license, float length, float width) 
    : Truck(serial, capacity, license), Plane(length, width)
{
}
Van::Van(const char* serial, unsigned int capacity, const char* license, float length, float width, float height) 
    : Truck(serial, capacity, license), Box(length, width, height)
{
}
Tanker::Tanker(const char* serial, unsigned int capacity, const char* license, float length, float radius)
    : Truck(serial, capacity, license), Cylinder(length, radius)
{

}

Van::~Van()
{
    delete serialNumber_;
    delete DOTLicense_;
    cout << "~Van()";
}
Flatbed::~Flatbed()
{
    delete serialNumber_;
    delete DOTLicense_;
    cout << "~Flatbed()";
}
Tanker::~Tanker()
{
    delete serialNumber_;
    delete DOTLicense_;
    cout << "~Tanker()";
}
Truck::~Truck()
{
    delete serialNumber_;
    delete DOTLicense_;
    cout << "~Truck()";
}
Car::~Car()
{
    delete serialNumber_;
    cout << "~Car()";
}
Vehicle::~Vehicle()
{
    delete serialNumber_;
    cout << "~Vehicle";
}


Car::Car() : Vehicle()
{
}
Tanker::Tanker() : Cylinder(), Truck()
{
}
Van::Van() : Box(), Truck()
{
}
Flatbed::Flatbed() : Plane(), Truck()
{
}
Truck::Truck() : Vehicle(), truckToll(10.00) 
{
    DOTLicense_ = 0;
}
Vehicle::Vehicle() : tollMin(2.00)
{
    serialNumber_ = 0;
    PassengerCapacity_ = 0;
}


VehicleType Vehicle::SnDecode(const char* sn)
{
	switch (sn[0])
    {
    case '1':
        return vehicle;
    case '2':
        return car;
    case '3':
        return truck;
    case '4': 
        return van;
    case '5': 
        return tanker;
    case '6':
        return flatbed;
    default:
        return badSn;
    }
}
const char* Car::ShortName() const
{
    return "CAR";
}
const char* Van::ShortName() const
{
    return "VAN";
}
const char* Truck::ShortName() const
{
    return "TRK";
}
const char* Tanker::ShortName() const
{
    return "TNK";
}
const char* Flatbed::ShortName() const
{
    return "FLT";
}
const char* Vehicle::ShortName() const 
{
    return "UNK";
}
float Van::LoadCapacity() const
{
    return Volume();
}
float Tanker::LoadCapacity() const
{
    return Volume();   
}
float Flatbed::LoadCapacity() const
{
    return Area();
}
float Vehicle::LoadCapacity() const
{
    return 0;
}
const char* Truck::DOTLicense() const
{
    return DOTLicense_;
}
const char* Vehicle::SerialNumber() const
{
    return serialNumber_;
}
unsigned int Vehicle::PassengerCapacity() const
{
    return PassengerCapacity_;
}


float Vehicle::Toll() const
{
    return tollMin;
}
float Truck::Toll() const
{
    return truckToll;
}