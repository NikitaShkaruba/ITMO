package Lab4;

import javafx.application.Application;
import javafx.stage.Stage;

/**
 * Created by Nikita on 11/3/2015.
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class Main extends Application {
    @Override
    public void start(Stage stage) {
        Controller controller = new Controller(stage);
        controller.startApplication();
    }

    public static void main(String[] args) {
        launch(args);
    }
}