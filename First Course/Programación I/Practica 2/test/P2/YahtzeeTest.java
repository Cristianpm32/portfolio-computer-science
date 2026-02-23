/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package P2;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author cristianpradomendez
 */
public class YahtzeeTest {
    
    public YahtzeeTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of main method, of class Yahtzee.
     */
    /*
    @Test
    public void testMain() {
        System.out.println("main");
        String[] args = null;
        Yahtzee.main(args);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of tiraDados method, of class Yahtzee.
     */
    /*
    @Test
    public void testTiraDados() {
        System.out.println("tiraDados");
        int[] daus = null;
        Yahtzee.tiraDados(daus);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of esYahtzee method, of class Yahtzee.
     */
    @Test
    public void testEsYahtzee1() {
        System.out.println("esYahtzee");
        int[] daus = {5, 5, 5, 5, 5,};
        boolean expResult = true;
        boolean result = Yahtzee.esYahtzee(daus);
        
        assertEquals(expResult, result);
    }
    public void testEsYahtzee2() {
        System.out.println("esYahtzee");
        int[] daus = {5, 3, 3, 4, 5};
        boolean expResult = false;
        boolean result = Yahtzee.esYahtzee(daus);
        
        assertEquals(expResult, result);
    }
}
