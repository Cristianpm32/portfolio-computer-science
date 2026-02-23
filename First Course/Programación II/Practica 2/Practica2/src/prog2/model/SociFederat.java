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

public class SociFederat extends Soci {
    /**
     * Instància de Federació.
     */
    private Federacio federacio;
    /**
     * Instància del descompte d'excursions pels federats.
     */
    private float descompte_excursions_federats;
    /**
     * Instància del descompte de la quota pels federats.
     */
    private float descompte_quota_federats;
    /**
     * Declaració del nom del tipus de soci.
     */
    private String _tipus = "Federat";

    /**
     * Constructor de SociFederat.
     * 
     * @param nom del soci
     * @param dni del soci
     * @param nomFederacio nom de la federacio del soci
     * @param preuFederacio preu de la federació (superior a 100€).
     * @param descompteExcursions descompte per les excursions
     * @param descompteQuota descompte en la quota mensual
     */
    public SociFederat(String nom, String dni, String nomFederacio, float preuFederacio, float descompteExcursions,
            float descompteQuota) {
        super(nom, dni);
        federacio = new Federacio(nomFederacio, preuFederacio);
        this.descompte_excursions_federats = descompteExcursions;
        this.descompte_quota_federats = descompteQuota;
    }

    /**
     * Retorna un String amb tots els detalls d'un soci federat.
     * 
     * @return String amb tota la informació del soci.
     */
    public String toString() {
        String informacio = "Nom: " + getNom() + ", DNI: " + getDNI() + ", " + federacio.toString();
        return informacio;
    }

    /**
     * Calcular la quota mensual del soci
     * 
     * @param quotaBase quota mensual base del club.
     * @return float amb la quota mensual d'aquest soci.
     * @throws ExcepcioClub
     */
    public float calculaQuota(float quotaBase) throws ExcepcioClub {
        return quotaBase * (1 - descompte_quota_federats);
    }

    /**
     * Retorna el tipus de soci.
     * 
     * @return String amb el tipus del soci
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
        return preuExcursioBase * (1 - descompte_excursions_federats);
    }

    /**
     * Comprova si les dades del soci són correctes o no
     * 
     * @throws ExcepcioClub Si hi ha algún error en les dades es llança una excepció
     */
    public void comprova() throws ExcepcioClub {
        if (federacio.get_preuFederacio() < 100) {
            throw new ExcepcioClub("El preu de la federació no és correcte.");
        }
    }
}
