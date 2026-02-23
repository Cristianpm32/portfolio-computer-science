#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
#include "Estudiant.h"
/*En aquest exercici, s'ha emprat la utilització de classes per fer POO. En aquest cas, el menú dóna 2 opcions, sortir o 
informar un estudiant. Per això, s'ha crat una classe Estudiant que en cas d'escollir l'opció 2, es crida al mètode 
informar_estudiant, i s'envia per referència comptador_alumnes, per així saber el número de l'estudiant que s'informa. En 
aquest mètoda, es crea un punter del tipus Esudiant, cridant al seu constructor amb els paràmetres que s'han
demanat prèviament al mateix mètode. Com que no necessitem res més que imprimir per pantalla les dades, un cop s'ha fet això,
s'esborra el punter i alliberem memòria dinàmica. A més a més, per l'any de naixement, si aquest és negatiu o supera l'actual, 
es llença un throw des del constructor, de forma que no es crea l'objecte ni tampoc augmenta el comptador d'estudiants.
*/
void informar_estudiant(int &comptador_alumnes);
int menu(vector<string> &arr_options);
int main()
{
    int comptador_alumnes = 0, opcio;
    vector<string> arr_options = {"Sortir", "Informar Estudiant"};

    do
    {
        opcio = menu(arr_options);
        switch (opcio)
        {
        case 1:
            cout << "Fins a la propera " << endl;
            break;
        case 2:
            informar_estudiant(comptador_alumnes);
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

void informar_estudiant(int &comptador_alumnes)
{
    try
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
    catch (const invalid_argument &error)
    {
        cout << error.what() << endl;
        comptador_alumnes--;
    }
}