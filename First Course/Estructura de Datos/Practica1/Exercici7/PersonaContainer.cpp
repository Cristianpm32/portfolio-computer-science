#include <iostream>
#include <vector>
using namespace std;
#include "PersonaContainer.h"
#include "Professor.h"
#include "Estudiant.h"
//Autor: Cristian Prado Méndez
int PersonaContainer::getOlder()
{
    int older = -1;
    for (vector<Persona *>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        if ((*it)->getEdat() > older)
        {
            older = (*it)->getEdat();
        }
    }
    return older;
}
int PersonaContainer::getYounger()
{
    int younger = 2023;
    for (vector<Persona *>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        if ((*it)->getEdat() < younger)
        {
            younger = (*it)->getEdat();
        }
    }
    return younger;
}
void PersonaContainer::addPersona(Persona *persona)
{
    if (elements.size() < 10)
    {
        elements.push_back(persona);
        cout << "Persona añadida" << endl;
    }
    else
    {
        throw invalid_argument("Ja has arribat al màxim de 10 persones.");
    }
}
void PersonaContainer::print()
{
    for (vector<Persona *>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        (*it)->print();
    }
}
PersonaContainer::~PersonaContainer()
{
    for (vector<Persona *>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        delete *it;
    }
    cout << "Destructor de PersonaContainer" << endl;
}