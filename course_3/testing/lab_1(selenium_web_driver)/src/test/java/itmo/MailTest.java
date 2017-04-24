package itmo;

import org.junit.*;
import org.openqa.selenium.WebDriver;

import static org.junit.Assert.*;

public class MailTest {
  WebDriver webDriver = ChromeWebDriverInstance.getDriver();

  MailPage mailPage;
  String login = "shkaruba.nikita";
  String password = System.getenv("YANDEX_PASS");

  @Before public void getMailPage() {
    mailPage = new MailPage(webDriver);
  }

  @Test public void loginError() {
    mailPage.insertLogin("error");
    mailPage.insertPassword("error");
    InboxPage inboxPage = mailPage.tryToLogin();

    assertEquals(null, inboxPage);
  }
  @Test public void successfulLogin() {
    InboxPage inboxPage = mailPage.successfullyLogin();

    assertNotEquals(null, inboxPage);
    inboxPage.logout();
  }

  @Test public void writeLetter() {
    InboxPage inboxPage = mailPage.successfullyLogin();

    MailWriteLetterPage mailWriteLetterPage = inboxPage.clickWriteToLetter();
    mailWriteLetterPage.insertTo(login + "@yandex.ru");
    mailWriteLetterPage.insertSubject("Subject");
    mailWriteLetterPage.insertTextLetter("Test message text");
    mailWriteLetterPage.clickWriteLetter();

    assertTrue(mailWriteLetterPage.isLetterSucessfullyDone());
    inboxPage.logout();
  }
  @Test public void searchLetter() {
    InboxPage inboxPage = mailPage.successfullyLogin();

    inboxPage.insertSearchQuery("Test");
    assertTrue(false);
  }
  @Test public void checkChangeInformation() {
    String textForLogin = "vicky.peony";
    String textForPassword = "12345qwerty";
    String textForNewName = "Виктория";

    MailPage mailPage = new MailPage(webDriver);
    mailPage.insertLogin(textForLogin);
    mailPage.insertPassword(textForPassword);
    InboxPage inboxPage = mailPage.tryToLogin();
    //write letter
    inboxPage.clickGoToInbox();
    MailChangeData mailChangeData = inboxPage.changePassword();
    mailChangeData.clickChangePersonalInformation();
    mailChangeData.clickInsertNewName(textForNewName);
    //inboxPage.logout();

    System.out.println("Ending test " + new Object() {
    }.getClass().getEnclosingMethod().getName());
  }
  @Test public void checkDeleteLetters() {
    String textForLogin = "vicky.peony";
    String textForPassword = "12345qwerty";
    String textForSubject = "Ку-ку";


    MailPage mailPage = new MailPage(webDriver);
    mailPage.insertLogin(textForLogin);
    mailPage.insertPassword(textForPassword);
    InboxPage inboxPage = mailPage.tryToLogin();

    inboxPage.clickGoToInbox();
    inboxPage.insertSearchQuery(textForSubject);
    inboxPage.clickSearchLetter();
    inboxPage.selectCheckbox();
    inboxPage.clickDeleteLetter();
    System.out.println("Ending test " + new Object() {
    }.getClass().getEnclosingMethod().getName());

    inboxPage.logout();
  }
  @Test public void checkCreateTemplate() {
    String textForLogin = "vicky.peony";
    String textForToInput = "vicky.peony@yandex.ru";
    String textForPassword = "12345qwerty";
    String textForSubject = "Ку-ку";
    String textForTextLetter = "Привет!";

    MailPage mailPage = new MailPage(webDriver);
    mailPage.insertLogin(textForLogin);
    mailPage.insertPassword(textForPassword);
    InboxPage inboxPage = mailPage.tryToLogin();

    inboxPage.clickGoToDraft();
    MailWriteLetterPage mailWriteLetterPage = inboxPage.clickCreateTemplate();
    mailWriteLetterPage.insertTo(textForToInput);
    mailWriteLetterPage.insertSubject(textForSubject);
    mailWriteLetterPage.insertTextLetter(textForTextLetter);
    inboxPage = mailWriteLetterPage.clickButtonSubmitSaveTemplate();
    inboxPage.clickGoToInbox();

    System.out.println("Ending test " + new Object() {
    }.getClass().getEnclosingMethod().getName());

    inboxPage.logout();
  }
  @Test public void checkDeleteLetter() {
    String textForLogin = "vicky.peony";
    String textForPassword = "12345qwerty";

    MailPage mailPage = new MailPage(webDriver);
    mailPage.insertLogin(textForLogin);
    mailPage.insertPassword(textForPassword);
    InboxPage inboxPage = mailPage.tryToLogin();

    inboxPage.selectCheckbox();
    inboxPage.clickDeleteLetter();
    System.out.println("Ending test " + new Object() {
    }.getClass().getEnclosingMethod().getName());

    inboxPage.logout();
  }

  @After public void afterTest() {
    webDriver.close();
  }
}
