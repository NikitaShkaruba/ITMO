package Lab3;

import javafx.application.Application;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.util.Callback;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.util.Optional;
import javafx.scene.Node;

public class Main extends Application {
    final NumberAxis xAxis = new NumberAxis();
    final NumberAxis yAxis = new NumberAxis();
    private LineChart<Number,Number> chart;
    private Pagination pagination = new Pagination(3);
    private Controller controller = new Controller(3);

    private void initializeGraphic(){
        xAxis.setLabel("x");
        xAxis.setLowerBound(-5);
        xAxis.setTickUnit(1);
        xAxis.setUpperBound(5);
        xAxis.setAutoRanging(false);

        yAxis.setLabel("y");
        yAxis.setLowerBound(-5);
        yAxis.setTickUnit(1);
        yAxis.setUpperBound(5);
        yAxis.setAutoRanging(false);

        chart = new LineChart<Number,Number>(xAxis,yAxis);
        chart.setCreateSymbols(false);
        chart.setAnimated(false);
    }
    private XYChart.Series getSinChart() {
        XYChart.Series sinSeries = new XYChart.Series();
        sinSeries.setName("Sin(x)");

        for (double x = -5; x < 5; x+=0.05)
            sinSeries.getData().add(new XYChart.Data(x, Math.sin(x)));

        return sinSeries;
    }

    @Override
    public void start(Stage stage) {
        stage.setTitle("Approximator(Lab 3)");
        initializeGraphic();

        // ---------- Prepare left chart side ---------- //
        chart.getData().add(getSinChart());
        // Bind controller to Chart
        for (int i = 0; i < controller.chartDataSeries.size(); i++) {
            XYChart.Series temp = new XYChart.Series(controller.chartDataSeries.get(i));
            temp.setName("Approximation" + i + "(x)");
            chart.getData().add(temp);
        }
        // Synchronized with chart coords mouse listener! AWESOME!
        Node chartBackground = chart.lookup(".chart-plot-background");
        chartBackground.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                controller.add(pagination.getCurrentPageIndex(), new Point((double)xAxis.getValueForDisplay(event.getX()),(double)yAxis.getValueForDisplay(event.getY())));
            }
        });


        // ---------- Prepare right stat side ---------- //
        pagination.setPageFactory(new Callback<Integer, Node>() {
            @Override   // That is called when a page has been selected by the application
            public Node call(Integer pageIndex) {
                VBox rightBox = new VBox();

                // Generate listView
                ListView<Point> listView = new ListView<>();
                listView.setEditable(true);
                listView.setPrefWidth(200);

                // Generate Buttons
                Button addButt = new Button("Add");
                Button deleteButt = new Button("Delete");
                Button testButt = new Button("Test");
                addButt.setOnAction(new EventHandler<ActionEvent>() {
                    @Override
                    public void handle(ActionEvent event) {
                        Dialog<Point> dialog = new Dialog<>();
                        dialog.setHeaderText("Input x and y!");

                        ButtonType AddButtonType = new ButtonType("Add", ButtonBar.ButtonData.OK_DONE);
                        dialog.getDialogPane().getButtonTypes().addAll(AddButtonType, ButtonType.CANCEL);

                        // Create the X and Y labels and fields
                        GridPane grid = new GridPane();
                        grid.setHgap(10);
                        grid.setVgap(10);
                        grid.setPadding(new Insets(20, 150, 10, 10));

                        TextField xField = new TextField();
                        xField.setPromptText("X");
                        TextField yField = new TextField();
                        yField.setPromptText("Y");

                        grid.add(new Label("X:"), 0, 0);
                        grid.add(xField, 1, 0);
                        grid.add(new Label("Y:"), 0, 1);
                        grid.add(yField, 1, 1);

                        dialog.getDialogPane().setContent(grid);
                        dialog.setResultConverter(dialogButton -> {
                            if (dialogButton == AddButtonType) {
                                return new Point(Double.parseDouble(xField.getText()),Double.parseDouble(yField.getText()));
                            }

                            return null;
                        });

                        Optional<Point> result = dialog.showAndWait();
                        if (result.get() != null)
                            controller.add(pagination.getCurrentPageIndex(), result.get());
                    }
                });
                deleteButt.setOnAction(new EventHandler<ActionEvent>() {
                    @Override
                    public void handle(ActionEvent event) {
                        controller.delete(pagination.getCurrentPageIndex(), listView.getSelectionModel().getSelectedIndex());
                    }
                });
                testButt.setOnAction(new EventHandler<ActionEvent>() {
                    @Override
                    public void handle(ActionEvent event) {
                        controller.setTestProbes();
                    }
                });
                HBox buttBox = new HBox();
                buttBox.setAlignment(Pos.CENTER);
                buttBox.getChildren().addAll(testButt, addButt, deleteButt);

                listView.setItems(controller.listDataSeries.get(pagination.getCurrentPageIndex()));
                rightBox.getChildren().addAll(listView, buttBox);

                return rightBox;
            }
        });

        // Pack left and right sides together
        HBox sceneContainer = new HBox();
        sceneContainer.setSpacing(10);
        sceneContainer.setPadding(new Insets(10, 10, 10, 10));
        sceneContainer.getChildren().addAll(chart, pagination);

        stage.setScene(new Scene(sceneContainer));
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}