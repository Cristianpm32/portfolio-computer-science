#include <iostream>
using namespace std;
#include "Professor.h"
//Autor: Cristian Prado Méndez
Professor::Professor(string s, int x)
{
    if (x <= 0 || x > 2022)
    {
        throw invalid_argument("L'any de naixement introduït no és correcte! Any introduït: " + to_string(x));
    }
    else
    {
        nom = s;
        any_naixement = x;
    }
}
void Professor::print()
{
    cout << "Professor(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ")" << endl;
    cout << "Edat del nou professor: " << getEdat() << "\n" << endl;
}
int Professor::getEdat()
{
    return 2022 - any_naixement;
}