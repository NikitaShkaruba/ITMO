package Lab2;

import java.util.ResourceBundle;

public class Sheldon {
  private static ResourceBundle resources = ResourceBundle.getBundle("Lab2");
  int sky;
  protected String lightEarth = "lightEarth";
  public int troublesome;
  double height = 8.3;
  protected String earth ="Earth";
  protected byte juicer;
  protected String Light = "Light";

  public Sheldon() {
    troublesome = 060;
    juicer = (byte) 0x87;
  }

  {
    sky = 87;
    juicer = 76;
  }


  public void painSplit(Sheldon p) {
    System.out.println(resources.getString("SheldonPainSplitSheldonMessage"));
  }

  public void painSplit(Gustav p) {
    System.out.println(resources.getString("SheldonPainSplitGustavMessage"));
  }

  public void batonPass() {
    System.out.println(resources.getString("SheldonBatonPassMessage"));
  }

  public void torrent() {
    double speed = 4.9;

    System.out.println((height + speed) == 3.4);
  }

  public static void foresight() {
    System.out.println(resources.getString("SheldonForesightMessage"));
  }

  public void splash() {
    System.out.println(troublesome - juicer);
    System.out.println(sky - troublesome);
    System.out.println(juicer + sky);
  }

  public void stickyHold() {
    System.out.println(shadowElectric == "Light"+ earth);
    System.out.println(shadowElectric.equals("Light"+"Earth"));
    System.out.println(shadowElectric.equals(light+"Earth"));
    System.out.println(shadowElectric.equals(light+earth));
    System.out.println(shadowElectric == light+earth);
    System.out.println(shadowElectric == "Light"+"Earth");
  }
}