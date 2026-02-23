#include <iostream>
#include <vector>
#include "CuaEstatica.h"

using namespace std;
int menu(vector<string> &arr_options);
int main()
{
    int key, opcio, maxSize;
    vector<string> arr_options = {"Inserir element a la cua", "Treure element de la cua", "Consultar el primer element",
                                  "Imprimir tot el contingut de la CuaEstatica", "Imprimir les posicions del front i el rear", "Sortir"};
    cout << "Quina vols que sigui la mida de la CuaEstatica? ";
    cin >> maxSize;
    CuaEstatica *cuaEstatica = new CuaEstatica(maxSize);
    do
    {
        opcio = menu(arr_options);
        switch (opcio)
        {
        case 1:
            cout << "Quin element vols inserir a la cua? ";
            cin >> key;
            try
            {
                cuaEstatica->enqueue(key);
            }
            catch (const out_of_range &error)
            {
                cout << error.what() << "\n\n";
            }
            break;
        case 2:
            try
            {
                cuaEstatica->dequeue();
            }
            catch (const out_of_range &error)
            {
                cout << error.what() << "\n\n";
            }
            break;
        case 3:
            try{
                cout << cuaEstatica->getFront() << endl;
            }
            catch(const out_of_range &error){
                cout << error.what() << "\n\n";
            }
            break;
        case 4:
            cuaEstatica->print();
            break;
        case 5:
            cuaEstatica->printFrontRear();
            break;
        case 6:
            cout << "Fins la propera!" << endl;
            delete cuaEstatica;
            break;
        default:
            cout << "Si us plau, introdueix un número que correspogui a una de les opcions" << endl;
            break;
        }
    } while (opcio != 6);
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