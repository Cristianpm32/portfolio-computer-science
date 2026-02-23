/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog2.model;

import java.io.Serializable;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.io.IOException;

import prog2.vista.ExcepcioClub;

/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class ClubUB implements Serializable {
    /**
     * Instància del nom del club.
     */
    private String nom;
    /**
     * Constant del preu de les excursions.
     */
    private final int PREU_EXCURSIO = 20;
    /**
     * Constant del preu de la quota mensual.
     */
    private final int PREU_QUOTA_MENSUAL = 25;
    /**
     * Constant del descompte per les excursions dels federats.
     */
    private final float DESCOMPTE_EXCURSIO_FEDERATS = 0.2f;
    /**
     * Constant del descompte de la quota dels federats.
     */
    private final float DESCOMPTE_QUOTA_FEDERATS = 0.3f;
    /**
     * Instància que emmagatzema els socis que formen part dels club.
     */
    private LlistaSocis llista;

    /**
     * Constructor de Club.
     * 
     * @throws ExcepcioClub
     */
    public ClubUB() throws ExcepcioClub {
        nom = "Club UB";
        llista = new LlistaSocis();
    }

    /**
     * Retorna el nom del club.
     * 
     * @return String del nom del club.
     */
    public String getNom() {
        return nom;
    }

    /**
     * Assigna el nom al club
     * 
     * @param nom del club.
     */
    public void setNom(String nom) {
        this.nom = nom;
    }

    /**
     * Assigna la mida màxima de la llista de socis.
     * 
     * @param max_size de la llista de Socis.
     */
    public void setMaxSize(int max_size) {
        llista.setMaxSize(max_size);
    }

    /**
     * Crea una instància de soci federat.
     * 
     * @param nom del soci federat.
     * @param dni del soci federat.
     * @param federacio escollida pel soci federat creat.
     * @param preu de la federació (més gran de 100€).
     * @throws ExcepcioClub si el preu de la federació és inferior a 100€
     */
    public void crearSociFederat(String nom, String dni, String federacio, float preu) throws ExcepcioClub {
        SociFederat sociFederat = new SociFederat(nom, dni, federacio, preu,
                DESCOMPTE_EXCURSIO_FEDERATS, DESCOMPTE_QUOTA_FEDERATS);
        addSoci(sociFederat);
    }

    /**
     * Crea una instància de soci estàndard.
     * 
     * @param nom del soci estàndard.
     * @param dni del soci estàndard.
     * @param asseguranca el soci estàndard. La introdueix l'usuari per teclat.
     * @param preu de l'assegurança.
     * @throws ExcepcioClub es llença en el cas que l'assegurança no sigui ni "Basica" ni "Completa".
     */
    public void crearSociEstandard(String nom, String dni, String asseguranca, float preu) throws ExcepcioClub {
        SociEstandard sociEstandard = new SociEstandard(nom, dni, asseguranca, preu);
        addSoci(sociEstandard);
    }

    /**
     * Crea una instància de soci Junior.
     * 
     * @param nom del soci junior.
     * @param dni del soci junior.
     * @param asseguranca el soci junior. La introdueix l'usuari per teclat.
     * @param preu de l'assegurança.
     * @param any_naixement del soci junior.
     * @throws ExcepcioClub es llença en el cas que l'assegurança no sigui ni "Basica" ni "Completa".
     */
    public void crearSociJunior(String nom, String dni, String asseguranca, float preu, String any_naixement)
            throws ExcepcioClub {
        SociJunior sociJunior = new SociJunior(nom, dni, asseguranca, preu, any_naixement);
        addSoci(sociJunior);
    }

    /**
     * Afegeix un soci a la llista.
     * 
     * @param soci que s'ha inscrit a la llista.
     * @throws ExcepcioClub es llença en cas de que existeixi un soci amb el mateix DNI ja inscrit a la llista.
     */
    public void addSoci(Soci soci) throws ExcepcioClub {
        llista.addSoci(soci);

    }

    /**
     * Retorna un String amb la informació dels socis segons el tipus.
     * 
     * @param tipus de soci (Federat, estàndard o junior)
     * @return String amb els socis demanats
     */
    public String llistarSocis(String tipus) {
        return llista.llistarSocis(tipus);
    }

    /**
     * Elimina un soci de la llista en cas de ser-hi en aquesta llista, sino llença
     * una excepció.
     * 
     * @param position de la llista que correspon al soci que es vol eliminar.
     * @throws ExcepcioClub es llença en cas de no existir aquesta posició.
     */
    public void removeSoci(int position) throws ExcepcioClub {
        llista.removeSoci(llista.getAt(position));
    }

    /**
     * Comprova si la informació introduida per cadascún dels socis és correcta.
     * 
     * @throws ExcepcioClub 
     */
    public void verificarSocis() throws ExcepcioClub {
        llista.verificarSocis();
    }

    /**
     * Calcula la factura total d'un soci determinat del qual sabem el seu dni i el
     * nombre d'excursions
     * que ha realitzat.
     * 
     * @param dni del soci del que volem fer el càlcul.
     * @param excursions que ha fet en un mes.
     * @return float amb la factura total.
     * @throws ExcepcioClub si el soci no existeix.
     */
    public float mostrarFacturaTotal(String dni, int excursions) throws ExcepcioClub {
        float preuQuota = llista.getSoci(dni).calculaQuota(PREU_QUOTA_MENSUAL);
        float preuExcursions = llista.getSoci(dni).calculaPreuExcursio(PREU_EXCURSIO) * excursions;
        return preuQuota + preuExcursions;
    }

    /**
     * Modifica el nom d'un soci determinat donats un nom i un dni. En cas de no
     * ser-hi a la llista
     * llença una excepció.
     * 
     * @param dni del soci del que volem modificar el seu nom
     * @param nom nou del soci
     * @throws ExcepcioClub en cas que el soci no existeixi.
     */
    public void modificarNomSoci(String dni, String nom) throws ExcepcioClub {
        llista.getSoci(dni).setNom(nom);
    }

    /**
     * Modifica el tipus d'assegurança d'un soci determinat donat un DNI per
     * l'assegurança que
     * introdueix l'usuari per teclat.
     * 
     * @param dni del soci del que volem canviar l'assegurança
     * @param asseguranca Nou tipus d'assegurança que es vol assignar al soci.
     * @throws ExcepcioClub En cas de no existir-hi el soci.
     */
    public void modificarTipusAssegurancaSoci(String dni, String asseguranca) throws ExcepcioClub {
        Soci a = llista.getSoci(dni);
        if (a instanceof SociFederat) {
            throw new ExcepcioClub("El DNI introduït correspon a un Soci federat.");
        } else {
            SociEstandard b = (SociEstandard) a;
            b.set_TipusAsseguranca(asseguranca);
        }
    }

    /**
     * Permet guardar les dades introduides (respecte els socis) per teclat en un
     * fitxer.
     * 
     * @param filename nom del fitxer on es guardaran les dades.
     * @throws ExcepcioClub 
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public void guardarDades(String filename) throws ExcepcioClub, IOException, ClassNotFoundException {
        File fitxer = new File(filename);
        FileOutputStream fout = new FileOutputStream(fitxer);
        ObjectOutputStream oos = new ObjectOutputStream(fout);
        oos.writeObject(this);
        fout.close();
    }

    /**
     * Permet recuperar les dades dels socis guardades en un fitxer previament en
     * una altre sessió.
     * 
     * @param filename nom del fitxer on es troben guardades les dades.
     * @return ClubUB Llista de socis inscrits.
     * @throws ExcepcioClub
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public static ClubUB carregarDades(String filename) throws ExcepcioClub, IOException, ClassNotFoundException {
        File fitxer = new File(filename);
        FileInputStream fin = new FileInputStream(fitxer);
        ObjectInputStream ois = new ObjectInputStream(fin);
        ClubUB aux = (ClubUB) ois.readObject();
        fin.close();
        return aux;
    }

    /**
     * Buida tota la llista de socis.
     * 
     * @throws ExcepcioClub en cas que la llista sigui buida.
     */
    public void clear() throws ExcepcioClub {
        llista.clear();
    }
}
