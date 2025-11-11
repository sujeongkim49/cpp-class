void ChangeSize1D(int*& a, const int oldsize, const int newsize) {
    if (newsize < 0) throw "คว";
    int* temp = new int[newsize];
    int number = std::min(oldsize, newsize);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}