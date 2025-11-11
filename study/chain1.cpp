template <class T> class Chain;

template <class T>
class ChainNode {
    friend class Chain<T>;
public:
    ChainNode(int element = 0, ChainNode* next = 0) {
        data = element; link = next;
    }
private:
    T data;
    ChainNode<T>* link;
};

template <class T>
class Chain {
private:
    ChainNode<T>* first;
};