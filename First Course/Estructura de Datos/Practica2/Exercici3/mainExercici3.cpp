#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
using namespace std;
#include "CuaEncadenada.h"
#include "Comanda.h"
int menu(vector<string> arr_options);
void saveFile(CuaEncadenada<Comanda> &llistacomandes);
int main()
{
    int opcio;
    string id,menjar, quantitat, hora, key;
    vector<string> arr_options = {"Llegir un fitxer amb les entrades de les comandes", "Eliminar una comanda",
                                  "Inserir n entrades de comandes des de teclat (0 per finalitzar)", "Imprimir per pantalla la cua de comandes", "Sortir"};
    CuaEncadenada<Comanda> llistacomandes;
    do
    {
        try
        {
            opcio = menu(arr_options);
            switch (opcio)
            {
            case 1:
                saveFile(llistacomandes);
                break;
            case 2:
                cout << "La comanda " << llistacomandes.getFront() << " ha estat eliminada correctament. " << endl;
                llistacomandes.dequeue();
                break;
            case 3:
                do
                {   cin.ignore();
                    cout << "Número de la comanda: ";
                    getline(cin, id);
                    cout << "Què vols demanar? ";
                    getline(cin, menjar);
                    cout << "Quantitat que es vol demanar: ";
                    getline(cin, quantitat);
                    cout << "Indica hora de la comanda realitzada: ";
                    getline(cin, hora);
                    Comanda nova_comanda = Comanda(stoi(id), menjar, stoi(quantitat), hora);
                    llistacomandes.enqueue(nova_comanda);

                    cout << "Per finalitzar l'entrada de comandes prem 0. Si no, prem qualsevol tecla. " << endl;
                    cin >> key;
                } while (key != "0");
                break;
            case 4:
                llistacomandes.print();
                break;
            case 5:
                cout << "Fins la propera!" << endl;
                break;
            default:
                cout << "Si us plau, introdueix un número que correspogui a una de les opcions" << endl;
                break;
            }
        }
        catch (const exception &error)
        {
            cout << error.what() << "\n\n";
        }

    } while (opcio != 5);
}
int menu(vector<string> arr_options)
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
void saveFile(CuaEncadenada<Comanda> &llistacomandes)
{
    ifstream fitxer("LlistaComandes.txt");
    string menjar, hora, identificador, quantitat;
    while (getline(fitxer, identificador, ',')) // opcio alternativa : while(!fitxer.eof()) i posar el getline a dins del while
    {
        // getline(fitxer, identificador, ',');
        identificador.erase(0, 2);
        getline(fitxer, menjar, ',');
        getline(fitxer, quantitat, ',');
        getline(fitxer, hora);
        llistacomandes.enqueue(Comanda(stoi(identificador), menjar, stoi(quantitat), hora));
    }
    fitxer.close();
}
