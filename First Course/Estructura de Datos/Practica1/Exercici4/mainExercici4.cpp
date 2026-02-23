#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
#include "Professor.h"
#include "Estudiant.h"
/* Segueix la mateixa dinámica de POO de l'exercici 3, amb la diferència que ara tenim una nova classe, anomenada Professor.
Aquesta és molt similar a Estudiant, amb la diferència que no es demana per paràmetre al constructor el nombre d'assignatures.
Si s'escull l'opció 2, es demanrà per entrada la lletra 'e'('E') o 'p'('P'). En cas de no rebre cap d'aquestes, es llença un throw
al catch i s'imprimeix que l'entrada no és vàlida. En cas d'entrada correcte, es farà dins del ry un if-else if, segons l'entrada. 
Si és e, es crearà un punter de la classe Estudiant, en cas contrari de la classe Professor. En el cas 3, es crida al mètode 
recompte_persones passant per referència els comptadors, de forma que es puguin imprimir i quan s'actualitzin i es cridi
un altre cop la funció, imprimeixi el valor corresponent. En el cas del catch, ara distingim en funció de si ha estat un
objecte de Professor o Estudiant, per així tornar a tenir el comptador al valor anterior, ja que no s'ha creat l'objecte, degut
al throw que s'ha llençat.
*/
void informar_persona(int &comptador_professors, int &comptador_alumnes, char creacio);
int menu(vector<string> &arr_options);
void recompte_persones(int &comptador_alumnes, int &comptador_professors);
int main()
{
    int comptador_alumnes = 0, comptador_professors = 0, opcio;
    char creacio;
    vector<string> arr_options = {"Sortir", "Afegir persona", "Resum persones"};

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
void informar_persona(int &comptador_professors, int &comptador_alumnes, char creacio)
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
