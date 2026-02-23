#include <iostream>
#include "Comanda.h"
using namespace std;

Comanda::Comanda(int id, string menjar, int quantitat, string hora)
{
    identificador = id;
    _menjar = menjar;
    _quantitat = quantitat;
    _hora = hora;
}
Comanda::Comanda(const Comanda &c)
{
    identificador = c.identificador;
    _menjar = c._menjar;
    _quantitat = c._quantitat;
    _hora = c._hora;
}
Comanda::~Comanda()
{
    cout << "Comanda eliminada" << endl;
}
string Comanda::toString() const
{
    string comanda = "Identificador: " + to_string(identificador) + ", Plat demanat: " +
                     _menjar + ", Quantitat: " + to_string(_quantitat) + ", Hora de la comanda: " + _hora;
    return comanda;
}
ostream &operator<<(ostream &os, const Comanda &obj)
{
    os << obj.toString();
    return os;
}