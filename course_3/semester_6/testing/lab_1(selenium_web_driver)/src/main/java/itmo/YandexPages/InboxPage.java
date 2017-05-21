package itmo.YandexPages;

import itmo.ChromeWebDriverFactory;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class InboxPage extends YandexPage {
  WebDriver webDriver;

  @FindBy(className = "mail-User-Name")
  private WebElement mailUserName;

  @FindBy(xpath = "//a[@data-metric=\"Меню сервисов:Сменить пароль\"]")
  private WebElement tabChangePassword;

  @FindBy(className = "js-left-col-toolbar-compose")
  private WebElement tabWrite;

  @FindBy(className = "mail-Search-Input")
  private static WebElement searchFocus;

  @FindBy(className = "mail-MessagesSearchInfo-Title")
  private WebElement successfulSearchTitle;

  @FindBy(className = "mail-Search-Button")
  private static WebElement buttonSearchLetter;

  @FindBy(css = ".ns-view-folder:nth-child(1)")
  private static WebElement goToInbox;

  public InboxPage(WebDriver webDriver) {
    this.webDriver = webDriver;
    PageFactory.initElements(this.webDriver, this);
    waitSecond();
  }

  public void goToInboxTab() {
    goToInbox.click();
    waitSecond();
  }
  public SettingsPage goToSettings() {
    mailUserName.click();
    waitSecond();
    tabChangePassword.click();
    return new SettingsPage(webDriver);
  }

  public void insertTestSearchQuery() {
    Actions actions = new Actions(ChromeWebDriverFactory.getDriver());
    actions.moveToElement(searchFocus);
    actions.click();
    actions.sendKeys("Test");
    actions.build().perform();
    buttonSearchLetter.click();

    waitSecond();
  }
  public boolean isAnyLettersFound() {
    return successfulSearchTitle.isDisplayed();
  }
  public WriteMessagePage clickWriteToLetter() {
    tabWrite.click();
    return new WriteMessagePage(webDriver);
  }
}
