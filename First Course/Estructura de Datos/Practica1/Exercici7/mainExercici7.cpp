#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "PersonaContainer.h"
#include "Professor.h"
#include "Estudiant.h"
using namespace std;
/*En aquest exercici, mantenim la classe mare i les filles, i el programa pateix una modificació, on ara els punters de les
diferents classes sí que son importants, ja que es guarden els elements en un vector de la classe Persona*, un vector que guarda 
punters de les classes derivades de Persona. Aquest vector ens servirà per poder implementar 3 opcions més del menú, que són 
donar l'edat del membre més jove, del més gran o fer un print() de tota la col·lecció. Per poder fer aquests mètodes, s'ha creat
una classe anomenada PersonaContainer, que és un vector que conté punters d'aquestes classes. 
----------------------------------------------------PREGUNTES EXERCICI 7------------------------------------------------------------
1-Què ens permet fer l’herència  que  no  podríem  fer  altrament? 
RESPOSTA: L'herència ens permet definir noves classes a partir d'unes ja existents, amb l'objectiu de reutilitzar el codi d'aaquestes
classes que anomenem "mare" i extendre la funcionalitat d'aquesta, generant una jerarquia de classes, on la classe base seria una 
superclasse i les altres classes que deriven. El fet de derivar implica que pot heretar els atributs i mètodes de la classe mare
i a més a més afegir-ne de nous, propis de la seva classe.

2-Que passa si  print() de la classe  Persona  no és  virtual?  Per  què?   
RESPOSTA: El fet de que el print() de la classe Persona no sigui virtual provoca que en el moment de cridar a aquest mètode des
del vector de la classe PersonaContainer, com aquest vector conté punters de la classe Persona, cridaria directament al print()
de la classe Persona, i no al corrsponent de Professor o Estudiant, ja que el que fa virtual és permetre que un mètode d'aquest tipus,
un cop declarat en la classe mare, pugui ser definit de diferents formes en les diferents classes filles. Els mètodes virtual són
característics de l'anomenat polimorfisme, i son declarats en les classes mares i en les filles són definits, en funció de les característiques específiciques de cadascuna.

3-Perquè els constructors  i  destructors  els  hem  de  cridar  a  les  classes  derivades  i  no  a  la  classe  base? 
RESPOSTA: Els constructors i els destructors els hem de cridar des de les classes derivades perquè en el cas de que el constructor
fos cridat des de la classe mare, crearia un objecte de la classe mare, però no de la classe derivada, ja que per jerarquia
la classe mare no sap quines són les seves derivades. Això provocaria que es pogués crear un objecte de la classe Persona, però
no tindria les característiques ni els mètodes de la classe derivada. En canvi, les classes derivades sí que saben d'on venen, és
a dir, saben de l'existència de la classe mare. Per tant, si escrida al constructor des de la classe derivada, crearà un objecte
d'aquesta classe, que a la mateixa vegada seria de la classe mare. En el moment d'execució, primer es crida al constructor de la
classe mare, per tal de tenir els atributs i els mètodes d'herència, i després al propi constructor de la classe. En el cas del
constructor, si no es crida des de la classe derivada, destruiria la classe mare, però mai la derivada, pel mateix argument que 
amb els constructors. Per tant, si es crida des de la derivada, es destrueix la classe derivada i com a conseqüència la classe mare.
En el moment d'execució, per tant, primer es crida al destructor de la classe derivada i després al de la classe mare, per tal
d'eliminar l'objecte per complet.

4-Anomena els membres de dades definits en els teus programes i digues a quina classe pertanyen. Explica les  decisions  de  
visibilitat  de  cadascun 
RESPOSTA: classe Estudiant: private: int assignatures; || public: Estudiant(string s, int x, int y); void print(); ~Estudiant();
Els atributs privats perquè no volem que es pugui accedir excepte en la pròpia classe. En canvi, volem que els mètodes, destructor 
i constructor sí que es pugin accedir, per exemple, des del main mitjançant un objecte de la seva classe.
classe Professor: public: Professor(string s, int x); void print(); ~Professor();
Com que no tenim un atribut específic diferent dels de la classe Persona, només tenim els mètodes, destructor i constructor, 
que volem que siguin públics per poder accedir-hi des del main, mitjançant un objecte de la classe Professor.
classe Persona: protected: string nom; int any_naixement; || public: Persona(string s, int x); virtual void print(); 
int getEdat(); virtual ~Persona();
Primer de tot, els mètodes, destructor i constructor són publics perquè volem que puguin ser accessibles en arxius diferents a 
la pròpia classe. De fet, aquests membres de dades són acccesibles des de les classes Estudiant i Professor, ja que són classes
filles de Persona. Per tant, hereten aquest mètodes i criden al constructor i al destructor. Per altra banda, tenim els protected,
els quals volem que només puguin ser visibles per les classes derivades i no per altres arxius o espais. En aquest cas, veiem que
els dos atributs són característics de les dues classes derivades.
classe PersonaContainer: private: std::vector<Persona*> elements; public: int getOlder(); int getYounger(); 
void addPersona(Persona* persona); void print(); ~PersonaContainer();
Tenim com a privat el vector que s'emprarà en tots el mètodes de la classe PersonaContainer, aquest vector guarda punters de la
classe Persona, és a dir, ja sigui del tipus Estudiant o Professor. Després, tenim els mètodes i destructor públics, ja que volem
que pugin ser cridats des del main, per tal de poder emmagatzemar les persones i tractar les seves dades, utilitzant un bucle
for i iterador.

5-L’iterador  que  recorre  les  figures,  quant  s’incrementa  cada  cop?  Perquè? 
RESPOSTA: L' iterador s'incrementa cada vegada en 1, ja que volem recòrrer cadascun dels punters i poder extreure informació 
del que hi ha a la seva referència, a partir de cridar als mètodes de la classe la referència de la qual emmagatzema.
*/


