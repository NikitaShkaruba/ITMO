package itmo.YandexPages;

import itmo.ChromeWebDriverFactory;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.concurrent.TimeUnit;

public class LoginPage extends YandexPage {
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

  public LoginPage(WebDriver webDriver) {
    this.webDriver = webDriver;

    this.webDriver.get("http://yandex.ru");
    PageFactory.initElements(this.webDriver, this);
    waitSecond();
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
    if (ChromeWebDriverFactory.getDriver().getTitle().toLowerCase().contains("авторизация")) {
      return null;
    }

    return new InboxPage(webDriver);
  }
  public InboxPage successfullyLogin() {
    this.insertLogin(login);
    this.insertPassword(password);
    return this.tryToLogin();
  }

  public String getMyEmail() {
    return this.login + "@yandex.ru";
  }
}

