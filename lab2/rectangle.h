//C435071 김수정

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>


class Rectangle {
public:
    Rectangle(int x=0, int y=0, int h=0, int w=0); // constructor
    ~Rectangle(); // destructor
    void Print();
    int Area();
    bool LessThan(Rectangle&); // 면적이 작으면 true
    bool EqualSize(Rectangle&); // 면적이 동일하면 true
    bool Equal(Rectangle&); // 교재의 Equal (모든 멤버가 동일하면 true)
    int GetHeight();
    int GetWidth();
    bool operator<(Rectangle&); // 면적이 작으면 true
    bool operator==(Rectangle&); // 면적이 같으면 true
    friend std:: ostream & operator<<(std::ostream&, Rectangle&);
private:
    int xLow, yLow, height, width;
};

#endif