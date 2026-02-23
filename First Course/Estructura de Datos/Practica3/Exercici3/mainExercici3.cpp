#include <iostream>
#include "BSTArbre.h"
#include "AVLArbre.h"

int main()
{
    AVLArbre<int, int> *tree1 = new AVLArbre<int, int>();
    int testKeys[] = {2, 0, 8, 45, 76, 5, 3, 40};
    int testValues[] = {5, 5, 1, 88, 99, 12, 9, 11};
    for (int i = 0; i < 8; i++)
    {
        cout <<  "Inserta a l'arbre l'element "<< tree1->insert(testKeys[i], testValues[i])->getKey() << endl;

    }
    tree1->printPreorder();
    cout << endl;
    tree1->printInorder();
    cout << endl;
    tree1->printPostorder();
    cout << endl;
    tree1->printSecondLargestKey();
    cout << endl;
    AVLArbre<int, int> tree2 = AVLArbre<int, int>(*tree1);
    tree2.printPreorder();
    tree1->valuesOf(45);
    tree1->mirrorTree();
    tree1->printInorder();
    tree1->getLeafNodes();
    delete tree1;
}