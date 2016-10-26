package SandBox;
/**
 * Simple class for an entry point
 * @author Shkaruba_Nikita
 * @version 0.1
 */
public class ConsoleWrite {
    /**
     * Entry point for a program
     * @param args args to show.
     */
    public static void main(String[] args) {
        StringBuilder string = new StringBuilder();
        for (int i = 0; i != args.length; i++) {
            System.out.println(i + ". " + args[i]);
            string.append(args[i] + " ");
        }

        assert(true != false);
        System.out.println("All args together: " + string);
        System.out.println("Pi is: " + Math.PI);
    }
}