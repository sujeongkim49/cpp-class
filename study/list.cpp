#include <iostream>
using namespace std;
class IntList;
class Node {
public:
    friend class IntList;
    Node(int d = 0, Node* l = 0) : data(d), link(l) {}
    friend ostream& operator<<(ostream&, IntList&);
private:
    int data;
    Node* link;
};

class IntList {
    friend ostream& operator<<(ostream&, IntList&);
public:
    Node* Find(int);
    void InsertAfter(int, Node*);
private:
    Node* first;
    Node* last;
};


Node* IntList::Find(int e) {
    Node* cur = first;
    Node* prev;
    Node* x;
    while (cur) {

    }
    return x;
}

void IntList