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

public class SociEstandard extends Soci {
    /**
     * Declaració del nom del tipus de soci.
     */
    private String _tipus = "Estàndard";
    /**
     * Instància d'assegurança.
     */
    protected Asseguranca asseguranca = new Asseguranca();

    /**
     * Constructor de SociEstandard.
     * 
     * @param nom del soci.
     * @param dni del soci.
     * @param tipusAsseguranca basica o completa
     * @param preuAsseguranca preu de l'assegurança
     */
    public SociEstandard(String nom, String dni, String tipusAsseguranca, float preuAsseguranca) {
        super(nom, dni);
        set_TipusAsseguranca(tipusAsseguranca);
        set_PreuAsseguranca(preuAsseguranca);
    }

    /**
     * Retorna el tipus d'assegurança d'un soci.
     * 
     * @return String amb el tipus de l'assegurança
     */
    public String get_TipusAsseguranca() {
        return asseguranca.get_tipusAsseguranca();
    }

    /**
     * Assigna el tipus d'assegurança a un soci.
     * 
     * @param tipusAsseguranca basica o completa
     */
    public void set_TipusAsseguranca(String tipusAsseguranca) {
        asseguranca.set_tipusAsseguranca(tipusAsseguranca);
    }

    /**
     * Retorna el preu de l'assegurança.
     * 
     * @return float amb el preu de l'assegurança
     */
    public float get_PreuAsseguranca() {
        return asseguranca.get_preuAsseguranca();
    }

    /**
     * Assigna el preu de l'assegurança d'un soci.
     * 
     * @param preuAsseguranca preu de l'assegurança.
     */
    public void set_PreuAsseguranca(float preuAsseguranca) {
        asseguranca.set_preuAsseguranca(preuAsseguranca);
    }

    /**
     * Retorna un String amb tota la informació d'un soci.
     * 
     * @return String amb la informació del soci.
     */
    public String toString() {
        String informacio = "Nom: " + getNom() + ", DNI: " + getDNI() + ", " + asseguranca.toString();
        return informacio;
    }

    /**
     * Retorna el tipus de soci.
     * 
     * @return String amb el tipus de soci.
     */
    public String getTipus() {
        return _tipus;
    }

    /**
     * Calcular la quota mensual del soci
     * 
     * @param quotaBase quota mensual base del club.
     * @return float amb la quota mensual d'aquest soci.
     * @throws ExcepcioClub
     */
    public float calculaQuota(float quotaBase) throws ExcepcioClub {
        return quotaBase;
    }

    /**
     * Calcular el preu de les excursions del soci
     * 
     * @param preuExcursioBase preu de les excursions del club.
     * @return float amb el preu de les excursions d'aquest soci.
     * @throws ExcepcioClub
     */
    public float calculaPreuExcursio(float preuExcursioBase) throws ExcepcioClub {
        return preuExcursioBase + get_PreuAsseguranca();
    }

    /**
     * Comprova si les dades del soci són correctes o no
     * 
     * @throws ExcepcioClub Si hi ha algún error en les dades es llança una excepció
     */
    public void comprova() throws ExcepcioClub {
        if (!asseguranca.get_tipusAsseguranca().equals("Bàsica")
                && !asseguranca.get_tipusAsseguranca().equals("Completa")) {
            throw new ExcepcioClub("El tipus d'assegurança no és correcta.");
        }
    }

}