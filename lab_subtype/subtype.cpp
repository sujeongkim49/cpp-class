#include <iostream>
using namespace std;
#include "bagstack.h"
int main() {
    Bag b(3);
    Stack s(3);
    b.Push(1); b.Push(2); b.Push(3);
    b.Push(4); b.Push(5);
    cout << "Bag: " << b;
    s.Push(1); s.Push(2); s.Push(3);
    s.Push(4); s.Push(5);
    cout << "Stack: " << s << endl;
    b.Pop(); s.Pop();
    cout << "Bag: " << b;
    cout << "Stack: " << s << endl << endl;
    int j = s.Size(); //Stack의 부모클래스 Bag의 Size()가 불려진다
    cout << "Stack 크기: " << j << endl;
    j = s.Top(); //Stack의 Top()가 불려진다. 
    cout << "Stack Top() 결과: " << j << endl;
    j = s.Element(); //Stack의 부모클래스 Bag의 Element()가 불려진다. 
    cout << "Stack Element() 결과: " << j << endl<<endl;
}