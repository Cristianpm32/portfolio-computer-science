#include <chrono>
#include <iostream>
#include <fstream>
#include "AVLArbre.h"
#include "BSTArbre.h"
#include "FoodPackage.h"
using namespace std;
template <class T>
void loadFromFile(T *arbre, string file_path)
{
    ifstream fitxer(file_path);
    string dataTime, productId, quantitat, preu;
    getline(fitxer, dataTime);             // S'executa una unica vegada per saltar-se la primera linia dels arxius (headers).
    while (getline(fitxer, dataTime, ',')) // opcio alternativa : while(!fitxer.eof()) i posar el getline a dins del while
    {
        getline(fitxer, productId, ',');
        getline(fitxer, quantitat, ',');
        getline(fitxer, preu);
        arbre->insert(dataTime, FoodPackage(dataTime, productId, stoi(quantitat), stof(preu)));
    }
    fitxer.close();
}
/*
Operació                                                         |      BSTArbre (µs)     |     AVLArbre(µs)     |
------------------------------------------------------------------------------------------------------------------
Inserció arbre petit  (transactions-small.txt)                   |          504824        |         114507       |
Inserció arbre petit barrejat  (transactionssmall.shuffled.txt)  |           30049        |        191924        |
Inserció arbre gran  (transactions-large.txt)                    |          5133311       |        1207126       |
Inserció arbre gran (transactionslarge.shuffled.txt)             |          319369        |        2077361       |
Cerca arbre petit barrejat                                       |             5          |           15         |
Cerca arbre gran barrejat                                        |             5          |           16         |
------------------------------------------------------------------------------------------------------------------
*/
int main()
{
    AVLArbre<string, FoodPackage> *tree1 = new AVLArbre<string, FoodPackage>();
    BSTArbre<string, FoodPackage> *tree2 = new BSTArbre<string, FoodPackage>();
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    loadFromFile(tree1, "transactions-small.txt");
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " us." << endl;
    chrono::steady_clock::time_point begin2 = chrono::steady_clock::now();
    loadFromFile(tree2, "transactions-small.txt");
    chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end2 - begin2).count() << " us." << endl;
    delete tree1;
    delete tree2;
    tree1 = new AVLArbre<string, FoodPackage>();
    tree2 = new BSTArbre<string, FoodPackage>();
    chrono::steady_clock::time_point begin3 = chrono::steady_clock::now();
    loadFromFile(tree1, "transactions-small.shuffled.txt");
    chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end3 - begin3).count() << " us." << endl;
    chrono::steady_clock::time_point begin4 = chrono::steady_clock::now();
    loadFromFile(tree2, "transactions-small.shuffled.txt");
    chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end4 - begin4).count() << " us." << endl;
    chrono::steady_clock::time_point begin9 = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
    {
        tree1->valuesOf("2021-02-03");
    }
    chrono::steady_clock::time_point end9 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end9 - begin9).count() << " us." << endl;
    chrono::steady_clock::time_point begin10 = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
    {
        tree2->valuesOf("2021-02-03");
    }
    chrono::steady_clock::time_point end10 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end10 - begin10).count() << " us." << endl;
    delete tree1;
    delete tree2;
    tree1 = new AVLArbre<string, FoodPackage>();
    tree2 = new BSTArbre<string, FoodPackage>();
    chrono::steady_clock::time_point begin5 = chrono::steady_clock::now();
    loadFromFile(tree1, "transactions-large.txt");
    chrono::steady_clock::time_point end5 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end5 - begin5).count() << " us." << endl;
    chrono::steady_clock::time_point begin6 = chrono::steady_clock::now();
    loadFromFile(tree2, "transactions-large.txt");
    chrono::steady_clock::time_point end6 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end6 - begin6).count() << " us." << endl;
    delete tree1;
    delete tree2;
    tree1 = new AVLArbre<string, FoodPackage>();
    tree2 = new BSTArbre<string, FoodPackage>();
    chrono::steady_clock::time_point begin7 = chrono::steady_clock::now();
    loadFromFile(tree1, "transactions-large.shuffled.txt");
    chrono::steady_clock::time_point end7 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end7 - begin7).count() << " us." << endl;
    chrono::steady_clock::time_point begin8 = chrono::steady_clock::now();
    loadFromFile(tree2, "transactions-large.shuffled.txt");
    chrono::steady_clock::time_point end8 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end8 - begin8).count() << " us." << endl;
    chrono::steady_clock::time_point begin11 = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
    {
        tree1->valuesOf("2021-02-03");
    }

    chrono::steady_clock::time_point end11 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end11 - begin11).count() << " us." << endl;
    chrono::steady_clock::time_point begin12 = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
    {
        tree2->valuesOf("2021-02-03");
    }
    chrono::steady_clock::time_point end12 = chrono::steady_clock::now();
    cout << "Temps transcorregut: " << chrono::duration_cast<chrono::microseconds>(end12 - begin12).count() << " us." << endl;
    delete tree1;
    delete tree2;
}