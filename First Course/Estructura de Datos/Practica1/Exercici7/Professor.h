#ifndef Professor_H
#define Professor_H
#include "Persona.h"
//Autor: Cristian Prado Méndez
class Professor : public Persona
{
public:
    Professor(string s, int x);
    void print();
    ~Professor();
};

#endif