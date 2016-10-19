package Lab2;

import java.util.Locale;

// Variant 1822
public class Lab2 {
  public static void main(String[] args) {
    //Locale.setDefault(new Locale("ru", "RU"));
    
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