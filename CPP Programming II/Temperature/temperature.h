#ifndef _H_MYTEMP_
#define _H_MYTEMP_

class Temperature {
public:

    Temperature();
    Temperature(double, char);
    void Input();
    void Show() const;
    void Increment(int, char);

    bool SetFormat(char);
    bool Set(double, char);
    bool Convert(char);

    double GetDegrees() const;
    char GetScale() const;
    int Compare(const Temperature&) const;

private:

    double DegreesInKelvin() const;
    char format;
    char scale;
    double temperature;

};




#endif
