package itmo;

import org.junit.After;
import org.junit.Test;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

public class ChromeConnectionTest {
  WebDriver chromeDriver = new ChromeDriver();

  @Test public void connectionTest() {
    chromeDriver.get("http://de.ifmo.ru");
  }

  @After
  public void closeDriver() {
    chromeDriver.quit();
  }
}