#ifndef BSTARBRE_H
#define BSTARBRE_H

#include <stdexcept>
#include <iostream>
#include <list>
#include "BSTNode.h"
using namespace std;

template <class K, class V>
class BSTArbre
{
public:
    BSTArbre();                           // O(1)
    BSTArbre(const BSTArbre<K, V> &orig); // O(n)
    virtual ~BSTArbre();                  // O(n)

    bool empty() const // O(1)
    {
        return _size == 0;
        // return root == nullptr;
    }
    int size() const // O(1)
    {
        return _size;
    }
    int height() const; // O(n)

    BSTNode<K, V> *insert(const K &k, const V &value);           // O(n)
    const list<V> &valuesOf(const K &k) const;                   // O(n)
    void printPreorder(const BSTNode<K, V> *n = nullptr) const;  // O(n)
    void printInorder(const BSTNode<K, V> *n = nullptr) const;   // O(n)
    void printPostorder(const BSTNode<K, V> *n = nullptr) const; // O(n)

    const list<BSTNode<K, V> *> &getLeafNodes() const; // O(n)
    void printSecondLargestKey() const;                // O(n)
    void mirrorTree();                                 // O(n)

protected:
    BSTNode<K, V> *root;
    BSTNode<K, V> *search(const K &k) const; // O(n)

private:
    int _size;
    /* Mètodes auxiliars definiu aquí els que necessiteu */
    // Tenen complexitat igual als mètodes dels que són auxiliars.
    void addLeafNode(BSTNode<K, V> *n, list<BSTNode<K, V> *> &list) const;
    void getSecond(BSTNode<K, V> *n, K &firstK, K &secondK) const;
    void mirrorTree(BSTNode<K, V> *n);
};
template <class K, class V>
BSTArbre<K, V>::BSTArbre()
{
    root = nullptr;
    _size = 0;
}

