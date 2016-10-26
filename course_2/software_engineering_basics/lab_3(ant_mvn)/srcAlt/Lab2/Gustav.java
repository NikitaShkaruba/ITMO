package Lab2;

import java.util.ResourceBundle;

public class Gustav extends Sheldon {
  private static ResourceBundle resources = ResourceBundle.getBundle("Lab2");
  private String Fire = "Fire";
  double attack = 2.1;
  private static int tracker = 87;
  private String earth = "Earth";
  private String fireEarth = "fireEarth";

  public void painSplit(Gustav p) {
    System.out.println(resources.getString("GustavPainSplitGustavMessage"));
  }

  public void focusEnergy() {
    System.out.println(juicer - tracker);
    System.out.println(tracker - sky);
    System.out.println(tracker + troublesome);
  }

  public void camouflage() {
    double defense = 7.9;

    System.out.println((defense - attack) == 5.8);
  }

  public static void foresight() {
    System.out.println(resources.getString("GustavForesightMessage"));
  }

  public void painSplit(Sheldon p) {
    System.out.println(resources.getString("GustavPainSplitSheldonMessage"));
  }

  public void swordsDance() {
    System.out.println(iceElectric == ice+earth);
    System.out.println(iceElectric == new String("fireEarth"));
    System.out.println(iceElectric == (ice+earth).intern());
    System.out.println(iceElectric == new String("Earth"+"Fire"));
  }

  public void batonPass() {
    System.out.println(resources.getString("GastrodonBatonPassMessage"));
  }
}