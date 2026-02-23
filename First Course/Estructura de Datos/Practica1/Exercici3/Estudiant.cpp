#include <iostream>
using namespace std;
#include "Estudiant.h"
//Autor: Cristian Prado Méndez
Estudiant::Estudiant(string s, int x, int y)
{
    if (x <= 0 || x > 2022)
    {
        throw invalid_argument("L'any de naixement introduït no és correcte! Any introduït: " + to_string(x));
    }
    else
    {
        nom = s;
        any_naixement = x;
        assignatures = y;
    }
}
void Estudiant::print()
{
    cout << "Estudiant(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ", Assignatures ==> " << assignatures << ")" << endl;
    cout << "Edat del nou estudiant: " << getEdat() << endl;
}
int Estudiant::getEdat()
{
    return 2022 - any_naixement;
}
