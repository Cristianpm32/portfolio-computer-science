#include <iostream>
#include <stdexcept>
using namespace std;
#include "CuaEstatica.h"

// Autor: Cristian Prado Méndez

CuaEstatica::CuaEstatica(const int max_size)
{
    _data = new int[max_size];
    _max_size = max_size;
    _size = 0;
    _front = 0;
    _rear = 0;
    cout << "Estructura creada correctament" << endl;
}
CuaEstatica::~CuaEstatica()
{
    cout << "Destructor de CuaEstatica" << endl;
    delete[] _data;
}
void CuaEstatica::enqueue(const int key)
{
    cout << _size << endl;
    if (isFull())
    {
        throw length_error("EXCEPTION: L’estructura està plena ");
    }
    _data[_rear] = key;
    _rear = (_rear + 1) % _max_size;
    _size++;
    cout << "Element " << key << " agregat" << endl;
}
void CuaEstatica::dequeue()
{
    if (isEmpty())
    {
        throw out_of_range("EXCEPTION: L’estructura està buida ");
    }
    cout << "Element " << _data[_front] << " eliminat" << endl;
    _front = (_front + 1) % _max_size;
    _size--;
}
bool CuaEstatica::isFull()
{
    return _size == _max_size;
}
bool CuaEstatica::isEmpty()
{
    return _size == 0;
}
void CuaEstatica::print()
{
    cout << "[";
    if (_size > 0)
    {
        for (int i = 0; i < _size; i++)
        {
            if (_front + i != _front)
                cout << ", ";
            cout << _data[(_front + i) % _max_size];
        }
    }
    cout << "]" << endl;
}
const int CuaEstatica::getFront()
{
    if (isEmpty())
    {
        throw out_of_range("EXCEPTION: L’estructura està buida ");
    }
    return _data[_front];
}

void CuaEstatica::printFrontRear()
{
    cout << "Front: " << _front << ", Rear: " << _rear << endl;
}