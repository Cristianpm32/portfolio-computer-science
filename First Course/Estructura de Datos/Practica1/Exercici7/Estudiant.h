#ifndef Estudiant_H
#define Estudiant_H
#include "Persona.h"
//Autor: Cristian Prado Méndez
class Estudiant : public Persona
{
private:
    int assignatures;

public:
    Estudiant(string s, int x, int y);
    void print();
    ~Estudiant();
};

#endif