void informar_persona(int &comptador_professors, int &comptador_alumnes, char &creacio, PersonaContainer *persones);
int menu(vector<string> &arr_options);
void recompte_persones(int &comptador_alumnes, int &comptador_professors);
void show_file(int &comptador_alumnes, int &comptador_professors, bool &unic_recompte, PersonaContainer *persones);

int main()
{
    int comptador_alumnes = 0, comptador_professors = 0, opcio;
    bool unic_recompte = true;
    char creacio;
    vector<string> arr_options = {"Sortir", "Afegir persona", "Llegir fitxer", "Resum persones", "Mostrar l'edat de la persona més jove", "Mostrar l'edat de la persona més gran", "Mostrar col·lecció de persones"};
    PersonaContainer *persones = new PersonaContainer();

    do
    {
        opcio = menu(arr_options);
        switch (opcio)
        {
        case 1:
        {
            cout << "Fins a la propera " << endl;
            delete persones;
            break;
        }
        case 2:
            cout << "Prem 'E' per crear un estudiant o 'P' per crear un professor: ";
            cin >> creacio;
            informar_persona(comptador_professors, comptador_alumnes, creacio, persones);
            break;
        case 3:
            show_file(comptador_alumnes, comptador_professors, unic_recompte, persones);
            break;
        case 4:
            recompte_persones(comptador_alumnes, comptador_professors);
            break;
        case 5:
            cout << "La persona més jove té " << persones->getYounger() << " anys" << endl;
            break;
        case 6:

            cout << "La persona més gran té " << persones->getOlder() << " anys" << endl;
            break;
        case 7:
            persones->print();
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
void informar_persona(int &comptador_professors, int &comptador_alumnes, char &creacio, PersonaContainer *persones)
{
    try
    {
        if (creacio == 'P' || creacio == 'p')
        {
            int any_naixement;
            string nom;
            cout << "Professor: " << comptador_professors + 1 << endl;
            cout << "Nom? " << endl;
            cin >> nom;
            cout << "Any naixement? " << endl;
            cin >> any_naixement;
            Professor *nou_professor = new Professor(nom, any_naixement);
            persones->addPersona(nou_professor);
            nou_professor->print();
            comptador_professors++;
        }
        else if (creacio == 'E' || creacio == 'e')
        {
            int any_naixement, assignatures;
            string nom;
            cout << "Estudiant: " << comptador_alumnes + 1 << endl;
            cout << "Nom? " << endl;
            cin >> nom;
            cout << "Any naixement? " << endl;
            cin >> any_naixement;
            cout << "Assignatures? " << endl;
            cin >> assignatures;
            Estudiant *nou_estudiant = new Estudiant(nom, any_naixement, assignatures);
            persones->addPersona(nou_estudiant);
            nou_estudiant->print();
            comptador_alumnes++;
        }
        else
        {
            throw invalid_argument("La entrada introduïda no és correcte, introdueix 'E' o 'P'.");
        }
    }
    catch (const invalid_argument &error)
    {
        cout << error.what() << "\n\n";
    }
}

void show_file(int &comptador_alumnes, int &comptador_professors, bool &unic_recompte, PersonaContainer *persones)
{
    char tipus;
    string nom;
    int any_naixement, assignatures;
    ifstream fileText("LlistaPersones.txt");
    while (!fileText.eof())
    {
        fileText >> tipus;
        fileText >> nom;
        fileText >> any_naixement;
        if (tipus == 'E' || tipus == 'e')
        {
            fileText >> assignatures;
            if (unic_recompte)
            {
                Estudiant *nou_estudiant = new Estudiant(nom, any_naixement, assignatures);
                persones->addPersona(nou_estudiant);
                comptador_alumnes++;
            }
            cout << "Estudiant(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ", Assignatures ==> " << assignatures << ")" << endl;
        }
        else
        {
            if (unic_recompte)
            {
                Professor *nou_professor = new Professor(nom, any_naixement);
                persones->addPersona(nou_professor);
                comptador_professors++;
            }
            cout << "Professor(Nom ==> " << nom << ", Naixement ==> " << any_naixement << ")" << endl;
        }
    }
    unic_recompte = false;
    fileText.close();
}
