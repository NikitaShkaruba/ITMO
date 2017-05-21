package itmo;

import itmo.YandexPages.InboxPage;
import itmo.YandexPages.LoginPage;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.openqa.selenium.WebDriver;
import static org.junit.Assert.*;

public class LoginPageTest {
  WebDriver webDriver = ChromeWebDriverFactory.getDriver();
  LoginPage mailPage;

  @Before public void getMailPage() {
    mailPage = new LoginPage(webDriver);
  }

  @Test public void loginError() {
    mailPage.insertLogin("error");
    mailPage.insertPassword("error");
    InboxPage inboxPage = mailPage.tryToLogin();

    assertNull(inboxPage);
    webDriver.close();
  }
  @Test public void successfulLogin() {
    InboxPage inboxPage = mailPage.successfullyLogin();
    assertNotNull(inboxPage);
  }

  @After public void closeDriver() {
    webDriver.quit();
  }
}
