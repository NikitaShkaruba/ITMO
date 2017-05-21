package itmo.YandexPages;

import static java.lang.Thread.sleep;

public class YandexPage {
  protected void waitSecond() {
    try {
      sleep(1000);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }
}
