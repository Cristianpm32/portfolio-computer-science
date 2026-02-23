#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
using namespace std;
#include "BSTArbre.h"
#include "AVLArbre.h"
#include "Inventari.h"
int menu(vector<string> arr_options);
template <class T>
float preuQueries(Inventari<T> *inventari)
{
    string linea;
    float preuTotal = 0;
    ifstream fitxer("queries.txt");
    while (getline(fitxer, linea))
    {
        preuTotal += inventari->priceInTimeInterval(pair<string, string>(linea, linea));
    }
    fitxer.close();
    return preuTotal;
}
template <class T>
void menuInventari()
{
    int avlBst, opcio;
    string nomArxiu, data1, data2, product;
    float preuTotal = 0;
    pair<string, string> dates;
    ifstream fitxer;
    vector<string> arr_options = {"Especificar la ruta del fitxer pel Gestor de Transaccions",
                                  "Mostra totes les transaccions ordenades temporalment",
                                  "Mostra totes les transaccions en ordre temporal invers",
                                  "Mostra el total de l'inventari", "Mostra el total de l'inventari entre dues dates",
                                  "Mostra el total de l'inventari entre dues dates per un producte",
                                  "Mostra el total de totes les transaccions efectuades en les dates llistades", "Sortir"};
    Inventari<T> *inventari = new Inventari<T>(0.21);
    do
    {
        try
        {
            opcio = menu(arr_options);
            switch (opcio)
            {
            case 1:
                cout << "Introdueix la ruta del fitxer: ";
                cin >> nomArxiu;
                inventari->loadFromFile(nomArxiu);
                break;
            case 2:
                inventari->printAll();
                break;
            case 3:
                inventari->printAllReverse();
                break;
            case 4:
                cout << "El total de les despeses de l'inventari és: " << inventari->priceInTotal() << endl;
                break;
            case 5:
                cout << "Introdueix la primera data: ";
                cin >> data1;
                cout << endl;
                cout << "Introdueix la segona data: ";
                cin >> data2;
                cout << endl;
                dates.first = data1;
                dates.second = data2;
                cout << "El total de les despeses de l'inventari en aquest interval és: " << inventari->priceInTimeInterval(dates) << endl;
                break;
            case 6:
                cout << "Introdueix la primera data: ";
                cin >> data1;
                cout << endl;
                cout << "Introdueix la segona data: ";
                cin >> data2;
                cout << endl;
                cout << "Introdueix l'identificador del producte: ";
                cin >> product;
                dates.first = data1;
                dates.second = data2;
                cout << "El total de les despeses de l'inventari en aquest interval amb aquest producte és: " << inventari->priceInTimeIntervalByProduct(dates, product) << endl;
                break;
            case 7:
                cout << "El total de les despeses de queries és: " << preuQueries(inventari) << endl;
                break;
            case 8:
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

    } while (opcio != 8);
}
int main()
{
    cout << endl
         << endl
         << "------------------" << endl;
    cout << "|    BSTArbre    |" << endl;
    cout << "------------------" << endl
         << endl
         << endl;
    menuInventari<BSTArbre<string, FoodPackage>>();

    cout << endl
         << endl
         << "------------------" << endl;
    cout << "|    AVLArbre    |" << endl;
    cout << "------------------" << endl
         << endl
         << endl;
    menuInventari<AVLArbre<string, FoodPackage>>();
    return 0;
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
