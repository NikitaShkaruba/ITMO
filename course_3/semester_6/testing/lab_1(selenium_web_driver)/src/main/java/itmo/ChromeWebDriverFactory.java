package itmo;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.remote.DesiredCapabilities;

public class ChromeWebDriverFactory {
  public static WebDriver getDriver() {
    ChromeOptions options = new ChromeOptions();
    options.addArguments("-incognito");
    options.addArguments("--start-maximized");
    DesiredCapabilities capabilities = DesiredCapabilities.chrome();
    capabilities.setCapability(ChromeOptions.CAPABILITY, options);
    return new ChromeDriver(capabilities);
  }
}
