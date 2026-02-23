#include <iostream>
using namespace std;
#include "Persona.h"
//Autor: Cristian Prado Méndez
Persona::Persona(string s, int x)
{
    if (x <= 0 || x > 2022)
    {
        throw invalid_argument("L'any de naixement introduït no és correcte! Any introduït: " + to_string(x));
    }
    else
    {
        this->nom = s;
        this->any_naixement = x;
        cout << "Constructor de Persona" << endl;
    }
}
int Persona::getEdat()
{
    return 2022 - any_naixement;
}

void Persona::print(){

}
Persona::~Persona(){
    cout << "Destructor de Persona" << endl;
}