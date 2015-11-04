#ifndef _VEHICLE_H
#define _VEHICLE_H
#include "shapes.h"


enum VehicleType {badSn, vehicle, car, truck, van, tanker, flatbed};

class Vehicle
{
    // Destructors in all the classes be virtual ?

    // Destructors ??


public:
    Vehicle();
    Vehicle(const char*, unsigned int);
    virtual ~Vehicle();
    const char* SerialNumber() const; // returns serial number 
    unsigned int PassengerCapacity() const; // returns passenger capacity 
    virtual float LoadCapacity() const; // returns 0
    virtual const char* ShortName() const; // returns "UNK"
    virtual float Toll() const; // returns toll using fee schedule
    static VehicleType SnDecode(const char*);
protected:
    char* serialNumber_;
    unsigned int PassengerCapacity_;
    const double tollMin;
private: 
    Vehicle(const Vehicle&); //Copy Constructor
    Vehicle& operator=(const Vehicle&); //Assignment Operator
};

class Car : public Vehicle
{
public:
    Car();
    Car(const char*, unsigned int);
    virtual ~Car();
    const char* ShortName() const; // returns "CAR"
private:
    Car(const Car&);
    Car& operator=(const Car&);
};

class Truck : public Vehicle
{
public:
    Truck();
    Truck(const char*, unsigned int, const char*);
    virtual ~Truck();
    const char* ShortName() const;  // returns "TRK"
    float Toll() const;  // returns toll using fee schedule
    const char* DOTLicense() const; // returns the license no  
protected: 
    char* DOTLicense_; 
    const double truckToll;
private:
    Truck(const Truck&);
    Truck& operator=(const Truck&);
};


class Van : public Truck, public Box
{
public:
    Van();
    Van(const char*, unsigned int, const char*, float, float, float);
    virtual ~Van();
    float LoadCapacity() const; // returns volume of box  
    const char* ShortName() const;  // returns "VAN"
private: 
    Van(const Truck&);
    Van& operator=(const Van&);
};

class Tanker: public Truck, public Cylinder
{
public:
    Tanker();
    Tanker(const char*, unsigned int, const char*, float, float);
    virtual ~Tanker();
    float LoadCapacity() const; // returns volume of cylinder
    const char* ShortName() const;  // returns "TNK"
private: 
    Tanker(const Tanker&);
    Tanker& operator=(const Tanker&);
};

class Flatbed: public Truck, public Plane
{
public:
    Flatbed();
    virtual ~Flatbed();
    Flatbed(const char*, unsigned int, const char*, float, float);
    float LoadCapacity() const; // returns area of plane
    const char* ShortName() const;  // returns "FLT"
private: 
    Flatbed(const Flatbed&);
    Flatbed& operator=(const Flatbed&);

};


#endif
