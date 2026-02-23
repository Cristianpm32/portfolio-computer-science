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

public class IniciadorClubUB {

    /**
     * @param args the command line arguments
     * 
     * @throws ExcepcioClub
     */
    public static void main(String[] args) throws ExcepcioClub {
        /**
         * Creació de la instància de l'objecte VistaClub.
         */
        VistaClubUB vistaClub = new VistaClubUB();
        /**
         * Crida al mètode gestioClubUB de l'objecte vistaClub.
         */
        vistaClub.gestioClubUB();

    }

}
