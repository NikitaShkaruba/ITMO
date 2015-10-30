package Tests;

import Lab2.*;
import java.util.ResourceBundle;
import java.io.*;
import org.junit.*;

public class Lab2Test extends junit.framework.TestCase {
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	private static ResourceBundle resources = ResourceBundle.getBundle("Lab2");

	@Before
	public void setUpStreams() {
    	System.setOut(new PrintStream(outContent));
	}

	@Test
    public void testShellos() {
    	Shellos patient = new Shellos();

    	patient.painSplit(patient);
    	assertEquals(resources.getString("ShellosPainSplitShellosMessage"), outContent.toString());
    }
    
    @Test
    public void testGastrodon() {
    	Shellos patient = new Shellos();

    	assertEquals(1, 1);
    }
    
    public void testWillAlwaysFail() {
        fail("An error message");
    }
    
    @After
	public void cleanUpStreams() {
    	System.setOut(null);
	}
}