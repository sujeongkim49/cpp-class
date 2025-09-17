//C435071 �����

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>


class Rectangle {
public:
    Rectangle(int x=0, int y=0, int h=0, int w=0); // constructor
    ~Rectangle(); // destructor
    void Print();
    int Area();
    bool LessThan(Rectangle&); // ������ ������ true
    bool EqualSize(Rectangle&); // ������ �����ϸ� true
    bool Equal(Rectangle&); // ������ Equal (��� ����� �����ϸ� true)
    int GetHeight();
    int GetWidth();
    bool operator<(Rectangle&); // ������ ������ true
    bool operator==(Rectangle&); // ������ ������ true
    friend std:: ostream & operator<<(std::ostream&, Rectangle&);
private:
    int xLow, yLow, height, width;
};

#endif