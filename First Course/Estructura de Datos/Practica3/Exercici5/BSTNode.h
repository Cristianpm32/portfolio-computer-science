#ifndef BSTNODE_H
#define BSTNODE_H

#include <stdexcept>
#include <iostream>
#include <list>
using namespace std;

template <class K, class V>
class BSTNode
{
public:
    BSTNode(const K &key);              // O(1)
    BSTNode(const BSTNode<K, V> &orig); // O(n)
    virtual ~BSTNode();                 // O(n)

    /* Modificadors */
    // Declareu-hi aquí els modificadors (setters) dels atributs que manquen
    void setLeft(BSTNode<K, V> *n) // O(1)
    {
        _left = n;
        if (n != nullptr)
        {
            n->setParent(this);
        }
    }
    void setRight(BSTNode<K, V> *n) // O(1)
    {
        _right = n;
        if (n != nullptr)
        {
            n->setParent(this);
        }
    }
    void setParent(BSTNode<K, V> *n) // O(1)
    {
        _parent = n;
    }

    /* Consultors */
    const K &getKey() const // O(1)
    {
        return key;
    }

    const list<V> &getValues() const // O(1)
    {
        return values;
    }

    // Declareu-hi aquí els consultors (getters) dels atributs que manquen
    BSTNode<K, V> *getLeft() const // O(1)
    {
        return _left;
    }
    BSTNode<K, V> *getRight() const // O(1)
    {
        return _right;
    }
    BSTNode<K, V> *getParent() const // O(1)
    {
        return _parent;
    }
    /* Operacions */
    bool isRoot() const // O(1)
    {
        return _parent == nullptr;
    }
    bool hasLeft() const // O(1)
    {
        return _left != nullptr;
    }
    bool hasRight() const // O(1)
    {
        return _right != nullptr;
    }
    bool isExternal() const // O(1)
    {
        return (!hasLeft() && !hasRight());
    }

    void insertValue(const V &v) // O(1)
    {
        values.push_back(v);
    }
    int depth() const;                               // O(n)
    int height() const;                              // O(n)
    bool operator==(const BSTNode<K, V> &node) const // O(1)
    {
        return (key == node.getKey()) && (values == node.getValues());
    }

private:
    K key;
    list<V> values;
    BSTNode<K, V> *_left;
    BSTNode<K, V> *_right;
    BSTNode<K, V> *_parent;
    // Afegiu-hi aquí els atributs que manquen
};

template <class K, class V>
BSTNode<K, V>::BSTNode(const K &key)
{
    this->key = key;
    _left = nullptr;
    _right = nullptr;
    _parent = nullptr;
}
template <class K, class V>
BSTNode<K, V>::BSTNode(const BSTNode<K, V> &orig)
{
    key = orig.getKey();
    values = orig.getValues();
    _left = nullptr;
    _right = nullptr;
    _parent = nullptr;
    if (orig.hasLeft())
    {
        _left = new BSTNode<K, V>(*orig.getLeft());
        _left->setParent(this);
    }
    if (orig.hasRight())
    {
        _right = new BSTNode<K, V>(*orig.getRight());
        _right->setParent(this);
    }
}
template <class K, class V>
BSTNode<K, V>::~BSTNode()
{
    delete _left;
    delete _right;
}

template <class K, class V>
int BSTNode<K, V>::depth() const
{
    if (isRoot())
    {
        return 0;
    }
    else
    {
        return 1 + _parent->depth();
    }
}

template <class K, class V>
int BSTNode<K, V>::height() const
{
    int h_l = 0, h_r = 0;

    if (hasLeft())
        h_l = getLeft()->height();

    if (hasRight())
        h_r = getRight()->height();

    return max(h_l, h_r) + 1;
}

#endif
