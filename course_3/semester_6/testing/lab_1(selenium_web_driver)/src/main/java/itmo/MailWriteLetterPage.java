package itmo;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

public class MailWriteLetterPage {
  private WebDriver webDriver;

  @FindBy(className = "_nb-large-action-button")
  private WebElement submitLetterButton;

  @FindBy(className = "ns-view-compose-save-link")
  private WebElement SubmitSaveTemplateButton;

  @FindBy(name = "subj")
  private static WebElement subjectInput;

  @FindBy(className = "cke_enable_context_menu")
  private static WebElement letterTextInput;

  @FindBy(name = "to")
  private static WebElement toInput;

  @FindBy(className = "mail-Done-Title")
  private WebElement isLetterDoneTitle;

  public MailWriteLetterPage(WebDriver driver) {
    webDriver = driver;

    PageFactory.initElements(webDriver, this);
    waitForButtonSubmitLetterToLoad();
  }

  public MailWriteLetterPage(WebDriver driver, String to, String subject, String letterText) {
    this(driver);

    this.insertTo(to);
    this.insertSubject(subject);
    this.insertTextLetter(letterText);
  }

  public InboxPage clickButtonSubmitSaveTemplate() {
    SubmitSaveTemplateButton.click();
    return new InboxPage(webDriver);
  }

  public void insertTo(String text) {
    toInput.sendKeys(text);
  }
  public void insertSubject(String text) {
    subjectInput.sendKeys(text);
  }
  public void insertTextLetter(String text) {
    letterTextInput.sendKeys(text);
  }

  public void clickWriteLetter() {
    submitLetterButton.click();
  }
  public boolean isLetterSucessfullyDone() {
    return isLetterDoneTitle.isDisplayed();
  }

  private void waitForButtonSubmitLetterToLoad() {
    try {
      Thread.sleep(1000);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    if (!isButtonSubmitLetterDisplayed()) {
      throw new Error("Button was not loaded");
    }
  }
  private boolean isButtonSubmitLetterDisplayed() {
    return submitLetterButton.isDisplayed();
  }
}
