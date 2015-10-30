package Lab2;

import java.util.ResourceBundle;

public class Gastrodon extends Shellos {
  private static ResourceBundle resources = ResourceBundle.getBundle("Lab2");
  private String ice = "Ice";
  double attack = 2.1;
  private static int tracker = 87;
  private String iceElectric = "IceElectric";

  public void painSplit(Gastrodon p) {
    System.out.println(resources.getString("GastrodonVPainSplitGastrodonMessage"));
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
    System.out.println(resources.getString("GastrodonForesightMessage"));
  }

  public void painSplit(Shellos p) {
    System.out.println(resources.getString("GastrodonPainSplitShellosMessage"));
  }

  public void swordsDance() {
    System.out.println(iceElectric == ice+electric);
    System.out.println(iceElectric == new String("IceElectric"));
    System.out.println(iceElectric == (ice+electric).intern());
    System.out.println(iceElectric == new String("Ice"+"Electric"));
  }

  public void batonPass() {
    System.out.println(resources.getString("GastrodonBatonPassMessage"));
  }
}