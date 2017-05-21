package itmo;

import org.junit.Before;
import org.openqa.selenium.WebDriver;

public class MailLoginTests {
  WebDriver webDriver = ChromeWebDriverInstance.getDriver();

  MailPage mailPage;

  @Before public void getMailPage() {
    mailPage = new MailPage(webDriver);
  }
}
