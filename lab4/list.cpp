#include "list.h"
ostream& operator<<(ostream& os, IntList& il)
{
    Node* ptr = il.first;
    while (ptr != 0) {
        os << ptr->data << " "; ptr = ptr->link;
    }
    os << endl;
    return os;
}
void IntList::InsertBack(int e)
{
    if (!first)
        first = last = new Node(e);
    else {
        last->link = new Node(e);
        last = last->link;
    }
}
void IntList::InsertFront(int e) {
    Node* n = new Node(e);
    if (first == nullptr)
        first = last = n;
    else {
        n->link = first;
        first = n;
    }
}
void IntList::Delete(int e) {
    //e를 검색하여 삭제하기
    Node* cur = first;
    Node* prev = first;
    Node* x = cur;
    bool found = false ;
    while (!found && cur) {
        if (cur->data != e) {
            prev = cur;
            cur = cur->link;
        }
        else
        {
            found = true;
            x = cur;
            //삭제 전 링크 조정하기
            if (cur == first)
                first = first->link;
            else if (cur == last)
            {
                last = prev;
                last->link = 0;
            }
            else
                prev->link = cur->link;
            delete x;
        }
    }// while
}