template <class K, class V>
BSTArbre<K, V>::BSTArbre(const BSTArbre<K, V> &orig)
{
    _size = orig._size;
    root = new BSTNode<K, V>(*orig.root);
}
template <class K, class V>
BSTArbre<K, V>::~BSTArbre()
{
    delete root;
}
template <class K, class V>
const list<V> &BSTArbre<K, V>::valuesOf(const K &k) const
{
    BSTNode<K, V> *n = search(k);
    if (n == nullptr)
    {
        throw invalid_argument("No hi ha cap node amb aquesta clau.");
    }
    else
    {
        return n->getValues();
    }
}
template <class K, class V>
void BSTArbre<K, V>::printPreorder(const BSTNode<K, V> *n) const
{
    // excepcio arbre buit
    if (empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    if (n == nullptr)
    {
        cout << "Preorder = [";
        printPreorder(root);
        cout << "]" << endl;
    }
    else
    {
        cout << n->getKey() << ", ";
        if (n->hasLeft())
            printPreorder(n->getLeft());
        if (n->hasRight())
            printPreorder(n->getRight());
    }
}
template <class K, class V>
void BSTArbre<K, V>::printInorder(const BSTNode<K, V> *n) const
{
    // excepcio arbre buit
    if (empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    if (n == nullptr)
    {
        cout << "Inorder = [";
        printInorder(root);
        cout << "]" << endl;
    }
    else
    {

        if (n->hasLeft())
            printInorder(n->getLeft());
        cout << n->getKey() << ", ";
        if (n->hasRight())
            printInorder(n->getRight());
    }
}
template <class K, class V>
void BSTArbre<K, V>::printPostorder(const BSTNode<K, V> *n) const
{
    // excepcio arbre buit
    if (empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    if (n == nullptr)
    {
        cout << "Postorder = [";
        printPostorder(root);
        cout << "]" << endl;
    }
    else
    {
        if (n->hasLeft())
            printPostorder(n->getLeft());
        if (n->hasRight())
            printPostorder(n->getRight());
        cout << n->getKey() << ", ";
    }
}

template <class K, class V>
BSTNode<K, V> *BSTArbre<K, V>::search(const K &k) const
{
    if (empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    else
    {
        BSTNode<K, V> *aux = root;
        bool trobat = false;
        while (trobat && aux != nullptr)
        {
            if (k < aux->getKey())
            {
                aux = aux->getLeft();
            }
            else if (k > aux->getKey())
            {
                aux = aux->getRight();
            }
            else
            {
                trobat = true;
            }
        }
        return aux;
    }
}
template <class K, class V>
BSTNode<K, V> *BSTArbre<K, V>::insert(const K &k, const V &value)
{
    BSTNode<K, V> *nouNode = new BSTNode<K, V>(k);
    nouNode->insertValue(value);
    if (empty())
    {

        root = nouNode;
        _size++;
    }
    else
    {
        BSTNode<K, V> *aux = root;
        bool trobat = false;
        while (!trobat)
        {
            if (k < aux->getKey())
            {
                if (aux->hasLeft())
                {
                    aux = aux->getLeft();
                }
                else
                {
                    aux->setLeft(nouNode);
                    _size++;
                    trobat = true;
                }
            }
            else if (k > aux->getKey())
            {
                if (aux->hasRight())
                {
                    aux = aux->getRight();
                }
                else
                {
                    aux->setRight(nouNode);
                    _size++;
                    trobat = true;
                }
            }
            else
            {
                aux->insertValue(value);
                trobat = true;
                delete nouNode;
                nouNode = aux;
            }
        }
    }
    return nouNode;
}
template <class K, class V>
int BSTArbre<K, V>::height() const
{
    if (empty())
    {
        return 0;
    }
    else
    {
        return root->height();
    }
}
template <class K, class V>
const list<BSTNode<K, V> *> &BSTArbre<K, V>::getLeafNodes() const
{
    if (empty())
    {
        throw out_of_range("EXCEPTION: L'arbre no té fulles, està buit");
    }
    list<BSTNode<K, V> *> *llista = new list<BSTNode<K, V> *>();
    addLeafNode(root, *llista);
    return *llista;
}
template <class K, class V>
void BSTArbre<K, V>::addLeafNode(BSTNode<K, V> *n, list<BSTNode<K, V> *> &list) const
{
    if (n->isExternal())
    {
        list.push_back(n);
    }
    else
    {
        if (n->hasLeft())
        {
            addLeafNode(n->getLeft(), list);
        }
        if (n->hasRight())
        {
            addLeafNode(n->getRight(), list);
        }
    }
}

template <class K, class V>
void BSTArbre<K, V>::printSecondLargestKey() const
{
    K first;
    K second;
    if (_size < 2)
    {
        throw out_of_range("EXCEPTION: L'arbre no conté més de 2 elements");
    }
    if (root->hasRight())
    {
        first = root->getRight()->getKey();
        second = root->getKey();
    }
    else
    {
        first = root->getKey();
        second = root->getLeft()->getKey();
    }
    getSecond(root, first, second);
    cout << "Second largest key is ... " << second << endl;
}
template <class K, class V>
void BSTArbre<K, V>::getSecond(BSTNode<K, V> *n, K &firstK, K &secondK) const
{
    if (n->getKey() > firstK)
    {
        secondK = firstK;
        firstK = n->getKey();
    }
    else if (n->getKey() > secondK)
    {
        secondK = n->getKey();
    }

    if (n->hasLeft())
    {
        getSecond(n->getLeft(), firstK, secondK);
    }
    if (n->hasRight())
    {
        getSecond(n->getRight(), firstK, secondK);
    }
}

template <class K, class V>
void BSTArbre<K, V>::mirrorTree()
{
    if (!empty())
    {
        mirrorTree(root);
    }
    cout << "Mirror Arbre Binari";
}
template <class K, class V>
void BSTArbre<K, V>::mirrorTree(BSTNode<K, V> *n)
{

    if (n->hasLeft())
    {
        mirrorTree(n->getLeft());
    }
    if (n->hasRight())
    {
        mirrorTree(n->getRight());
    }

    BSTNode<K, V> *aux = n->getLeft();
    n->setLeft(n->getRight());
    n->setRight(aux);
}

#endif