#include "shapes.h"
#include <iostream>
using namespace std;

Box::Box()
{
    length_ = 0;
    width_ = 0;
    height_ = 0;
}

Box::Box(float len, float w, float h)
{
    length_ = len;
    width_ = w;
    height_ = h;
}

Cylinder::Cylinder() : PI(3.14159265359)
{
    radius_ = 0;
    length_ = 0;
}

Cylinder::Cylinder(float len, float r) : PI(3.14159265359)
{
    length_ = len;
    radius_ = r;
}

Plane::Plane()
{
    length_ = 0;
    width_ = 0;
}

Plane::Plane(float len, float w)
{
    length_ = len;
    width_ = w;
}

float Box::Volume() const
{
    return length_ * width_ * height_;
}

float Cylinder::Volume() const
{
    return PI * radius_ * radius_ * length_;
}

float Plane::Area() const
{
    return length_ * width_;
}

Plane::~Plane()
{
    cout << "~Plane()";
}
Box::~Box()
{
    cout << "~Box()";
}

Cylinder::~Cylinder()
{
    cout << "~Cylinder()";
}