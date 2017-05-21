package itmo;

import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.concurrent.TimeUnit;

public class MailPage {
  private WebDriver webDriver;

  private String login = "shkaruba.nikita";
  private String password = System.getenv("YANDEX_PASS");

  @FindBy(className = "domik2__link")
  private WebElement tabMail;

  @FindBy(className = "domik2__auth-button")
  private WebElement submitButton;

  @FindBy(name = "login")
  private static WebElement loginField;

  @FindBy(name = "passwd")
  private static WebElement passwordField;

  public MailPage(WebDriver webDriver) {
    this.webDriver = webDriver;

    this.webDriver.get("http://yandex.ru");
    PageFactory.initElements(this.webDriver, this);
    waitForPageToLoad();
  }

  public void insertLogin(String text) {
    loginField.sendKeys(text);
  }
  public void insertPassword(String text) {
    passwordField.sendKeys(text);
  }
  public InboxPage tryToLogin() {
    submitButton.click();
    webDriver.manage().timeouts().pageLoadTimeout(10, TimeUnit.SECONDS);
    if (ChromeWebDriverInstance.getDriver().getTitle().toLowerCase().contains("авторизация")) {
      return null;
    }

    return new InboxPage(webDriver);
  }
  public InboxPage successfullyLogin() {
    this.insertLogin(login);
    this.insertPassword(password);
    return this.tryToLogin();
  }

  private void waitForPageToLoad() {
    try {
      Thread.sleep(1000);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    if (!isSearchStringDisplayed()) {
      throw new Error("Page can't be opened");
    }
  }
  private boolean isSearchStringDisplayed() {
    try {
      return tabMail.isDisplayed();
    } catch (NoSuchElementException e) {
      return false;
    }
  }
}

