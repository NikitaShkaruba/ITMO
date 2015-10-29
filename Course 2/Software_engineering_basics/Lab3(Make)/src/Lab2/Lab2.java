package Lab2;

import java.util.ResourceBundle;
import java.util.Locale;

// Вариант 1822
public class Lab2 {
  public static void main(String[] args) {
    Gastrodon daughter = new Gastrodon();
    Shellos mother = new Shellos();
    Shellos sister = new Gastrodon();

    sister.foresight();
    daughter.painSplit(sister);
    ((Gastrodon)sister).swordsDance();
    mother.painSplit(sister);
    mother.batonPass();
    daughter.foresight();
    daughter.focusEnergy();
    daughter.camouflage();
    daughter.batonPass();
    mother.torrent();
    mother.foresight();
    daughter.splash();
    daughter.painSplit(mother);
    sister.batonPass();
    sister.stickyHold();
    mother.painSplit(daughter);
  }
}

class Shellos {
  private static ResourceBundle resources = ResourceBundle.getBundle("Lab2", new Locale.Builder().setLanguage("ru").setScript("Cyrl").build());
  int sky;
  protected String shadowElectric = "ShadowElectric";
  public int troublesome;
  double height = 8.3;
  protected String electric ="Electric";
  protected byte juicer;
  protected String shadow = "Shadow";

  public Shellos() {
    troublesome = 060;
    juicer = (byte) 0x87;
  }

  {
    sky = 87;
    juicer = 76;
  }


  public void painSplit(Shellos p) {
    System.out.println(resources.getString("ShellosPainSplitShellosMessage"));
  }

  public void painSplit(Gastrodon p) {
    System.out.println(resources.getString("ShellosPainSplitGastrodonMessage"));
  }

  public void batonPass() {
    System.out.println(resources.getString("ShellosBatonPassMessage"));
  }

  public void torrent() {
    double speed = 4.9;

    System.out.println((height + speed) == 3.4);
  }

  public static void foresight() {
    System.out.println(resources.getString("ShellosForesightMessage"));
  }

  public void splash() {
    System.out.println(troublesome - juicer);
    System.out.println(sky - troublesome);
    System.out.println(juicer + sky);
  }

  public void stickyHold() {
    System.out.println(shadowElectric == "Shadow"+electric);
    System.out.println(shadowElectric.equals("Shadow"+"Electric"));
    System.out.println(shadowElectric.equals(shadow+"Electric"));
    System.out.println(shadowElectric.equals(shadow+electric));
    System.out.println(shadowElectric == shadow+electric);
    System.out.println(shadowElectric == "Shadow"+"Electric");
  }
}

class Gastrodon extends Shellos {
  private static ResourceBundle resources = ResourceBundle.getBundle("Lab2", new Locale.Builder().setLanguage("ru").setScript("Cyrl").build());
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


