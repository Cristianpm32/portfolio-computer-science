#include <iostream>
#include <vector>
#include <string>
using namespace std;
/* Seguint la mecànica de l'exercici 1, s'opta per utilitzar un switch, ja que ara tenim més de 2 opcions a escollir en el menú.
Llavors, en funció de que s'entri en la termnal, el switch accionarà l'opció escollida. Tenim un default si l'entrada no és 
correcta. El switch funciona gràcies al mètode opcioEscollida, que s'encarrega de mostrar el menú i de retornar l'opció 
escollida. En aqeust cas, hem utilitzat una variable bool anomenada fi que canvia el seu valor quan l'opció escollida és 1, cosa
que suposa el fi del bucle.
*/
int opcioEscollida(string &nom);
int main(){
    string nom;
    int opcio;
    bool fi = false;
    cout << "Hola, com et dius? ";
    cin >> nom;
    do{
        switch(opcioEscollida(nom)){
            case 1:
                cout <<  "Fins a la propera " << nom << endl;
                fi = true;
                break;
            case 2:
                cout << "Benvingut/da a l'assignatura d'estructura de dades " << nom << endl;
                break;
            case 3:
                cout << "Hola, com et dius? ";
                cin >> nom;
                cout << "\n";
                break;
            default:
                cout << "Si us plau, introdueix un número que correspogui a una de les opcions" << endl;
                break;
        }
    }    
    while(!fi);
    return 0;
}
int opcioEscollida(string &nom){
        int opcio;
        vector<string> arr_options = {"Sortir", "Benvinguda", "Redefinir nom"};
        cout << "Hola " << nom << ", què vols fer?" << endl;
        for(int i=0; i < arr_options.size(); i++){
            cout << i + 1 << ". " << arr_options[i]<< endl;
        }
        cin >> opcio;
    return opcio;
}