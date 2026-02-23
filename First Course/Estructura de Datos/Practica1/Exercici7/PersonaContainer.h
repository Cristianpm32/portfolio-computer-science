#ifndef PersonaContainer_H
#define PersonaContainer_H
#include <vector>
#include "Estudiant.h"
#include "Professor.h"
//Autor: Cristian Prado Méndez
class PersonaContainer
{
private:
    std::vector<Persona*> elements;
public:
    int getOlder();
    int getYounger();
    void addPersona(Persona* persona);
    void print();
    ~PersonaContainer();
};

#endif
