package itmo;

import itmo.YandexPages.InboxPage;
import itmo.YandexPages.LoginPage;
import itmo.YandexPages.SettingsPage;
import org.junit.*;
import org.openqa.selenium.WebDriver;
import static org.junit.Assert.*;

public class SettingsPageTest {
  WebDriver webDriver = ChromeWebDriverFactory.getDriver();
  LoginPage loginPage;

  @Before public void getMailPage() {
    loginPage = new LoginPage(webDriver);
  }

  @Test public void checkChangeInformation() {
    LoginPage mailPage = new LoginPage(webDriver);
    InboxPage inboxPage = mailPage.successfullyLogin();

    inboxPage.goToInboxTab();
    SettingsPage mailChangeDataPage = inboxPage.goToSettings();
    assertNotNull(mailChangeDataPage);

    mailChangeDataPage.clickChangePersonalInformation();
    mailChangeDataPage.clickInsertNewName();
    assertTrue(mailChangeDataPage.getFullName().equals("Никита Шкаруба"));
  }

  @After public void closeDriver() {
    webDriver.quit();
  }
}
