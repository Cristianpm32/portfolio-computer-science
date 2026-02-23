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
 * @data Nov. 21
 * Descripció:
 * Aquest programa realitza un tauler per jugar al joc Flota Naval i comprova 
 * si la posició que ocupen els vaixells és correcta o no. Es considera que és correcta
 * si els vaixells diferents no es toquen, de forma diagonal inclosa.
 * El mètode main() fa que el jugador introdueixi la mida del tauler i es crea un array bi-
 * dimensional (matriu) que serà el tauler. El jugador va introduint o bé un 0 (indica
 * que a la casella només hi ha aigua) o un 1 (indica que a la casella hi ha un vaixell).
 * un cop es crea el tauler, es crida al mètode esCorrecte() per comprovar si els vaixells 
 * estan posicionats correctament o no, segons les regles anomenades anteriorment.
 */
public class FlotaCorrecteBatallaNaval {
    public static void main(String[] args) {
        Scanner teclat = new Scanner (System.in);
        System.out.print("Introdueix la mida del tauler: ");
        int mida = teclat.nextInt();
        if (mida == 0){
            System.out.println("Fi del joc");
        }
        else{
            int [][] tauler = new int [mida][mida];
            System.out.println("Introdueix les dades del tauler (0 és aigua, 1 és part del vaixell): ");
            /* Identificació seq: Nombres del 0 a mida (estricte)
             * Primer: 0 
             * Següent(i): i++ 
             * FiSeq(i): i >= mida
             * Esquema: Recorregut
             */
            for (int i = 0; i < mida; i++){
                /* Identificació seq: Nombres del 0 a mida (estricte)
                 * Primer: 0 
                 * Següent(j): j++ 
                 * FiSeq(j): j >= mida
                 * Esquema: Recorregut
                 */
                for (int j = 0; j < mida; j++){
                    tauler [i][j] = teclat.nextInt(); // Dóna a cada element de l'array un valor.
                }
            }
            if (taulerCorrecte(tauler)){
                System.out.println("El tauler és correcte");
            }
            else{
                System.out.println("El tauler no és correcte");
            }
        }
    }
    /**
     * Aquest mètode serveix per comprovar si el tauler que s'ha introduit és correcte.
     * És a dir, donades les posicions dels vaixells comprova si aquestsestan posicionats
     * d'acord amb les regles.
     * @param tauler : Aquest paràmetre és el que rep del main(), que en aquest cas
     * és un array bidimensional. La funció comprovarà aquest paràmetre.
     * @return : La funció retorna si el tauler compleix amb les condicions o no, 
     * mitjançant una variable del tipus boolean ("correcte").
     */
    static boolean taulerCorrecte(int [][] tauler){
        boolean correcte = true;
         /* Identificació seq: Nombres del 0 a tauler.length (estricte)
          * Primer: 0 
          * Següent(i): i++ 
          * FiSeq(i): i >= tauler.length
          * Esquema: Recorregut
          */
        for (int i = 0; i < tauler.length; i++){
             /* Identificació seq: Nombres del 0 a tauler.length (estricte)
              * Primer: 0 
              * Següent(i): j++ 
              * FiSeq(i): j >= tauler.length
              * Esquema: Recorregut
              */
            for (int j = 0; j < tauler.length; j++){
                if (tauler [i][j] == 1){
                    /* Aquesta condició fa que comprovi si els vaixells compleixen
                     * si es toquen o no diagonalment. S'afegeixen condicions als
                     * indexos per evitar que siguin índexos fora del rang de 
                     * l'array.
                     */
                    if ((i + 1 < tauler.length && j + 1 < tauler.length && tauler [i+1][j+1] == 1) || 
                        (i - 1 >= 0 && j + 1 < tauler.length && tauler [i-1][j+1] == 1)|| 
                        (j - 1 >= 0 && i + 1 < tauler.length && tauler [i+1][j-1] == 1)|| 
                            (i - 1 >= 0 && j - 1 >= 0 && tauler [i-1][j-1] == 1)){
                            correcte = false;
                    }
                    /* Aquesta condició comprova si els vaixells es toquen en forma de L
                     * o no, en el cas que e vaixell que s'estigui comprovant sigui
                     * horitzontal.
                     */
                    else if (((i + 1 < tauler.length && tauler [i+1][j] == 1) && (i - 1 >= 0 && tauler [i-1][j] == 0 )) || 
                             ((i + 1 < tauler.length && tauler [i+1][j] == 0) && (i - 1 >= 0 && tauler [i-1][j] == 1))){
                        // Comprova que no tingui vaixells just amunt o sota seu.
                        if ((j - 1 >= 0 && tauler[i][j-1] == 1) || (j + 1 < tauler.length && tauler [i][j+1] == 1)){
                            correcte = false;
                        }
                    }
                    /* Aquesta condició comprova si els vaixells es toquen en forma de L
                     * o no, en el cas que el vaixell que s'estigui comprovant sigui
                     * vertical.
                     */
                    else if (((j + 1 < tauler.length && tauler [i][j+1] == 1) && (j - 1 >= 0 && tauler [i][j-1] == 0)) || 
                             ((j + 1 < tauler.length && tauler [i][j+1] == 0) && (j - 1 >= 0 && tauler [i][j-1] == 1 ))){
                        // Comprova que el vaixell no tingui vaixells a l'esquerra o a la dreta seu.
                        if ((i - 1 >= 0 && tauler[i-1][j] == 1) || (i + 1 < tauler.length && tauler [i+1][j] == 1)){
                            correcte = false;
                        }
                    }
                }
            } 
        }
        return correcte;
    }
}
