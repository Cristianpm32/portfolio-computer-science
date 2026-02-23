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
public class ADNTest {
    
    public ADNTest() {
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
     * Test of main method, of class ADN.
     */
    /*@Test
    public void testMain() {
        System.out.println("main");
        String[] args = null;
        ADN.main(args);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of sonIguals method, of class ADN.
     */
    @Test
    public void testSonIguals1() {
        System.out.println("sonIguals");
        char[] cadena1 = {'H', 'O', 'L', 'A'};
        char[] cadena2 = {'H', 'O', 'L', 'A'};
        boolean expResult = true;
        boolean result = ADN.sonIguals(cadena1, cadena2);
        
        assertEquals(expResult, result);
    }
    @Test
    public void testSonIguals2() {
        System.out.println("sonIguals");
        char[] cadena1 = {'H', 'O', 'L', 'A'};
        char[] cadena2 = {'O', 'L', 'A', 'H'};
        boolean expResult = true;
        boolean result = ADN.sonIguals(cadena1, cadena2);
        
        assertEquals(expResult, result);
    }
    @Test
    public void testSonIguals() {
        System.out.println("sonIguals");
        char[] cadena1 = {'H', 'O', 'L', 'A'};
        char[] cadena2 = {'H', 'O', 'L', 'L'};
        boolean expResult = false;
        boolean result = ADN.sonIguals(cadena1, cadena2);

        assertEquals(expResult, result);
    }
}
