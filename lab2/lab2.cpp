//C435071 ±è¼öÁ¤

#include <iostream>
#include "rectangle.h"
using namespace std;

int main() {
    Rectangle r(2, 3, 4, 6), s(1, 2, 6, 6);
    cout << "<rectangle r> "; r.Print();
    cout << "<rectangle s> "; s.Print();
    if (r.LessThan(s))
        cout << "s is bigger";
    else if (r.EqualSize(s))
        cout << "Same Size";
    else cout << "r is bigger";
    cout << endl << endl;
    cout << "<rectangle r> " << r << endl;
    cout << "<rectangle s> " << s << endl;
    if (r < s)
        cout << "s is bigger";
    else if (r == s)
        cout << "Same Size";
    else cout << "r is bigger";
    cout << endl << endl << endl << endl;
    return 0;
}