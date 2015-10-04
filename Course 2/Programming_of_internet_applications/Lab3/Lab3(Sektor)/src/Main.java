import java.util.ArrayList;
import java.util.Iterator;
/**
 * Created by Nikita on 9/25/2015.
 */

public class Main {
    public static void RunKonturTest() {
        /*The first brace creates a new AnonymousInnerClass, the second declares
        an instance initializer block that is run when the anonymous inner class is instantiated
         */
        ArrayList spots = new ArrayList() {{
            add(new Spot(0, 0));
            add(new Spot(0, -3));
            add(new Spot(4, 5));
            add(new Spot(-3, 3));
            add(new Spot(2, 0));
            add(new Spot(3, -4));
            add(new Spot(-2, 0));
            add(new Spot(-3, -4));
        }};
        Kontur kontur = new Kontur(500);

        for (Iterator<Object> it = spots.iterator(); it.hasNext();) {
            Spot next = (Spot)it.next();

            System.out.print("Is Kontur covering this point {" + next.x + ", " + next.y + "} ? ");
            System.out.println(kontur.compute(next));
        }
    }
    public static void main(String[] args) {
        //RunKonturTest();
        ArrayList spots = new ArrayList() {{
            add(new Spot(0, 0));
            add(new Spot(0, -3));
            add(new Spot(4, 5));
            add(new Spot(-3, 3));
            add(new Spot(2, 0));
            add(new Spot(3, -4));
            add(new Spot(-2, 0));
            add(new Spot(-3, -4));
        }};

        String cmd = "";
        while (true) {
            System.out.println("1 - Run tests/n2 - Input new R/n3 - add\\remove points/n4 - quit");
            // System.in.read;
            switch (cmd) {
                case "1": break;
                case "2": break;
                case "3": break;
                case "4": return;

                default: System.out.println("Incorrect input");
            }
        }
    }
}

class Kontur {
    private ArrayList<Spot> bounds;
    private double R;
    public Kontur(double R) {
        this.R = R;
    }
    // refactor method's name
    public boolean compute(Spot spot) {
        if  (spot.y > 0)
            return (spot.x < 0 && Math.pow(spot.x, 2) + Math.pow(spot.y, 2) < Math.pow(R/2, 2));
        if (spot.y < 0)
            return (spot.x > -R && spot.y > -R/2 && spot.y > -R/2 + spot.x);
        if (spot.y == 0)
            return (spot.x > -R/2 && spot.x < 0);

        return (0 == -0);
    }
}
class Spot {
    public double x, y;

    public Spot(double x,double y) {
        this.x = x;
        this.y = y;
    }

    /*public double getX() {
        return x;
    }
    public double getY() {
        return y;
    }
    public void setX(float x) {
        this.x = x;
    }
    public void setY(float y) {
        this.y = y;
    }*/
}