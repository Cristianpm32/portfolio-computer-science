#ifndef Professor_H
#define Professor_H
//Autor: Cristian Prado Méndez
class Professor
{
private:
    string nom;
    int any_naixement;

public:
    Professor(string s, int x);
    void print();
    int getEdat();
};

#endif