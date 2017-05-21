package itmo;

import itmo.YandexPages.InboxPage;
import itmo.YandexPages.LoginPage;
import itmo.YandexPages.WriteMessagePage;
import org.junit.*;
import org.openqa.selenium.WebDriver;
import static org.junit.Assert.*;

public class MailPageTest {
  WebDriver webDriver = ChromeWebDriverFactory.getDriver();
  LoginPage mailPage;

  @Before public void getMailPage() {
    mailPage = new LoginPage(webDriver);
  }

  @Test public void writeLetter() {
    InboxPage inboxPage = mailPage.successfullyLogin();

    WriteMessagePage mailWriteLetterPage = inboxPage.clickWriteToLetter();
    mailWriteLetterPage.insertRecipient(mailPage.getMyEmail());
    mailWriteLetterPage.insertTestSubject();
    mailWriteLetterPage.insertTestMessageText();

    mailWriteLetterPage.clickSendLetter();
    assertTrue(mailWriteLetterPage.isLetterSuccessfullyDone());
  }
  @Test public void searchLetter() {
    InboxPage inboxPage = mailPage.successfullyLogin();

    inboxPage.insertTestSearchQuery();
    assertTrue(inboxPage.isAnyLettersFound());
  }

  @After public void closeDriver() {
    webDriver.quit();
  }
}
