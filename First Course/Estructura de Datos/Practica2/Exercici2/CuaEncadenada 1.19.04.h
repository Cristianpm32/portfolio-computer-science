#ifndef CuaEncadenada_H
#define CuaEncadenada_H
#include <stdexcept>
#include "Node.h"
template <typename T>
class CuaEncadenada
{
public:
    CuaEncadenada();
    CuaEncadenada(const CuaEncadenada<T> &q);
    ~CuaEncadenada();
    bool isEmpty();
    void print();
    void enqueue(const T key);
    void dequeue();
    const T getFront()
    {
        if (_front->getNext() == nullptr)
        {
            throw out_of_range("EXCEPTION: L'estructura està buida");
        }
        return _front->getNext()->getElement();
    }

private:
    Node<T> *_front;
    Node<T> *_rear;
};
template <typename T>
CuaEncadenada<T>::CuaEncadenada()
{
    Node<T> *sentinella = new Node<T>();
    _front = sentinella;
    _rear = sentinella;
    if (sentinella == nullptr)
    {
        throw bad_alloc();
    }
    cout << "L'estructura ha estat creada correctament" << endl;
}
template <typename T>
CuaEncadenada<T>::CuaEncadenada(const CuaEncadenada<T> &q)
{
    Node<T> *sentinella = new Node<T>();
    _front = sentinella;
    _rear = sentinella;
    if (sentinella == nullptr)
    {
        throw bad_alloc();
    }
    else
    {
        sentinella = q._front->getNext;
        while (sentinella != nullptr)
        {
            enqueue(sentinella->getElement());
            sentinella = sentinella->getNext();
        }
        cout << "L'estructura ha estat creada correctament" << endl;
    }
}
template <typename T>
CuaEncadenada<T>::~CuaEncadenada()
{
    cout << "Destructor de CuaEncadenada" << endl;
    Node<T> *auxDelete;
    while (_front != nullptr)
    {
        auxDelete = _front->getNext();
        delete _front;
        _front = auxDelete;
    }
}
template <typename T>
bool CuaEncadenada<T>::isEmpty()
{
    return _front->getNext() == nullptr;
}
template <typename T>
void CuaEncadenada<T>::enqueue(const T key)
{
    Node<T> *nouNode = new Node<T>(key);
    _rear->setNext(nouNode);
    _rear = nouNode;
    cout << "Element " << key << " agregat." << endl;
}
template <typename T>
void CuaEncadenada<T>::dequeue()
{
    if (isEmpty())
    {
        throw out_of_range("EXCEPTION: L'estructura està buida");
    }
    Node<T> *aux = _front->getNext();
    _front->setNext(aux->getNext());
    cout << "Element " << aux->getElement() << " eliminat." << endl;
    delete aux;
    if (_front->getNext() == nullptr)
    {
        _rear = _front;
    }
}
template <typename T>
void CuaEncadenada<T>::print()
{
    cout << "[";
    Node<T> *auxPrint = _front->getNext();
    while (auxPrint != nullptr)
    {
        cout << auxPrint->getElement();
        if (auxPrint != _rear)
        {
            cout << ", ";
        }
        auxPrint = auxPrint->getNext();
    }
    cout << "]" << endl;
}

#endif
