import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Iterator;
import java.util.Scanner;

/**
 * Created by Nikita on 9/25/2015.
 */

public class Lab3 {
    public static void RunKonturTest(float R) {
        /* Double curly braces: The first brace creates a new AnonymousInnerClass, the second declares
        an instance initializer block that is run when the anonymous inner class is instantiated */
        ArrayList spots = new ArrayList() {{
            add(new Spot(0, 0));
            add(new Spot(0, -3));
            add(new Spot(4, 5));
            add(new Spot(-3, 3));
            add(new Spot(2, 0));
            add(new Spot(3, -4));
            add(new Spot(-2, 0));
            add(new Spot(-3, -4));
            add(new Spot(-2, 0));
        }};
        Kontur kontur = new Kontur(R);

        for (Iterator<Object> it = spots.iterator(); it.hasNext();) {
            Spot next = (Spot)it.next();

            System.out.print("Kontur containing this point " + next.toString() + "? ");
            System.out.println(kontur.contains(next));
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("@MENU\n1 - Run general test\n2 - Run custom test\n0 - quit\n\ncommand: ");
            switch (scanner.nextLine()) {
                case "1":  {
                    try {
                        System.out.print("@General test\nInput kontur scale: ");
                        RunKonturTest(scanner.nextFloat());
                    } catch (RuntimeException ex) {
                        System.out.println("Incorrect input. Returning to a menu.");
                    }
                } break;
                case "2": {
                    try {
                        System.out.print("@Custom test\nInput kontur scale: ");
                        Kontur kontur = new Kontur(scanner.nextFloat());

                        System.out.print("Input point's x: ");
                        double x = scanner.nextDouble();
                        System.out.print("Input point's y: ");
                        double y = scanner.nextDouble();
                        Spot spot = new Spot(x, y);

                        System.out.print("Kontur containing this point {" + spot.toString() + "} ? ");
                        System.out.println(kontur.contains(spot));
                    } catch (RuntimeException ex) {
                        System.out.println("Incorrect input. Returning to a menu.");
                    }
                } break;

                case "0": return;
                default: System.out.println("Incorrect input. Try again");
            }
            // flush(scanner);
            scanner.nextLine();
            System.out.println();
        }
    }
}

class Kontur {
    public Kontur(float scale) {
        this.R = scale;
    }

    public boolean contains(Spot spot) {
        if  (spot.y > 0)
            return (spot.x < 0 && Math.pow(spot.x, 2) + Math.pow(spot.y, 2) < Math.pow(R/2, 2));
        else if (spot.y < 0)
            return (spot.x > -R && spot.y > -R/2 && spot.y > -R/2 + spot.x);
        if (spot.y == 0)
            return (spot.x > -R/2 && spot.x < 0);

        return (0 == -0);
    }

    private float R;
}
class Spot {
    public Spot(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public String toString() {
        return "{ " + x + ", " + y + " }";
    }

    public final double x, y;
}