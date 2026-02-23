#ifndef CUAESTATICA_H
#define CUAESTATICA_H

class CuaEstatica
{
public:
    CuaEstatica(const int max_size);
    virtual ~CuaEstatica();
    void enqueue(const int key);
    void dequeue();
    bool isFull();
    bool isEmpty();
    void print();
    const int getFront();

    void printFrontRear();

private:
    int _max_size;
    int _size;
    int _front;
    int _rear;
    int *_data;
};

#endif
/*
Quina condició hem d’imposar en una cua estàtica no circular per comprovar si està plena?

RESPOSTA: En el cas de no ser circular, cal imposar que en el cas que el rear sigui igual a max_size, ja que en el cas que
s'elimini un element, com no és circular, tots els elements es desplacen cap a l'esquerra i, per tant, el rear decreix. Això
provoca que l'unica forma de saber si la cua està plena o no sigui aquesta.

Aquesta condició és suficient en el cas de ser circular?

RESPOSTA: No és suficient, perquè tal i com hem vist, el fet que sigui circular implica que el rear, un cop arribi a la màxima
posició de l'array i s'insereixi el següent element, donarà la volta i tornarà a la posició 0. Aquesta implementació del TAD
implica que el front, quan s'elimini un element de la cua, es mourà una posició, de forma que pot arribar el moment en el que
el front i el rear estiguin a la mateixa posició, i això comporta problemes en el moment de fer el print de la cua. Per tant,
necesssitem d'una tercera variable a la qual anomenarem size. Aquesta varibale ens serà util per saber si el fet de que estiguin
a la mateixa posició comporta que la cua estigui plena o estigui buida. Efectivament, si la variable size és igual a max_size,
la cua estarà plena, en cas contrari estarà buida.

La variable _max_size és necessària en el cas de ser una cua no circular?

RESPOSTA: L'única funció que tindria el max_size es definir la màxima capacitat de la cua, com passa amb un array qualsevol i
llavors si el rear té el mateix valor que el max_size, ens indica que la cua està plena.

Per a què utilitzem aquesta variable per les cues circulars?

RESPOSTA: En el cas de les cues circulars, trobem que max_size ens serveix de més utilitat que a una cua no circular, ja que en 
el cas de ser una cua circular, disposemm d'una variable size que augmenta per cada inserció i disminueix per cada eliminació
d'element. Per tant, ens servirà per comparar-la amb size, i en el cas de tenir el mateix valor, la cua estarà plena i en cas
contrari, no ho estarà. A més a més, serveix per comparar-la també amb el rear i el front, que en aquesa implementeació es van 
movent els dos, en funció de produir-se una inserció o elminació. Per tant, si una d'aquestes variables arriba a tenir el mateix
valor  que el max_size, passa a tenir valor 0, de forma que dona la volta. Llavors, en el cas de que el front i el rear estiguin
en la mateixa posició, la variable size es compararà amb el max_size. En el cas d'estar plena, size tindrà el mateix valor que el
max_size, i en cas de no tenir el mateix valor, size tindrà valor 0 i per tant, la cua estarà buida.
 */