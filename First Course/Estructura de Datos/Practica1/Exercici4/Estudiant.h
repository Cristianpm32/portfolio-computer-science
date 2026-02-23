#ifndef Estudiant_H
#define Estudiant_H
//Autor: Cristian Prado Méndez
class Estudiant
{
private:
    string nom;
    int assignatures, any_naixement;

public:
    Estudiant(string s, int x, int y);
    void print();
    int getEdat();
};

#endif