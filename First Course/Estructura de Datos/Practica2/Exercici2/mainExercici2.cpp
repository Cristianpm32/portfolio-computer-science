#include <iostream>
#include <vector>
using namespace std;
#include "CuaEncadenada.h"
#include "Node.h"
int menu(vector<string> &arr_options);
int main()
{
    int key, opcio;
    vector<string> arr_options = {"Inserir element a la cua", "Treure element de la cua", "Consultar el primer element",
                                  "Imprimir tot el contingut de la CuaEstatica", "Sortir"};
    CuaEncadenada<int> *cuaEncadenada = new CuaEncadenada<int>();
    do
    {
        try
        {
            opcio = menu(arr_options);
            switch (opcio)
            {
            case 1:
                cout << "Quin element vols inserir a la cua? ";
                cin >> key;
                cuaEncadenada->enqueue(key);
                break;
            case 2:
                cuaEncadenada->dequeue();
                break;
            case 3:
                cout << cuaEncadenada->getFront() << endl;
                break;
            case 4:
                cuaEncadenada->print();
                break;
            case 5:
                cout << "Fins la propera!" << endl;
                delete cuaEncadenada;
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