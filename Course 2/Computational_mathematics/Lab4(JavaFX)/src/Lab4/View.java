package Lab4;

import javafx.scene.control.TextField;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.util.Vector;

/**2
 * Created by nikita on 11/17/15.
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class View {
    private Stage stage;
    private LineChart<Number, Number> chart;
    private VBox UIPanel;
    private TextField xBeginField;      // User Interface
    private TextField yBeginField;      // *
    private TextField xLastfield;       // *
    private TextField precisionField;   // *
    private Label alarmLabel; // Label for bad user input

    public View(Stage stage) {
        this.stage = stage;
        stage.setTitle("Lab 4");

        //----------- LeftPanel - chart setup -----------//
        NumberAxis xAxis = new NumberAxis();
        xAxis.setLabel("x");
        xAxis.setLowerBound(-5);
        xAxis.setTickUnit(1);
        xAxis.setUpperBound(5);
        xAxis.setAutoRanging(false);

        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("y");
        yAxis.setLowerBound(-5);
        yAxis.setTickUnit(1);
        yAxis.setUpperBound(5);
        yAxis.setAutoRanging(false);

        chart = new LineChart(xAxis,yAxis);
        chart.setCreateSymbols(false);
        chart.setAnimated(false);   // There's a JavaFX bug with animation, you don't believe me :D

        //----------- stat panel setup -----------//
        UIPanel = new VBox();

        HBox xbeginContainer = new HBox();
        xbeginContainer.setPadding(new Insets(20, 0, 0, 0));
        xbeginContainer.getChildren().add(new Label("First x: "));
        xBeginField = new TextField("-1");
        xbeginContainer.getChildren().add(xBeginField);

        HBox yBeginContainer = new HBox();
        yBeginContainer.getChildren().add(new Label("First y: "));
        yBeginField = new TextField("2");
        yBeginContainer.getChildren().add(yBeginField);

        HBox xLastClntainer = new HBox();
        xLastClntainer.getChildren().add(new Label("Last x: "));
        xLastfield = new TextField("5");
        xLastClntainer.getChildren().add(xLastfield);

        HBox precisionContainer = new HBox();
        precisionContainer.getChildren().add(new Label("Precis: "));
        precisionField = new TextField("0.01");
        precisionContainer.getChildren().add(precisionField);

        Label sourceDescriptor = new Label("Source: y' = 2 + 3x^2 - x^3");
        sourceDescriptor.setPadding(new Insets(20, 0, 0, 0));
        Label diffurDescriptor = new Label("Diffur: y' = 6x - 3x^2");

        alarmLabel = new Label("Warning: Bad input!");
        alarmLabel.setTextFill(Color.web("#FF2222"));
        alarmLabel.setVisible(false);
        UIPanel.getChildren().addAll(xbeginContainer, yBeginContainer, xLastClntainer, precisionContainer, sourceDescriptor, diffurDescriptor, alarmLabel);

        //----------- Packing all together -----------//
        HBox sceneContainer = new HBox();
        sceneContainer.setSpacing(10);
        sceneContainer.setPadding(new Insets(10, 10, 10, 10));
        sceneContainer.getChildren().addAll(chart, UIPanel);

        stage.setScene(new Scene(sceneContainer));
    }

    public void addSeries(String name, Vector<Point> points) {
        XYChart.Series series = new XYChart.Series();
        series.setName(name);
        for (Point p: points)
            series.getData().add(new XYChart.Data(p.getX(), p.getY()));

        chart.getData().add(series);
    }
    public void changeLastSeries(String name, Vector<Point> points) {
        chart.getData().remove(chart.getData().size()-1);
        addSeries(name, points);
    }
    public void showStage() {
        stage.show();
    }
    public void bustAlarm() {
        alarmLabel.setVisible(true);
    }
    public void hideAlarm() {
        alarmLabel.setVisible(false);
    }
    public TextField getXFirst() {
        return xBeginField;
    }
    public TextField getYFirst() {
        return yBeginField;
    }
    public TextField getXLast() {
        return xLastfield;
    }
    public TextField getPrec() {
        return precisionField;
    }
}