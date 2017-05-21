package itmo.YandexPages;

import itmo.YandexPages.YandexPage;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class WriteMessagePage extends YandexPage {
  @FindBy(className = "_nb-large-action-button")
  private WebElement submitLetterButton;

  @FindBy(name = "subj")
  private static WebElement subjectInput;

  @FindBy(className = "cke_enable_context_menu")
  private static WebElement letterTextInput;

  @FindBy(name = "to")
  private static WebElement toInput;

  @FindBy(className = "mail-Done-Title")
  private WebElement isLetterDoneTitle;

  public WriteMessagePage(WebDriver driver) {
    PageFactory.initElements(driver, this);
    waitSecond();
  }

  public void insertRecipient(String text) {
    toInput.sendKeys(text);
  }
  public void insertTestSubject() {
    subjectInput.sendKeys("Subject");
  }
  public void insertTestMessageText() {
    letterTextInput.sendKeys("Test message text");
  }

  public void clickSendLetter() {
    submitLetterButton.click();

    try {
      Thread.sleep(1000);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }
  public boolean isLetterSuccessfullyDone() {
    return isLetterDoneTitle.isDisplayed();
  }
}
