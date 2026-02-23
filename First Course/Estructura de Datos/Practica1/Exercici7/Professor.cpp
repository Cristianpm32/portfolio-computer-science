#include <iostream>
using namespace std;
#include "Professor.h"
#include "Persona.h"
//Autor: Cristian Prado Méndez
Professor::Professor(string s, int x) : Persona(s, x)
{
    cout << "Constructor de Professor" << endl;
}
void Professor::print()
{
    cout << "Professor(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ")" << endl;
    cout << "Edat del nou professor: " << getEdat() << "\n"
         << endl;
}
Professor::~Professor(){
    cout << "Destructor de Professor" << endl;
}