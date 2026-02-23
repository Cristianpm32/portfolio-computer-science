/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prog2.vista;

import java.util.*;

import prog2.model.ClubUB;


/**
 *
 * @author Cristian Prado Méndez i Alba Cano Iglesias
 */

public class VistaClubUB {
    /**
     * Instància de ClubUB.
     */
    private ClubUB clubUB;

    /**
     * Constructor de VistaClubUB.
     * 
     * @throws ExcepcioClub
     */
    public VistaClubUB() throws ExcepcioClub {
        clubUB = new ClubUB();
    }

    /* Métodes */
    public void gestioClubUB() {

        // Creación de un objeto para leer el input desde el teclado
        Scanner sc = new Scanner(System.in);

        // Llamar a la funcion que gestiona el menu
        gestioMenu(sc);
    }

    /* ******************************************** */
    /* Gestion, Opciones y Descripcion del Menu (M) */
    /* ******************************************** */
    private static enum OpcionesMenu {
        M_Opcion_1_DonarAltaSoci,
        M_Opcion_2_ListaSocis,
        M_Opcion_3_ListaSocisFederats,
        M_Opcion_4_ListaSocisEstandard,
        M_Opcion_5_ListaSocisJunior,
        M_Opcion_6_Eliminar_Soci,
        M_Opcion_7_Verificar_Soci,
        M_Opcion_8_Mostrar_FacturaTotal,
        M_Opcion_9_Modificar_NomSoci,
        M_Opcion_10_Modificar_TipusAssegurancaSoci,
        M_Opcion_11_Guardar_Dades,
        M_Opcion_12_Recuperar_Dades,
        M_Opcion_13_Salir
    };

    // Descripcio de les opcions del menu principal
    private static final String[] descMenu = {
            "Donar d'alta un soci", // Opcio 1
            "Mostrar llista de socis", // Opcio 2
            "Mostrar llista de socis federats", // Opcio 3
            "Mostrar llista de socis estàndards", // Opcio 4
            "Mostrar llista de socis junior", // Opcio 5
            "Eliminar soci", // Opcio 6
            "Verificar socis", // Opcio 7
            "Mostrar total factura", // Opcio 8
            "Modificar nom soci", // Opcio 9
            "Modificar tipus assegurança soci", // Opcio 10
            "Guardar dades", // Opcion 11
            "Recuperar dades", // Opcion 12
            "Sortir" // Opcion 13
    };

    /* ******************************************** */
    /* Gestion, Opciones y Descripcion del Menu (1) */
    /* ******************************************** */
    private static enum OpcionesMenu1 {
        M_Opcion_1_AfegirSociFederat,
        M_Opcion_2_AfegirSociEstandard,
        M_Opcion_3_AfegirSociJunior,
        M_Opcion_4_MenuAnterior
    };

    // Descripcio de les opcions del menu opció 1.
    private static final String[] menuAltaSocis = {
            "Afegir Soci Federat",
            "Afegir Soci Estàndard",
            "Afegir Soci Junior",
            "Menú anterior"
    };

