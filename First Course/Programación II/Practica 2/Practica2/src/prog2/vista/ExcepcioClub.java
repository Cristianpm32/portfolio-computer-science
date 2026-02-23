/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog2.vista;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class ExcepcioClub extends Exception {
    /**
     * Constructor d'ExcepcioClub.
     * 
     * @param missatgeError amb el tipus d'execpció.
     */
    public ExcepcioClub(String missatgeError) {
        super(missatgeError);
    }
}

