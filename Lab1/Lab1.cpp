//C435071 �����
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool myfunction(int i, int j) { return (i < j); }
struct myclass {
    bool operator() (int i, int j) { return (i > j); }
} myobject;
int main() {
    int myints[] = { 32,71,12,45,26,80,53,33 };
    vector<int> myvector(myints, myints + 8); // 32 71 12 45 26 80 53 33
    vector<int>::iterator it; // using default comparison (operator <):
    cout << "�ʱ� myvector contains:";
    for (it = myvector.begin(); it != myvector.end(); ++it)
        cout << " " << *it; cout << endl;
    cout << endl;
    sort(myvector.begin(), myvector.begin() + 4); //(12 32 45 71)26 80 53 33
    cout << "�� 4���� �������� ���� ��myvector contains:";
    for (it = myvector.begin(); it != myvector.end(); ++it)
        cout << " " << *it; cout << endl;
    cout << endl;
    // using function as comp
    sort(myvector.begin() + 4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)
    // using object as comp
    sort(myvector.begin(), myvector.end(), myobject); // ��ü �������� ���� (80 71 53 45 33 32 26 12)
    // print out content:
    cout << "��ü �������� ���� �� myvector contains:";
    for (it = myvector.begin(); it != myvector.end(); ++it)
        cout << " " << *it; cout << endl;
    cout << endl;
    return 0;
}