#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;
#include "Professor.h"
#include "Estudiant.h"
/* Es segueix amb la mateixa dinàmica que a l'exercici 4, però ara introduïm al menú un nou cas, que és el de llegi el fitxer.
Aquest fitxer es llegeix amb el mètode show_file, i el que fa és utilitzar les eines de tractament amb fitxers per poder convertir
les dades. Es fa un for per convertir cada línia del fitxer i imprimir-la tal i com es faria amb un objecte de Estudiant o de 
Professor. A més a més, es passa per referència el recompte de professors i estudiants per poder afegir els del fitxer al 
comptador. S'utilitza una varible bool que ens ajudarà a assegurar-nos que si el fitxer es llegeix més d'una vegada, no incrementi
un altre cop els comptadors, de manera que només augmentarà la primera vegada.
*/
void informar_persona(int &comptador_professors, int &comptador_alumnes, char &creacio);
int menu(vector<string> &arr_options);
void recompte_persones(int &comptador_alumnes, int &comptador_professors);
void show_file(int &comptador_alumnes, int &comptador_professors, bool &unic_recompte);
int main()
{
    int comptador_alumnes = 0, comptador_professors = 0, opcio;
    bool unic_recompte = true;
    char creacio;
    vector<string> arr_options = {"Sortir", "Afegir persona", "Llegir fitxer", "Resum persones"};

    do
    {
        opcio = menu(arr_options);
        switch (opcio)
        {
        case 1:
            cout << "Fins a la propera " << endl;
            break;
        case 2:
            cout << "Prem 'E' per crear un estudiant o 'P' per crear un professor: ";
            cin >> creacio;
            informar_persona(comptador_professors, comptador_alumnes, creacio);
            break;
        case 3:
            show_file(comptador_alumnes, comptador_professors, unic_recompte);
            break;
        case 4:
            recompte_persones(comptador_alumnes, comptador_professors);
            break;
        default:
            cout << "Si us plau, introdueix un número que correspogui a una de les opcions" << endl;
            break;
        }
    } while (opcio != 1);
}

int menu(vector<string> &arr_options)
{
    int opcio;
    cout << "Hola , què vols fer?" << endl;
    for (int i = 0; i < arr_options.size(); i++)
    {
        cout << i + 1 << ". " << arr_options[i] << endl;
    }
    cin >> opcio;
    return opcio;
}
void recompte_persones(int &comptador_alumnes, int &comptador_professors)
{
    cout << "Estudiants creats: " << comptador_alumnes << " , professors creats: " << comptador_professors << "\n"
         << endl;
}
void informar_persona(int &comptador_professors, int &comptador_alumnes, char &creacio)
{
    try
    {
        if (creacio == 'P' || creacio == 'p')
        {
            int any_naixement;
            string nom;
            comptador_professors++;
            cout << "Professor: " << comptador_professors << endl;
            cout << "Nom? " << endl;
            cin >> nom;
            cout << "Any naixement? " << endl;
            cin >> any_naixement;
            Professor *nou_professor = new Professor(nom, any_naixement);
            nou_professor->print();
            delete nou_professor;
        }
        else if (creacio == 'E' || creacio == 'e')
        {
            int any_naixement, assignatures;
            string nom;
            comptador_alumnes++;
            cout << "Estudiant: " << comptador_alumnes << endl;
            cout << "Nom? " << endl;
            cin >> nom;
            cout << "Any naixement? " << endl;
            cin >> any_naixement;
            cout << "Assignatures? " << endl;
            cin >> assignatures;
            Estudiant *nou_estudiant = new Estudiant(nom, any_naixement, assignatures);
            nou_estudiant->print();
            delete nou_estudiant;
        }
        else
        {
            throw invalid_argument("La entrada introduïda no és correcte, introdueix 'E' o 'P'.");
        }
    }
    catch (const invalid_argument &error)
    {
        cout << error.what() << "\n"
             << endl;
        if (creacio == 'P' || creacio == 'p')
            comptador_professors--;
        else if (creacio == 'E' || creacio == 'e')
            comptador_alumnes--;
    }
}
void show_file(int &comptador_alumnes, int &comptador_professors, bool &unic_recompte)
{
    char tipus;
    string nom;
    int any_naixement, assignatures;
    ifstream fileText("LlistaPersones.txt");
    while (!fileText.eof())
    {
        fileText >> tipus;
        fileText >> nom;
        fileText >> any_naixement;
        if (tipus == 'E' || tipus == 'e')
        {
            if (unic_recompte)
            {
                comptador_alumnes++;
            }
            fileText >> assignatures;
            cout << "Estudiant(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ", Assignatures ==> " << assignatures << ")" << endl;
        }
        else
        {
            if (unic_recompte)
            {
                comptador_professors++;
            }
            cout << "Professor(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ")" << endl;
        }
    }
    unic_recompte = false;
    fileText.close();
}
