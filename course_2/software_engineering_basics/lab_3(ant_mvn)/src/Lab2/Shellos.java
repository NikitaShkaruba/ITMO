package Lab2;

import java.util.ResourceBundle;

public class Shellos {
  private static ResourceBundle resources = ResourceBundle.getBundle("Lab2");
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