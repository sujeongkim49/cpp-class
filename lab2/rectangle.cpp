//C435071 ±è¼öÁ¤

#include <iostream>
#include "rectangle.h"
using namespace std;

Rectangle::Rectangle(int x, int y, int h, int w)
    : xLow(x), yLow(y), height(h), width(w) { }
Rectangle::~Rectangle() {}

void Rectangle::Print() {
    cout << "xLow: " << xLow << ", yLow: " << yLow
         << ", height: " << height << ", width: " << width<<endl;
}
int Rectangle::Area() {
    return height * width;
}
bool Rectangle::LessThan(Rectangle& s) {
    return Area() < s.Area();
}
bool Rectangle::EqualSize(Rectangle& s) {
    return Area() == s.Area();
}
bool Rectangle::Equal(Rectangle& s) {
    return (xLow == s.xLow) && (yLow == s.yLow)
        && (height == s.height) && (width == s.width);
}
int Rectangle::GetHeight() {
    return height;
}
int Rectangle::GetWidth() {
    return width;
}
ostream& operator<<(ostream& os, Rectangle& s) {
    os << "xLow: " << s.xLow << ", yLow: " << s.yLow
       << ", height: " << s.height << ", width: " << s.width;
    return os;
}
bool Rectangle::operator<(Rectangle& s) {
    if (this == &s) return false; // same object
    if (Area() < s.Area())
        return true;
    else return false;
}
bool Rectangle::operator==(Rectangle& s) {
    if (this == &s) return true; // same object
    if (Area() == s.Area())
        return true;
    else return false;
}
