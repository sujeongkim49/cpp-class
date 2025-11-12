#pragma once
#include <iostream>
#include <algorithm>
using namespace std;
template <class T>
class MaxPQ {
public:
    virtual~MaxPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};
template <class T>
class Maxheap : public MaxPQ <T > {
public:
    Maxheap(int); // constructor
    Maxheap(); // default constructor: capacity를 임의로 설정.
    ~Maxheap();//파괴자
    void Push(const T& e);
    void Pop();
    bool IsEmpty() const { return heapSize ==0 ; } // ?? 채우기
    const T& Top() const { return heap[1] ; } // ?? 채우기
    template <class T> friend ostream& operator<<(ostream&, Maxheap<T>&);
private:
    void ChangeSize1D(T*&, int, int);
    T* heap; // element array
    int heapSize; // #elements in heap
    int capacity; // size of the array heap
};
template <class T>
ostream& operator<<(ostream& os, Maxheap<T>& H) {
    os << "<Heap Contents> ";
    for(int i=1; i<=H.heapSize; i++)
        os << i<<":"<<H.heap[i] << " ";
    os << endl;
    return os;
}
template <class T>
Maxheap<T>::~Maxheap() // destructor
{
    if (heapSize) delete[] heap;
}
template <class T>
void Maxheap<T>::ChangeSize1D(T*& a, int oldsize, int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    int* temp = new int[newSize];
    int number = min(oldsize, newSize);
    copy(a, a + number + 1, temp);
    delete[] a;
    a = temp;
}

template <class T>
Maxheap<T>::Maxheap(int capacityis) {
    if (capacityis < 1) throw "Capacity must be >= 1";
    capacity = capacityis;
    heapSize = 0;
    heap = new T[capacity + 1];
}

template <class T>
Maxheap<T>::Maxheap() {
    capacity = 10;
    heapSize = 0;
    heap = new T[capacity + 1];
}

template <class T>
void Maxheap<T>::Push(const T& e) {
    if (heapSize == capacity) {
        ChangeSize1D(heap, capacity + 1, 2 * capacity + 1);
        capacity *= 2;
    }
    int i = ++heapSize;
    while ((i != 1) && (e > heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = e;
}

template <class T>
void Maxheap<T>::Pop() {
    if (IsEmpty()) throw "Heap is empty. Cannot pop.";
    T rootMax = heap[1];
    T last = heap[heapSize];
    heapSize--;
    int parent = 1;
    int child = 2;
    while (child <= heapSize) {
        if((child + 1 <= heapSize) && (heap[child+1] > heap[child]))
            child++;
        if (last >= heap[child]) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last;
}

//... constructor, Push, Pop, Top, IsEmpty 함수의 구현(교재 이용)