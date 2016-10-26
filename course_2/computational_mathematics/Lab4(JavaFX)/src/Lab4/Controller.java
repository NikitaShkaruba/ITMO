package Lab4;

import javafx.beans.value.ObservableValue;
import javafx.beans.value.ChangeListener;
import javafx.stage.Stage;

/**
 * Created by nikita on 11/17/15.
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class Controller {
    View view;
    Model model;

    public Controller(Stage stage) {
        view = new View(stage);
        model = new Model();

        view.addSeries("Source function", model.getSourcePoints());
        model.updateEulerFunction();
        view.addSeries("Euler's function", model.getMyFuncChart());
        view.getXFirst().textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                try {
                    model.start.setX(Double.parseDouble(newValue));
                    model.updateEulerFunction();
                    view.changeLastSeries("Euler's function", model.getMyFuncChart());
                    view.hideAlarm();
                } catch (NumberFormatException ex) {
                    view.bustAlarm();
                }
            }
        });
        view.getYFirst().textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                try {
                    model.start.setY(Double.parseDouble(newValue));
                    model.updateEulerFunction();
                    view.changeLastSeries("Euler's function", model.getMyFuncChart());
                    view.hideAlarm();
                } catch (NumberFormatException ex) {
                    view.bustAlarm();
                }
            }
        });
        view.getXLast().textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                try {
                    model.last = (Double.parseDouble(newValue));
                    model.updateEulerFunction();
                    view.changeLastSeries("Euler's function", model.getMyFuncChart());
                    view.hideAlarm();
                } catch (NumberFormatException ex) {
                    view.bustAlarm();
                }
            }
        });
        view.getPrec().textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                try {
                    model.precision = (Double.parseDouble(newValue));
                    model.updateEulerFunction();
                    view.changeLastSeries("Euler's function", model.getMyFuncChart());
                    view.hideAlarm();
                } catch (NumberFormatException ex) {
                    view.bustAlarm();
                }
            }
        });
    }

    public void startApplication() {
        view.showStage();
    }
}
