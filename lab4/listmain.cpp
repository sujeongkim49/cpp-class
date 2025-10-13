//C435071 ±è¼öÁ¤
#include <iostream>
#include "list.h"
int main()
{
    IntList il;
    il.InsertFront(2); il.InsertBack(7);
    cout << il;
    il.InsertFront(4); il.InsertBack(5);
    cout << il;
    il.InsertFront(3); il.InsertBack(9);
    cout << il;
    il.Delete(8); // no 8 to delete!
    il.Delete(3); // delete the first int
    il.Delete(7); // delete an int in the middle
    il.Delete(9); // delete the last int
    cout << il;
}