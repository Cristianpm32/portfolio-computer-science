package prog2.model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;

import prog2.vista.ExcepcioClub;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class LlistaSocis implements InSociList, Serializable {
    /**
     * Creació d'una llista d'elements de tipus Soci.
     */
    private ArrayList<Soci> _socis;
    /**
     * Instància del nombre màxim de socis dins una llista.
     */
    private int _max_size;

    /**
     * Constructor que estableix el màxim de socis de la LListaSocis en 100.
     */
    public LlistaSocis() {
        _socis = new ArrayList<Soci>();
        _max_size = 100;
    }

    /**
     * Constructor de LListaSocis en cas d'haver-hi un màxim de socis introduït per
     * l'usuari.
     * 
     * @param max_size Nombre màxim d'usuaris que poden inscriure's.
     */
    public LlistaSocis(int max_size) {
        _socis = new ArrayList<Soci>();
        _max_size = max_size;
    }

    /**
     * Donar el número d'elements que hi ha actualment emmagatzemants a la llista.
     * 
     * @return int amb el número d'elements de la llista.
     */
    public int getSize() {
        return _socis.size();
    }

    /**
     * Assigna la mida màxima a la llista.
     * 
     * @param max_size Nombre màxim d'usuaris que poden inscriure's.
     */
    public void setMaxSize(int max_size) {
        _max_size = max_size;
    }

    /**
     * Afegir un nou soci
     * 
     * @param soci objecte per afegir a la llista.
     * @throws prog2.vista.ExcepcioClub si la llista està plena o el soci ja hi és a
     *                                  la llista.
     */
    public void addSoci(Soci soci) throws ExcepcioClub {
        if (isFull()) {
            throw new ExcepcioClub("La llista està plena.");
        } else if (_socis.contains(soci)) {
            throw new ExcepcioClub("El soci ja està apuntat.");
        } else {
            _socis.add(soci);
        }

    }

    /**
     * Eliminar un objecte de la llista
     * 
     * @param soci objecte per eliminar.
     * @throws prog2.vista.ExcepcioClub si el soci no està a la llista.
     */
    public void removeSoci(Soci soci) throws ExcepcioClub {
        if (!_socis.remove(soci)) {
            throw new ExcepcioClub("El soci no està a la llista.");
        }
    }

    /**
     * Obtenir el soci guardat a una certa posició donada
     * 
     * @param position posició a la llista de socis.
     * @return objecte soci a la posició donada o null si no existeix.
     * @throws prog2.vista.ExcepcioClub
     */
    public Soci getAt(int position) throws ExcepcioClub {
        if (_socis.size() <= position) {
            return null;
        } else {
            return _socis.get(position);
        }
    }

    /**
     * Obtenir el soci donat el seu DNI
     * 
     * @param dni DNI del soci al que volem accedir.
     * @return Objecte soci amb el dni donat o null si no existeix.
     * @throws prog2.vista.ExcepcioClub
     */
    public Soci getSoci(String dni) throws ExcepcioClub {
        Iterator<Soci> it = _socis.iterator();
        Soci s = null;
        while (it.hasNext()) {
            Soci aux = it.next();
            if (aux.getDNI().equals(dni)) {
                s = aux;
            }
        }
        return s;
    }

    /**
     * Eliminar tots els elements de la llista
     * 
     * @throws prog2.vista.ExcepcioClub
     */
    public void clear() throws ExcepcioClub {
        _socis.clear();
    }

    /**
     * Comprovar si la llista està a la seva capacitat màxima o no.
     * 
     * @return True si la llista està plena (no hi ha lloc per més elements) o false
     *         sinó.
     * @throws prog2.vista.ExcepcioClub
     */
    public boolean isFull() throws ExcepcioClub {
        return _socis.size() == _max_size;
    }

    /**
     * Comprovar si la llista està buida o no.
     * 
     * @return True si la llista està buida (no hi ha cap elements) o false sinó.
     * @throws prog2.vista.ExcepcioClub
     */
    public boolean isEmpty() throws ExcepcioClub {
        return _socis.isEmpty();
    }

    /**
     * Comprovar si les dades dels socis de la llista són correctes.
     * 
     * @throws prog2.vista.ExcepcioClub Si hi ha algún error en les dades es llança
     *                                  una excepció
     */
    public void verificarSocis() throws ExcepcioClub {
        Iterator<Soci> it = _socis.iterator();
        while (it.hasNext()) {
            it.next().comprova();
        }
    }

    /**
     * Retorna un string amb tota la informació  dels socis segons el tipus.
     * @param tipus de soci (federat, estandard, junior.)
     * @return String amb tota la informacio dels socis.
     */
    public String llistarSocis(String tipus) {
        String informacio = new String();
        if (tipus.equals("Tots")) {
            Iterator<Soci> it = _socis.iterator();
            while (it.hasNext()) {
                informacio += it.next().toString() + "\n";
            }
        } else {
            Iterator<Soci> it = _socis.iterator();
            while (it.hasNext()) {
                Soci s = it.next();
                if (s.getTipus().equals(tipus)) {
                    informacio += s.toString() + "\n";
                }
            }
        }
        return informacio;
    }
}
