/*
 * Universitat de Barcelona
 * Programació 2
 * Curs 2021-2022
 */

package prog2.model;

import prog2.vista.ExcepcioClub;

/**
 * Interfície InSoci
 * @author laura
 */
public interface InSoci {
    
    public void setNom(String nom);
    public String getNom();
    public void setDNI(String dni);
    public String getDNI();
    
    /**
     * Calcular la quota mensual del soci
     * @param quotaBase quota mensual base del club.
     * @return float amb la quota mensual d'aquest soci.
     * @throws ExcepcioClub 
     */
    public float calculaQuota(float quotaBase) throws ExcepcioClub;
    
    /**
     * Calcualr el preu de les excursions del soci
     * @param preuExcursioBase preu de les excursions del club.
     * @return float amb el preu de les excursions d'aquest soci.
     * @throws ExcepcioClub 
     */
    public float calculaPreuExcursio(float preuExcursioBase) throws ExcepcioClub;
    
         
    /**
     * Comprova si les dades del soci són correctes o no
     * @throws ExcepcioClub Si hi ha algún error en les dades es llança una excepció 
     */ 
    public void comprova() throws ExcepcioClub;

}
