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
public class FlotaCorrecteBatallaNavalTest {
    
    public FlotaCorrecteBatallaNavalTest() {
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
     * Test of main method, of class FlotaCorrecteBatallaNaval.
     */
    /*
    @Test
    public void testMain() {
        System.out.println("main");
        String[] args = null;
        FlotaCorrecteBatallaNaval.main(args);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of taulerCorrecte method, of class FlotaCorrecteBatallaNaval.
     */
    @Test
    public void testTaulerCorrecte1() {
        System.out.println("taulerCorrecte");
        int[][] tauler = {{0,1,1,0},{0,0,0,1},{0,0,0,1},{1,0,0,0}};
        boolean expResult = false;
        boolean result = FlotaCorrecteBatallaNaval.taulerCorrecte(tauler);
        assertEquals(expResult, result);
    }
    @Test
    public void testTaulerCorrecte2() {
        System.out.println("taulerCorrecte");
        int[][] tauler = {{0,1,1,0},{0,0,0,0},{0,0,0,1},{1,0,0,0}};
        boolean expResult = true;
        boolean result = FlotaCorrecteBatallaNaval.taulerCorrecte(tauler);
        assertEquals(expResult, result);
    }
    @Test
    public void testTaulerCorrecte() {
        System.out.println("taulerCorrecte");
        int[][] tauler = {{0,1,1,0},{0,0,1,0},{0,0,1,0},{1,0,1,0}};
        boolean expResult = false;
        boolean result = FlotaCorrecteBatallaNaval.taulerCorrecte(tauler);
        assertEquals(expResult, result);
    }
}
