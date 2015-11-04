#ifndef _MYSHAPES_H
#define _MYSHAPES_H


class Box
{
public:
    Box();
    Box(float, float, float);
    ~Box();
    float Volume() const;
protected:
    float length_;
    float width_;
    float height_;
    Box(const Box&);
    Box& operator= (const Box&);
};

class Cylinder
{
public:
    Cylinder();
    Cylinder(float, float);
    ~Cylinder();
    float Volume() const;
protected:
    float length_;
    float radius_;
    const double PI;
    Cylinder(const Cylinder&);
    Cylinder& operator= (const Cylinder&);
};

class Plane 
{
public: 
    Plane();
    Plane(float, float);
    ~Plane();
    float Area() const;

protected:
    float length_;
    float width_;
    Plane(const Plane&);
    Plane& operator= (const Plane&);

};

#endif