    // Funcio que gestiona el menu principal de la aplicacio
    // Hi ha 3 passos principals:
    // 1. Crear l'objete que representa (conté) el menu
    // 2. Asignar les descripcions del menu
    // 3. Bucle n el cual es tracta la opcio seleccionada per l'usuari
    public void gestioMenu(Scanner sc) {
        // Creación del objeto que representa el menu. El primer argumento del
        // contructor es el nombre del menu
        Menu<OpcionesMenu> menuClubUB = new Menu<>(clubUB.getNom(),
                OpcionesMenu.values());
        Menu<OpcionesMenu1> menuOpcion1 = new Menu<>("Indica una de les següents opcions", OpcionesMenu1.values());

        // Assignar una descripción a cada una de las opciones
        // - OPCIONAL - Por defecto enseña el nombre de la opción
        menuClubUB.setDescripcions(descMenu);
        menuOpcion1.setDescripcions(menuAltaSocis);

        // Variable (de tipo enumerado igual a las opciones del menu) que contiene la
        // opcion escogida
        OpcionesMenu opcionMenu;

        System.out.println("Quants socis es poden inscriure?");
        int mida = sc.nextInt();
        clubUB.setMaxSize(mida);

        // Lançar el bucle principal de la aplicación
        do {
            menuClubUB.mostrarMenu();
            opcionMenu = menuClubUB.getOpcio(sc);
            switch (opcionMenu) {
                case M_Opcion_1_DonarAltaSoci:
                    OpcionesMenu1 opcionMenu1;
                    do {
                        menuOpcion1.mostrarMenu();
                        opcionMenu1 = menuOpcion1.getOpcio(sc);
                        switch (opcionMenu1) {
                            case M_Opcion_1_AfegirSociFederat:
                                try {
                                    afegirSociFederat(clubUB, sc);

                                } catch (Exception e) {
                                    System.out.println(e);
                                }
                                break;
                            case M_Opcion_2_AfegirSociEstandard:
                                try {
                                    afegirSociEstadard(clubUB, sc);

                                } catch (Exception e) {
                                    System.out.println(e);
                                }
                                break;
                            case M_Opcion_3_AfegirSociJunior:
                                try {
                                    afegirSociJunior(clubUB, sc);
                                    break;
                                } catch (Exception e) {
                                    System.out.println(e);
                                }
                            case M_Opcion_4_MenuAnterior:
                                break;
                        }
                    } while (opcionMenu1 != OpcionesMenu1.M_Opcion_4_MenuAnterior);
                    break;
                case M_Opcion_2_ListaSocis:
                    try {
                        System.out.println(clubUB.llistarSocis("Tots"));

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_3_ListaSocisFederats:
                    try {
                        System.out.println(clubUB.llistarSocis("Federat"));

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_4_ListaSocisEstandard:
                    try {
                        System.out.println(clubUB.llistarSocis("Estàndard"));

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_5_ListaSocisJunior:
                    try {
                        System.out.println(clubUB.llistarSocis("Junior"));

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_6_Eliminar_Soci:
                    try {
                        System.out.println("Quina és la posició del soci que vols eliminar?");
                        int position = sc.nextInt();
                        clubUB.removeSoci(position);

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_7_Verificar_Soci:
                    try {
                        clubUB.verificarSocis();
                        System.out.println("Totes les dades són correctes.");

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_8_Mostrar_FacturaTotal:
                    try {
                        mostrarFactura(clubUB, sc);

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_9_Modificar_NomSoci:
                    try {
                        modificarNomSoci(clubUB, sc);

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_10_Modificar_TipusAssegurancaSoci:
                    try {
                        modificarTipusAsseguranca(clubUB, sc);

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_11_Guardar_Dades:
                    try {
                        clubUB.guardarDades("clubUb.dat");

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_12_Recuperar_Dades:
                    try {
                        clubUB = ClubUB.carregarDades("clubUb.dat");

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case M_Opcion_13_Salir:
                    try {
                        clubUB.clear();
                        System.out.println("Fins aviat");

                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
            }

        } while (opcionMenu != OpcionesMenu.M_Opcion_13_Salir);
    }

    /**
     * Demana el nom, el DNI, el nom de la Federació i el preu de la federació per
     * després afegir un soci Federat a
     * la llista de Socis de clubUB amb aquestes dades.
     * 
     * @param clubUb instància de clubUB amb tota la infromació dels socis.
     * @param sc scanner perquè l'usuari introdueixi dades per teclat.
     * @throws ExcepcioClub
     */
    public void afegirSociFederat(ClubUB clubUb, Scanner sc) throws ExcepcioClub {
        System.out.println("Indica el nom del nou soci: ");
        String nom = sc.nextLine();
        System.out.println("Indica el DNI del nou soci: ");
        String dni = sc.nextLine();
        System.out.println("Indica el nom de la Federació: ");
        String nomFederacio = sc.nextLine();
        System.out.println("Indica el preu de la Federació seleccionada: ");
        float preuFederacio = sc.nextFloat();
        clubUB.crearSociFederat(nom, dni, nomFederacio, preuFederacio);
    }

    /**
     * Demana el nom, el DNI, el tipus d'assegurança i el preu de l'assegurança per
     * després afegir un soci Estàndard a
     * la llista de Socis de clubUB amb aquestes dades.
     * 
     * @param clubUb instància de clubUB amb tota la infromació dels socis.
     * @param sc scanner perquè l'usuari introdueixi dades per teclat.
     * @throws ExcepcioClub
     */
    public void afegirSociEstadard(ClubUB clubUB, Scanner sc) throws ExcepcioClub {

        System.out.println("Indica el nom del nou soci: ");
        String nom = sc.nextLine();
        System.out.println("Indica el DNI del nou soci: ");
        String dni = sc.nextLine();
        System.out.println("Indica el tipus de l'assegurança: ");
        String tipusAsseguranca = sc.nextLine();
        System.out.println("Indica el preu de l'assegurança seleccionada: ");
        float preuAsseguranca = sc.nextFloat();
        clubUB.crearSociEstandard(nom, dni, tipusAsseguranca, preuAsseguranca);
    }

    /**
     * Demana el nom, el DNI, la data de naixement, el tipus d'assegurança i el preu
     * de l'assegurança per després afegir
     * un soci Estàndard a la llista de Socis de clubUB amb aquestes dades.
     * 
     * @param clubUb instància de clubUB amb tota la infromació dels socis.
     * @param sc scanner perquè l'usuari introdueixi dades per teclat.
     * @throws ExcepcioClub
     */
    public void afegirSociJunior(ClubUB clubUB, Scanner sc) throws ExcepcioClub {

        System.out.println("Indica el nom del nou soci: ");
        String nom = sc.nextLine();
        System.out.println("Indica el DNI del nou soci: ");
        String dni = sc.nextLine();
        System.out.println("Indica la data de naixement: ");
        String any_naixement = sc.nextLine();
        System.out.println("Indica el tipus de l'assegurança: ");
        String tipusAsseguranca = sc.nextLine();
        System.out.println("Indica el preu de l'assegurança seleccionada: ");
        float preuAsseguranca = sc.nextFloat();
        clubUB.crearSociJunior(nom, dni, tipusAsseguranca, preuAsseguranca, any_naixement);
    }

    /**
     * Demana el DNI d'un soci i el nombre d'excursions per després calcular la
     * factura total .
     * 
     * @param clubUb instància de clubUB amb tota la infromació dels socis.
     * @param sc scanner perquè l'usuari introdueixi dades per teclat.
     * @throws ExcepcioClub
     */
    public void mostrarFactura(ClubUB clubUB, Scanner sc) throws ExcepcioClub {

        System.out.println("Indica el DNI del Soci: ");
        String dni = sc.nextLine();
        System.out.println("Indica el nombre d'excursions realitzades pel Soci aquest mes.");
        int excursions = sc.nextInt();
        System.out.println("Factura total: " + clubUB.mostrarFacturaTotal(dni, excursions));
    }

    /**
     * Demana el DNI i el nou nom del soci i canvia el nom del soci amb aquell DNI.
     * 
     * @param clubUb instància de clubUB amb tota la infromació dels socis.
     * @param sc scanner perquè l'usuari introdueixi dades per teclat.
     * @throws ExcepcioClub
     */
    public void modificarNomSoci(ClubUB clubUB, Scanner sc) throws ExcepcioClub {

        System.out.println("Introdueix el DNI del Soci que vols modificar: ");
        String dni = sc.nextLine();
        System.out.println("Digues el nou nom del Soci");
        String nom = sc.nextLine();
        clubUB.modificarNomSoci(dni, nom);
        System.out.println("S'ha modificat correctament!");
    }

    /**
     * Demana el DNI d'un soci, busca el soci amb aquest DNI dins la llista de
     * clubUB i li canvia el tipus
     * d'assegurança.
     * 
     * @param clubUb instància de clubUB amb tota la infromació dels socis.
     * @param sc scanner perquè l'usuari introdueixi dades per teclat.
     * @throws ExcepcioClub
     */
    public void modificarTipusAsseguranca(ClubUB clubUB, Scanner sc) throws ExcepcioClub {

        System.out.println("Introdueix el DNI del Soci que vols modificar: ");
        String dni = sc.nextLine();
        System.out.println("Digues el nou tipus d'asseguranca del Soci.");
        String asseguranca = sc.nextLine();
        clubUB.modificarTipusAssegurancaSoci(dni, asseguranca);
        System.out.println("S'ha modificat correctament!");
    }
}
