#ifndef _H_MYTRIANGLE_
#define _H_MYTRIANGLE_

class Triangle

{
public:
    Triangle(int, char ='#', char ='*');
    void Grow();
    void Shrink();
    void SetBorder(char);
    void SetFill(char);
    
    int Perimeter() const;
    int GetSize() const;

    double Area() const;
    bool IsGoodAscii(char) const;

    void Draw() const;
    void Summary() const;

private:
    int length;// length of a side
    char border; // border character - default #
    char fill; // fill character - default *
};

#endif
