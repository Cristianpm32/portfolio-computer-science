
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog2.model;

import prog2.vista.ExcepcioClub;
import java.io.Serializable;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public abstract class Soci implements InSoci, Serializable {
    /**
     * Instància del nom del soci.
     */
    protected String nom;
    /**
     * Instància del DNI del soci.
     */
    protected String dni;

    /**
     * Constructor de Soci.
     * 
     * @param nom del nou soci
     * @param dni del nou soci
     */
    public Soci(String nom, String dni) {
        this.nom = nom;
        this.dni = dni;
    }

    /**
     * Comprova si dos socis tenen el mateix DNI. Retorna un boolean, true si són iguals, 
     * fals si són diferents.
     * 
     * @param externo objecte de tipus object que després convertim en soci
     * @return boolean.
     */
    public boolean equals(Object externo) {
        String myDni = this.getDNI();
        String externoDni = ((Soci) externo).getDNI();
        return myDni.equals(externoDni);
    }

    /**
     * Retorna el nom del Soci.
     * 
     * @return String amb el nom del soci
     */
    public String getNom() {
        return nom;
    }

    /**
     * Assigna un nom a un soci.
     * 
     * @param nom del soci
     */
    public void setNom(String nom) {
        this.nom = nom;
    }

    /**
     * Retorna el DNI del soci.
     * 
     * @return String amb el DNI del soci
     */
    public String getDNI() {
        return dni;
    }

    /**
     * Assigna un dni a un soci.
     * 
     * @param dni del soci
     */
    public void setDNI(String dni) {
        this.dni = dni;
    }

    /**
     * Mètode abstracte que es defineix a les classes filles.
     */
    public abstract String toString();

    /**
     * Mètode abstracte que es defineix a les classes filles.
     * 
     * @return String amb el tipus de soci.
     */
    public abstract String getTipus();

    /**
     * Calcular la quota mensual del soci
     * 
     * @param quotaBase quota mensual base del club.
     * @return float amb la quota mensual d'aquest soci.
     * @throws ExcepcioClub
     */
    public abstract float calculaQuota(float quotaBase) throws ExcepcioClub;

    /**
     * Calcular el preu de les excursions del soci
     * 
     * @param preuExcursioBase preu de les excursions del club.
     * @return float amb el preu de les excursions d'aquest soci.
     * @throws ExcepcioClub
     */
    public abstract float calculaPreuExcursio(float preuExcursioBase) throws ExcepcioClub;

    /**
     * Comprova si les dades del soci són correctes o no
     * 
     * @throws ExcepcioClub Si hi ha algún error en les dades es llança una excepció
     */
    public abstract void comprova() throws ExcepcioClub;

}