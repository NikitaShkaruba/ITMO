package itmo;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.remote.DesiredCapabilities;

import java.util.Arrays;

public class ChromeWebDriverInstance {
    private static WebDriver webDriver;

    static {
        ChromeOptions options = new ChromeOptions();
        options.addArguments("-incognito");
        options.addArguments("--start-maximized");
        DesiredCapabilities capabilities = DesiredCapabilities.chrome();
        capabilities.setCapability(ChromeOptions.CAPABILITY, options);
        webDriver = new ChromeDriver(capabilities);
    }

    public static WebDriver getDriver() {
        return webDriver;
    }
}
