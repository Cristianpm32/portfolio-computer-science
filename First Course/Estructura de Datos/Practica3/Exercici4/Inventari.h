#ifndef INVENTARI_H
#define INVENTARI_H

#include <iostream>
#include <iterator>
#include "BSTArbre.h"
#include "BSTNode.h"
#include "FoodPackage.h"
using namespace std;

template <class T>
class Inventari : protected T
{
public:
    Inventari(float iva);// O(1)
    Inventari(float iva, string file_path);// O(1)
    Inventari(const Inventari<T> &orig);// O(1)
    virtual ~Inventari();

    void loadFromFile(string file_path);// O(nlog(n))
    void printAll() const;// O(n)
    void printAllReverse() const;// O(n)

    float priceInTotal() const;// O(n)
    float priceInTimeInterval(pair<string, string> ival) const;// O(n)
    float priceInTimeIntervalByProduct(pair<string, string> ival, string pid) const;// O(n)

    int size() const// O(1)
    {
        return this->size();
    }
    int height() const// O(1)
    {
        return this->height();
    }

private:
    float iva;
    /* Metodes auxiliars, definiu-los aquí sota */
    //Els mètodes auxiliars tenen la mateixa complexitat que el mètodes dels que són auxiliars.
    void printAll(const BSTNode<string, FoodPackage> *n) const;
    void printAllReverse(const BSTNode<string, FoodPackage> *n) const;
    void priceInTotal(const BSTNode<string, FoodPackage> *n, float &preuTotal) const;
    void priceInTimeInterval(const BSTNode<string, FoodPackage> *n, pair<string, string> ival, float &preuInterval) const;
    void priceInTimeIntervalByProduct(const BSTNode<string, FoodPackage> *n, pair<string, string> ival, float &preuInterval, string &pid) const;
};
template <class T>
Inventari<T>::Inventari(float iva) : T()
{
    this->iva = iva;
}
template <class T>
Inventari<T>::Inventari(float iva, string file_path) : T()
{
    this->iva = iva;
    loadFromFile(file_path);
}

template <class T>
Inventari<T>::Inventari(const Inventari<T> &orig) : T((T)orig)
{
    iva = orig.iva;
}

template <class T>
Inventari<T>::~Inventari()
{
}

template <class T>
void Inventari<T>::loadFromFile(string file_path)
{
    ifstream fitxer(file_path);
    string dataTime, productId, quantitat, preu;
    getline(fitxer, dataTime);             // S'executa una unica vegada per saltar-se la primera linia dels arxius (headers).
    while (getline(fitxer, dataTime, ',')) // opcio alternativa : while(!fitxer.eof()) i posar el getline a dins del while
    {
        getline(fitxer, productId, ',');
        getline(fitxer, quantitat, ',');
        getline(fitxer, preu);
        this->insert(dataTime, FoodPackage(dataTime, productId, stoi(quantitat), stof(preu)));
    }
    fitxer.close();
}

template <class T>
void Inventari<T>::printAll() const
{
    if (this->empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    printAll(this->root);
}
template <class T>
void Inventari<T>::printAll(const BSTNode<string, FoodPackage> *n) const
{

    if (n->hasLeft())
        printAll(n->getLeft());

    cout << n->getKey() << ": " << endl;
    for (list<FoodPackage>::const_iterator it = n->getValues().begin(); it != n->getValues().end(); ++it)
    {
        cout << "    " << it->toString() << endl;
    }

    if (n->hasRight())
        printAll(n->getRight());
}

template <class T>
void Inventari<T>::printAllReverse() const
{
    if (this->empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    printAllReverse(this->root);
}
template <class T>
void Inventari<T>::printAllReverse(const BSTNode<string, FoodPackage> *n) const
{

    if (n->hasRight())
        printAllReverse(n->getRight());

    cout << n->getKey() << ": " << endl;
    for (list<FoodPackage>::const_iterator it = n->getValues().begin(); it != n->getValues().end(); ++it)
    {
        cout << "    " << it->toString() << endl;
    }

    if (n->hasLeft())
        printAllReverse(n->getLeft());
}
template <class T>
float Inventari<T>::priceInTotal() const
{
    if (this->empty())
    {
        throw out_of_range("EXCEPTION: L'arbre està buit, no hi ha elements");
    }
    float preuTotal = 0;
    priceInTotal(this->root, preuTotal);
    return preuTotal;
}
template <class T>
void Inventari<T>::priceInTotal(const BSTNode<string, FoodPackage> *n, float &preuTotal) const
{
    if (n->hasLeft())
        priceInTotal(n->getLeft(), preuTotal);
    for (list<FoodPackage>::const_iterator it = n->getValues().begin(); it != n->getValues().end(); ++it)
    {
        preuTotal += it->getPrice() * (1 + this->iva) * it->getAmount();
    }

    if (n->hasRight())
        priceInTotal(n->getRight(), preuTotal);
}
template <class T>
float Inventari<T>::priceInTimeInterval(pair<string, string> ival) const
{
    float preuInterval = 0;
    if (!this->empty())
        priceInTimeInterval(this->root, ival, preuInterval);
    return preuInterval;
}
template <class T>
void Inventari<T>::priceInTimeInterval(const BSTNode<string, FoodPackage> *n, pair<string, string> ival, float &preuInterval) const
{
    if (ival.first > n->getKey())
    {
        if (n->hasRight())
            priceInTimeInterval(n->getRight(), ival, preuInterval);
    }
    else if (ival.second < n->getKey())
    {
        if (n->hasLeft())
            priceInTimeInterval(n->getLeft(), ival, preuInterval);
    }
    else
    {
        for (list<FoodPackage>::const_iterator it = n->getValues().begin(); it != n->getValues().end(); ++it)
        {
            preuInterval += it->getPrice() * (1 + this->iva) * it->getAmount();
        }
        if (n->hasRight())
            priceInTimeInterval(n->getRight(), ival, preuInterval);
        if (n->hasLeft())
            priceInTimeInterval(n->getLeft(), ival, preuInterval);
    }
}

template <class T>
float Inventari<T>::priceInTimeIntervalByProduct(pair<string, string> ival, string pid) const
{
    float preuInterval = 0;
    if (!this->empty())
        priceInTimeIntervalByProduct(this->root, ival, preuInterval, pid);
    return preuInterval;
}
template <class T>
void Inventari<T>::priceInTimeIntervalByProduct(const BSTNode<string, FoodPackage> *n, pair<string, string> ival, float &preuInterval, string &pid) const
{
    if (ival.first > n->getKey())
    {
        if (n->hasRight())
            priceInTimeIntervalByProduct(n->getRight(), ival, preuInterval, pid);
    }
    else if (ival.second < n->getKey())
    {
        if (n->hasLeft())
            priceInTimeIntervalByProduct(n->getLeft(), ival, preuInterval, pid);
    }
    else
    {
        for (list<FoodPackage>::const_iterator it = n->getValues().begin(); it != n->getValues().end(); ++it)
        {
            if (it->getProduct_id() == pid)
                preuInterval += it->getPrice() * (1 + this->iva) * it->getAmount();
        }
        if (n->hasRight())
            priceInTimeIntervalByProduct(n->getRight(), ival, preuInterval, pid);
        if (n->hasLeft())
            priceInTimeIntervalByProduct(n->getLeft(), ival, preuInterval, pid);
    }
}
#endif