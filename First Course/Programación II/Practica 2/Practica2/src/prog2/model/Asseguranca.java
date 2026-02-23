package prog2.model;

import java.io.Serializable;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class Asseguranca implements Serializable {
    /**
     * Instància del tipus d'assegurança.
     */
    private String _tipusAsseguranca;

    /**
     * Instància del preu de l'assegurança.
     */
    private float _preuAsseguranca;

    /**
     * Constructor buit.
     */
    public Asseguranca() {
    }

    /**
     * Constructor d'asseguranca.
     * 
     * @param tipusAsseguranca Tipus d'assegurança (Basica o completa).
     * @param preuAsseguranca Preu de l'assegurança.
     */
    public Asseguranca(String tipusAsseguranca, float preuAsseguranca) {
        _tipusAsseguranca = tipusAsseguranca;
        _preuAsseguranca = preuAsseguranca;
    }

    /**
     * Retorna el tipus d'assegurança.
     * 
     * @return String del tipus d'assegurança (Basica o completa).
     */
    public String get_tipusAsseguranca() {
        return _tipusAsseguranca;
    }

    /**
     * Assigna el tipus d'assegurança.
     * 
     * @param _tipusAsseguranca Tipus d'assegurança (Basica o completa).
     */
    public void set_tipusAsseguranca(String _tipusAsseguranca) {
        this._tipusAsseguranca = _tipusAsseguranca;
    }

    /**
     * Retorna el preu de l'assegurança.
     * 
     * @return float del preu de l'assegurança.
     */
    public float get_preuAsseguranca() {
        return _preuAsseguranca;
    }

    /**
     * Assigna un preu a l'assegurança.
     * 
     * @param _preuAsseguranca Preu de l'assegurança.
     */
    public void set_preuAsseguranca(float _preuAsseguranca) {
        this._preuAsseguranca = _preuAsseguranca;
    }

    /**
     * Retona un String amb tota la informació de l'assegurança.
     * 
     * @return String amb la informació de l'assegurança.
     */
    public String toString() {
        String informacio = "Tipus d'assegurança: " + get_tipusAsseguranca() + ", Preu: " + get_preuAsseguranca();
        return informacio;
    }
}

