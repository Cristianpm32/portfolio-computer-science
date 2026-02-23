/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package P2;
import java.util.Scanner;
/**
 * @author Cristian Prado Méndez
 * @version 1.0
 * Aquest programa comprova si, donades dues cadenes que s'entren per escáner,
 * són iguals o no. Per això, al mètode main() l'usuari introdueix les dues diferents 
 * cadenes. Un cop s'introdueixen, aquestes es comproven al mètode sonIguals(). Com
 * que les cadenes són cícliques, la posició on començi la igualtat és irrellevant, tal que 
 * "adeu" és igual a "deua". Les cadenes comencen a ser comprovades sempre i quan tinguin
 * la mateixa llargada. En cas contrari, ja són diferents.
 */
public class ADN {
     public static void main(String[] args) {
        Scanner cadena1 = new Scanner (System.in);
        System.out.println("Introdueix la primera cadena de ADN: ");
        String cadenaADN1 = cadena1.nextLine();
        Scanner cadena2 = new Scanner (System.in);
        System.out.println("Introdueix la segona cadena de ADN: ");
        String cadenaADN2 = cadena2.nextLine();
        if (cadenaADN1.length() != cadenaADN2.length()){
            System.out.println("Són diferents");
        }
        else{
            char [] adn1 = new char [cadenaADN1.length()];
            char [] adn2 = new char [cadenaADN2.length()];
            /* Identificació seq: Nombres del 0 a adn1.length (estricte)
             * Primer: 0 
             * Següent(i): i++ 
             * FiSeq(i): i >= adn1.length
             * Esquema: Recorregut
             */
            for(int i = 0; i < adn1.length; i++){
                adn1 [i] = cadenaADN1.charAt(i); // S'asigna valor a l'array.
                adn2 [i] = cadenaADN2.charAt(i); // S'asigna valor a l'array.
            }
            if (sonIguals(adn1, adn2)){
                System.out.println("Són la mateixa cadena");
            }
            else{         
                System.out.println("Són diferents");
            }
        }
     }
     /**
      * Aquest mètode comprova si els dos arrays que s'han creat al main() són iguals,
      * és a dir, comprova que les dues cadenes siguin iguals o no, independentment si ho
      * són de forma cíclica o directa.
      * @param cadena1 : Es refereix al primer array, que correson a la primera cadena
      * entrada per escáner. Servirà per fer la comparació entre les dues cadenes.
      * @param cadena2 : Es refereix al primer array, que correson a la segona cadena
      * entrada per escáner. Servirà per fer la comparació entre les dues cadenes.
      * @return : El mètode retorna una variable del tipus boolean, concretament 
      * "iguals". Un cop s'ha fet tota la comparació, retornarà si les dues cadenes són
      * iguals o no.
      */
     static boolean sonIguals(char [] cadena1, char [] cadena2){
         boolean iguals = true;
         int comptador = 0; // Màxim de desigualtats permeses a la comparació.
         int j = 0; // índex de la cadena 1.
         int k = 0; // índex de la cadena 2.
         /* Identificació seq: Nombres del 0 a adn1.length (estricte)
          * Primer: 0 
          * Següent(j): j++ 
          * FiSeq(j): j >= cadena1.length ó comptador > cadena1.length
          * Esquema: Recorregut
          */
         while (comptador <= cadena1.length && j < cadena1.length){
                    /*Si són diferents es reseteja líndex j, fent que l'únic que arriba
                      a fer l'efecte cíclic, mentre que l'altra només va cap endvant, fins
                      arribar al final de la cadena. Si el comptador arriba a ser superior a 
                      la llargada, llavors significaria que no són iguals, ja que no
                      poden haver-hi més lletres diferents que la llargada de la cadena.
                     */
                    if(cadena1 [j] != cadena2 [k]){
                       j = 0;
                       comptador++;
                    }
                    // Si són iguals, els indexos augmenten.
                    else{
                        j++;      
                    }
                    k++;
                    if (k == cadena2.length){
                    // Evitem que l'index estigui fora de rang i es fa l'efecte cíclic
                        k = 0;
                    }
         }
         /* Si s'ha sortit del bucle amb un comptador menor a la llargada de la cadena,
            indica que són iguals, ja que s'ha recoregut tota la cadena que era fixa. 
            En canvi si ha sortit amb un comptador superior a la llargada vol dir que 
            no són iguals.
          */
         iguals = (comptador < cadena2.length) ? iguals : false;  
         return iguals;
     }
            
}
