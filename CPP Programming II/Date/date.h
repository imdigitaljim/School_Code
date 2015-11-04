#ifndef _DATE_H
#define _DATE_H
class Date

{
public:
    Date();
    Date(int, int, int);
    bool SetFormat(char);
    bool Set(int, int, int);
    void Increment(int = 1);
    void Input();

    void Show() const;
    int Compare(const Date&) const;
    int GetMonth() const;
    int GetDay() const;
    int GetYear() const;


private:
    int GetDPM(int, int) const;
    int month;
    int day;
    int year;
    char format;
};

#endif _DATE_H