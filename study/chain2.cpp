template <class T>
void Chain<T>::InsertBack(const T& e) {
    if (first) {
        last->link = new ChainNode<T>(e);
        last = last->link;
    }
    else first = last = new ChainNode<T>(e);
}