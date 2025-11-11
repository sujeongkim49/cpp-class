#pragma once
#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <queue>
using namespace std;
template <class K, class E> class BST; //전방선언
template <class K, class E>
class TreeNode {
    friend class BST<K, E>;
    TreeNode(K ky, E el, TreeNode<K, E>* left = 0, TreeNode<K, E>* right = 0)
        : key(ky), element(el), leftChild(left), rightChild(right) {
    }
private:
    TreeNode<K, E>* leftChild;
    K key;
    E element;
    TreeNode<K, E>* rightChild;
};
template <class K, class E>
class BST {
public:
    BST() { root = 0; } // empty BST
    void Insert(K& newkey, E& el) { Insert(root, newkey, el); }
    void Preorder() { Preorder(root); }
    void Inorder() { Inorder(root); }
    void Postorder() { Postorder(root); }
    void Levelorder();
private: // helper 함수들
    void Visit(TreeNode<K, E>*);
    void Insert(TreeNode<K, E>*&, K&, E&);
    void Preorder(TreeNode<K, E>*);
    void Inorder(TreeNode<K, E>*);
    void Postorder(TreeNode<K, E>*);
    TreeNode<K, E>* root;
};
template <class K, class E>
void BST<K, E>::Visit(TreeNode<K, E>* ptr)
{
    cout << ptr->key << ":" << ptr->element << " ";
}
template <class K, class E>
void BST<K, E>::Insert(TreeNode<K, E>*& ptr, K& newkey, E& el) { 
        if (ptr == 0) ptr = new TreeNode<K, E>(newkey, el);
        else if (newkey < ptr->key) Insert(ptr->leftChild, newkey, el);
        else if (newkey > ptr->key) Insert(ptr->rightChild, newkey, el);
        else ptr->element = el; // Update element
}
template <class K, class E>
void BST<K, E>::Preorder(TreeNode<K, E>* currentNode) { //Preorder의helper함수
    if (currentNode) {
        Visit(currentNode);
        Preorder(currentNode->leftChild);
        Preorder(currentNode->rightChild);
    }
}
template <class K, class E>
void BST<K, E>::Inorder(TreeNode<K, E>* currentNode) {
    if (currentNode) {
        Inorder(currentNode->leftChild);
        Visit(currentNode);
        Inorder(currentNode->rightChild);
    }
}
template <class K, class E>
void BST<K, E>::Postorder(TreeNode<K, E>* currentNode) {
    if (currentNode) {
        Postorder(currentNode->leftChild);
        Postorder(currentNode->rightChild);
        Visit(currentNode);
    }
}
template <class K, class E>
void BST<K, E>::Levelorder() {
    if (root == 0) return; // empty tree
    queue<TreeNode<K, E>*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode<K, E>* currentNode = q.front();
        q.pop();
        Visit(currentNode);
        if (currentNode->leftChild)
            q.push(currentNode->leftChild);
        if (currentNode->rightChild)
            q.push(currentNode->rightChild);
    }
}

#endif