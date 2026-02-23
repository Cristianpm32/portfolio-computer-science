/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package P2;

/**
 * @author Cristian Prado Méndez
 * @version 1.0
 * @data Nov. 21
 * Aquest programa es basa en el joc de Yahtzee. En aquest programa, es llencen 
 * 5 daus. Si els 5 daus coicncideixen en el seu valor, llavors el jugador haurà
 * guanyat. En cas contrari, no. Es crea un array al main(), que es va omplint al
 * mètode tiraDados()vamb les tirades de dau (mitjançant un nombre aleatori entre 
 * l'1 i el 6). Després es comprova si aquests nombres són iguals o són diferents
 * al mètode esYahtzee().
 */
public class Yahtzee {
    public static void main(String[] args) {
        int [] daus = new int [5];
        tiraDados(daus); // Es crida al mètode per  tenir un array amb els valors.
        System.out.println(" ");
        if (esYahtzee(daus)){
            System.out.println("Yahtzee!");
        }
        else{
           System.out.println("Llàstima, torna a intentar-ho!"); 
        }
    }
    /**
     * Aquest mètode realitza un array que es va omplint dels nombres aleatoris.
     * No retorna res, ja que és un void.
     * @param daus : És l'array que emmagatzema els valors.
     */
    static void tiraDados(int [] daus){
         /* Identificació seq: Nombres del 0 a daus.length (estricte)
          * Primer: 0 
          * Següent(i): i++ 
          * FiSeq(i): i >= daus.length
          * Esquema: Recorregut
          */
        for(int i = 0; i < daus.length; i++){
            daus[i] = (int) (Math.random() * 6 +1); // S'assigna valor a l'array.
            System.out .print(daus[i] + " ");
        }
    }
    /**
     * Aquest mètode comprova si els valors dels daus coincideixen o no
     * @param daus: Aquest paràmetre és un array, que és el que es rep pel pas de
     * paràmeres, que corresponia a l'array que es crea a tiraDados()
     * @return : El mètode retorna una booleana, que en aquest cas retorna si els
     * valors són iguals o no, mitjaçant la variable iguals, del tipus boolean.
     */
    static boolean esYahtzee(int [] daus){
        boolean iguals = true;
        int i = 1;
         /* Identificació seq: Nombres del 1 a daus.length (estricte)
          * Primer: 1 
          * Següent(i): i++ 
          * FiSeq(i): i >= daus.length
          * Esquema: Cerca Condició cerca: daus[i] != daus[i-1]
          */
        while(iguals && i < daus.length){
            if (daus[i] != daus[i-1]){
                iguals = false;
            }
            i++;
        }    
        return iguals;    
    }
 }   
 
