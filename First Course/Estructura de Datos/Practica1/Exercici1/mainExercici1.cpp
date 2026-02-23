#include <iostream>
using namespace std;
/* En aquest exercici, s'han utilitzat un array per emmagatzemar les diferents opcions del menú. S'ha emprat un 
bucle for per imprimir cada element del tipus string de l'array corresponent. S'ha fet ús d'un do-while per implementar per 
mostrar el menú almenys una vegada, que es seguirà mostrant fins que s'esculli l'opció 1.
 */
int main(){
    string nom;
    int opcio;
    string  arr_options[]  = {"Sortir",  "Benvinguda"}; 
    cout << "Hola, com et dius? ";
    cin >> nom;
    do{
        cout << "Hola " << nom << ", què vols fer?" << endl;
        for(int i=0; i < 2; i++){
            cout << i + 1 << ". " << arr_options[i]<< endl;
        }
        cin >> opcio;
        if (opcio == 2){
            cout << "Benvingut/da a l'assignatura d'estructura de dades " << nom << endl;
        }
        else if( opcio <= 0 || opcio > 2){
            cout << "Si us plau, introudeix un número que correspogui a una de les opcions" << endl;
        }
    }
    while(opcio != 1);
    cout << "Fins a la propera " << nom << endl;
    return 0;
}