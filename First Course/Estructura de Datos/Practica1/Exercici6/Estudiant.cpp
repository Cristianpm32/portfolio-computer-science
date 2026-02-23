#include <iostream>
using namespace std;
#include "Estudiant.h"
#include "Persona.h"
//Autor: Cristian Prado Méndez
Estudiant::Estudiant(string s, int x, int y) : Persona(s,x)
{
        this-> assignatures = y;
        cout << "Constructor d'Estudiant" << endl;
}
void Estudiant::print()
{
    cout << "Estudiant(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ", Assignatures ==> " << assignatures << ")" << endl;
    cout << "Edat del nou estudiant: " << getEdat() << "\n" << endl;
}