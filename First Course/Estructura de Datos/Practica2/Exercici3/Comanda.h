#ifndef COMANDA_H
#define COMANDA_H
#include <iostream>

using namespace std;
class Comanda
{
private:
    int identificador;
    string _menjar;
    int _quantitat;
    string _hora;

public:
    Comanda()
    {
    }
    Comanda(int id, string menjar, int quantitat, string hora);
    Comanda(const Comanda &c);
    ~Comanda();
    string toString() const;
    friend ostream &operator<<(ostream &os, const Comanda &obj);
};

#endif