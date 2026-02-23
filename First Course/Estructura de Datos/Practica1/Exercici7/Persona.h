#ifndef Persona_H
#define Persona_H
#include <string>
using namespace std;
//Autor: Cristian Prado Méndez
class Persona
{
protected:
    string nom;
    int any_naixement;

public:
    Persona(string s, int x);
    virtual void print();
    int getEdat();
    virtual ~Persona();
};

#endif