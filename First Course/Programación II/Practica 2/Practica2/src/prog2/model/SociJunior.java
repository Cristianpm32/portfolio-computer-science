/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog2.model;

import prog2.vista.ExcepcioClub;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class SociJunior extends SociEstandard {
    /**
     * Instància de la data de naixement del soci.
     */
    private String any_naixement;
    /**
     * Declaració del tipus de soci.
     */
    private String _tipus = "Junior";

    /**
     * Constructor de SociJunior.
     * 
     * @param nom del soci junior
     * @param dni del soci junior
     * @param tipusAsseguranca del soci junior (basica o completa)
     * @param preuAsseguranca preu de l'assegurança del soci junior
     * @param any_naixement data de naixement del soci junior
     */
    public SociJunior(String nom, String dni, String tipusAsseguranca, float preuAsseguranca, String any_naixement) {
        super(nom, dni, tipusAsseguranca, preuAsseguranca);
        this.any_naixement = any_naixement;
    }

    /**
     * Retorna la data de naixement del soci.
     * 
     * @return String amb la data de naixement
     */
    public String getAnyNaixement() {
        return any_naixement;
    }

    /**
     * Assigna la data de naixement a un soci.
     * 
     * @param any_naixement data de naixement del soci junior
     */
    public void setAnyNaixement(String any_naixement) {
        this.any_naixement = any_naixement;
    }

    /**
     * Retorna un String amb tota la informació d'un soci junior.
     * 
     * @return String amb tota la informacio del soci.
     */
    public String toString() {
        String informacio = "Nom: " + getNom() + ", DNI: " + getDNI() + ", Any de naixement: " + getAnyNaixement()
                + ", " + asseguranca.toString();
        return informacio;
    }

    /**
     * Retorna el tipus de soci.
     * 
     * @return Stringamb el tipus de soci
     */
    public String getTipus() {
        return _tipus;
    }

    /**
     * Calcular el preu de les excursions del soci
     * 
     * @param preuExcursioBase preu de les excursions del club.
     * @return float amb el preu de les excursions d'aquest soci.
     * @throws ExcepcioClub
     */
    public float calculaPreuExcursio(float preuExcursioBase) throws ExcepcioClub {
        return 0;
    }

}
