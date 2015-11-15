package Sample;

import javax.faces.bean.ManagedBean;
import java.util.Vector;

@ManagedBean(name = "helloWorld", eager = true)
public class HelloWorld {
    private Vector<String> pulledStrings = new Vector<String>();

    public HelloWorld() {
        // Pull everything from db
        pulledStrings.add("Hello ");
        pulledStrings.add("World ");

        System.out.println("HelloWorld started!");
    }
    public String getMessage() {
        String sum = "";

        for(String s: pulledStrings)
            sum += s;

        return sum;
    }
}