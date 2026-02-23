package prog2.model;

import java.io.Serializable;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class Federacio implements Serializable {
    /**
     * Instància del nom de la Federació.
     */
    private String _nomFederacio;
    /**
     * Instància del preu de la federació.
     */
    private float _preuFederacio;

    /**
     * Constructor de Federació.
     * 
     * @param nomFederacio Nom de la federació introduida per teclat.
     * @param preuFederacio Preu de la federació introduida per teclat (superior a 100€).
     */
    public Federacio(String nomFederacio, float preuFederacio) {
        _nomFederacio = nomFederacio;
        _preuFederacio = preuFederacio;
    }

    /**
     * Retorna el nom de la federació.
     * 
     * @return String amb el nom de la federació introduida per teclat.
     */
    public String get_nomFederacio() {
        return _nomFederacio;
    }

    /**
     * Assigna un nom a la federació.
     * 
     * @param _nomFederacio Nom de la federació introduida per teclat.
     */
    public void set_nomFederacio(String _nomFederacio) {
        this._nomFederacio = _nomFederacio;
    }

    /**
     * Retorna el preu de la federació.
     * 
     * @return float amb el preu de la federació introduida per teclat (superior a 100€).
     */
    public float get_preuFederacio() {
        return _preuFederacio;
    }

    /**
     * Assigna un preu a la federació.
     * 
     * @param _preuFederacio Preu de la federació introduida per teclat (superior a 100€).
     */
    public void set_preuFederacio(float _preuFederacio) {
        this._preuFederacio = _preuFederacio;
    }

    /**
     * Retorna una String amb la informació de la federació.
     * 
     * @return String amb la informació de la federació.
     */
    public String toString() {
        String informacio = "Nom de Federació: " + get_nomFederacio() + ", Preu: " + get_preuFederacio();
        return informacio;
    }
}

