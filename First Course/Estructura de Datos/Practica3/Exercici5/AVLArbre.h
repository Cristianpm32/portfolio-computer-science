#ifndef AVLARBRE_H
#define AVLARBRE_H
#include "BSTNode.h"
#include "BSTArbre.h"
template <class K, class V>
class AVLArbre : public BSTArbre<K, V>
{
public:
    const int balanceFactor(const BSTNode<K, V> *n); // O(n^2)
    BSTNode<K, V> *insert(const K &k, const V &value);// O(log n)

private:
    void rotacioDreta(BSTNode<K, V> *n); // O(1)
    void rotacioDretaEsquerra(BSTNode<K, V> *n); // O(1)
    void rotacioEsquerraDreta(BSTNode<K, V> *n); // O(1)
    void rotacioEsquerra(BSTNode<K, V> *n); // O(1)
};
template <class K, class V>
BSTNode<K, V> *AVLArbre<K, V>::insert(const K &k, const V &value)
{
    BSTNode<K, V> *node = BSTArbre<K, V>::insert(k, value);
    BSTNode<K, V> *aux = node->getParent();
    while (aux != nullptr)
    {
        int bf = balanceFactor(aux);

        if (bf > 1 || bf < -1)
        {
            int bf_fill;
            if (bf > 0)
                bf_fill = balanceFactor(aux->getLeft());
            else
                bf_fill = balanceFactor(aux->getRight());

            if (bf >= 2 && bf_fill >= 0)
            {
                rotacioDreta(aux);
            }
            else if (bf >= 2 && bf_fill < 0)
            {
                rotacioEsquerraDreta(aux);
            }
            else if (bf <= -2 && bf_fill > 0)
            {
                rotacioDretaEsquerra(aux);
            }
            else if (bf <= -2 && bf_fill <= 0)
            {
                rotacioEsquerra(aux);
            }
        }

        aux = aux->getParent();
    }
    return node;
}
template <class K, class V>
const int AVLArbre<K, V>::balanceFactor(const BSTNode<K, V> *n)
{
    int balanceFactor = 0;
    if (n->hasLeft() && n->hasRight())
    {
        balanceFactor = n->getLeft()->height() - n->getRight()->height();
    }
    else if (n->hasRight() && !n->hasLeft())
    {
        balanceFactor = -n->getRight()->height();
    }
    else if (n->hasLeft() && !n->hasRight())
    {
        balanceFactor = n->getLeft()->height();
    }
    return balanceFactor;
}
template <class K, class V>
void AVLArbre<K, V>::rotacioEsquerra(BSTNode<K, V> *n) // Rotació cap a l'esquerra
{

    BSTNode<K, V> *f = n->getRight();
    BSTNode<K, V> *p = n->getParent();

    if (p != nullptr)
    {
        if (p->getKey() > f->getKey())
            p->setLeft(f);
        else
        {
            p->setRight(f);
        }
    }
    else
    {
        this->root = f;
        f->setParent(nullptr);
    }
    n->setRight(f->getLeft());
    f->setLeft(n);
}
template <class K, class V>
void AVLArbre<K, V>::rotacioDreta(BSTNode<K, V> *n) // Rotació cap a la dreta
{

    BSTNode<K, V> *f = n->getLeft();
    BSTNode<K, V> *p = n->getParent();

    if (p != nullptr)
    {
        if (p->getKey() > f->getKey())
            p->setLeft(f);
        else
        {
            p->setRight(f);
        }
    }
    else
    {
        this->root = f;
        f->setParent(nullptr);
    }

    n->setLeft(f->getRight());
    f->setRight(n);
}
template <class K, class V>
void AVLArbre<K, V>::rotacioEsquerraDreta(BSTNode<K, V> *n) // Primera rotació cap a l'esquerra i segona rotació cap a la dreta
{
    rotacioEsquerra(n->getLeft());
    rotacioDreta(n);
}
template <class K, class V>
void AVLArbre<K, V>::rotacioDretaEsquerra(BSTNode<K, V> *n) // Primera rotació cap a la dreta i segona rotació cap a l'esquerra
{
    rotacioDreta(n->getRight());
    rotacioEsquerra(n);
}
#endif