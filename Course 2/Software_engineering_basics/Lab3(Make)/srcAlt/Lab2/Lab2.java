package Lab2;

import java.util.Locale;

// Variant 1822
public class Lab2 {
  public static void main(String[] args) {
    //Locale.setDefault(new Locale("ru", "RU"));
    
    Gustav daughter = new Gustav();
    Sheldon mother = new Sheldon();
    Sheldon sister = new Gustav();

    sister.foresight();
    daughter.painSplit(sister);
    ((Gustav)sister).swordsDance();
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