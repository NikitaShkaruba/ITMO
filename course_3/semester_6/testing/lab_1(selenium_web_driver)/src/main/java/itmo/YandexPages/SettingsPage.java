package itmo.YandexPages;

import itmo.YandexPages.YandexPage;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import static java.lang.Thread.sleep;

public class SettingsPage extends YandexPage {
  @FindBy(css = ".nav-item:nth-child(1)")
  private static WebElement personalInformation;

  @FindBy(linkText = "Изменить персональные данные")
  private static WebElement changePersonalInformation;

  @FindBy(className = "personal-info-name")
  private WebElement accountName;

  @FindBy(css = ".control-personalInfoEditForm button[type=submit]")
  private static WebElement saveChange;

  public SettingsPage(WebDriver webDriver) {
    PageFactory.initElements(webDriver, this);
    waitForPageToLoad();
  }

  public void clickInsertNewName() {
    saveChange.click();
  }

  public String getFullName() {
    return accountName.getText();
  }

  public void clickChangePersonalInformation() {
    personalInformation.click();
    waitForChangePersonalInformationDisplayedToLoad();
    changePersonalInformation.click();
  }

  protected void waitForPageToLoad() {
    int secondsCount = 0;
    boolean isPageOpenedIndicator = isPersonalInformationDisplayed();
    while (!isPageOpenedIndicator && secondsCount < 20) {
      try {
        sleep(1000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
      secondsCount++;
      isPageOpenedIndicator = isPersonalInformationDisplayed();
    }
    if (!isPageOpenedIndicator) {
      throw new AssertionError("Personal Information was not opened");
    }
  }

  private boolean isPersonalInformationDisplayed() {
    try {
      return personalInformation.isDisplayed();
    } catch (NoSuchElementException e) {
      return false;
    }
  }

  protected void waitForChangePersonalInformationDisplayedToLoad() {
    int secondsCount = 0;
    boolean isPageOpenedIndicator = isChangePersonalInformationDisplayed();
    while (!isPageOpenedIndicator && secondsCount < 10) {
      try {
        sleep(1000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
      secondsCount++;
      isPageOpenedIndicator = isChangePersonalInformationDisplayed();
    }
    if (!isPageOpenedIndicator) {
      throw new AssertionError("Change Personal Information Displayed was not opened");
    }
  }

  private boolean isChangePersonalInformationDisplayed() {
    try {
      return changePersonalInformation.isDisplayed();
    } catch (NoSuchElementException e) {
      return false;
    }
  }
}
