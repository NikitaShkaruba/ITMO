package Lab3;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.Callback;

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

        yAxis.setLabel("y");
        yAxis.setLowerBound(-5);
        yAxis.setTickUnit(1);
        yAxis.setUpperBound(5);


        chart = new LineChart<Number,Number>(xAxis,yAxis);
        chart.setCreateSymbols(false);
    }
    private XYChart.Series getSinChart() {
        XYChart.Series sinSeries = new XYChart.Series();
        sinSeries.setName("Sin(x)");

        for (double x = -5; x < 5; x+=0.05)
            sinSeries.getData().add(new XYChart.Data(x, Math.sin(x)));

        return sinSeries;
    }
    private void setTestCases() {
        // case 1
        controller.add(0, new Point(-Math.PI, 0));
        controller.add(0, new Point(-Math.PI/2, -1));
        controller.add(0, new Point(0, 0));
        controller.add(0, new Point(Math.PI/2, 1));
        controller.add(0, new Point(Math.PI, 0));

        // case 2
        controller.add(1, new Point(-Math.PI, 0));
        controller.add(1, new Point(-Math.PI/2, -1));
        controller.add(1, new Point(0, 0));
        controller.add(1, new Point(Math.PI/2, 1));
        controller.add(1, new Point(Math.PI, 0));
        controller.add(1, new Point(-Math.PI/6, -Math.sqrt(3)/2));
        controller.add(1, new Point(-Math.PI/4, -Math.sqrt(2)/2));
        controller.add(1, new Point(-Math.PI/3, -1/2));
        controller.add(1, new Point(Math.PI/3, 1/2));
        controller.add(1, new Point(Math.PI / 6, Math.sqrt(3) / 2));
        controller.add(1, new Point(Math.PI / 4, Math.sqrt(2) / 2));

        // case 3
        controller.add(2, new Point(-11*Math.PI, -1));
        controller.add(2, new Point(-15*Math.PI, 0));
        controller.add(2, new Point(-7*Math.PI, -1));
        controller.add(2, new Point(5*Math.PI, 0));
        controller.add(2, new Point(-3*Math.PI, -1));
        controller.add(2, new Point(0, 0));
        controller.add(2, new Point(3*Math.PI, 1));
        controller.add(2, new Point(5*Math.PI, 0));
        controller.add(2, new Point(7*Math.PI, 1));
        controller.add(2, new Point(11*Math.PI, 0));
        controller.add(2, new Point(15*Math.PI, 1));
    }

    @Override
    public void start(Stage stage) {
        stage.setTitle("Approximator(Lab 3)");
        initializeGraphic();

        // ---------- Prepare chart ---------- //
        chart.getData().add(getSinChart());
        for (int i = 0; i < controller.chartDataSeries.size(); i++) {
            XYChart.Series temp = new XYChart.Series(controller.chartDataSeries.get(i));
            temp.setName("Approximation " + i);
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


        // ---------- Prepare pagination ---------- //
        pagination.setPageFactory(new Callback<Integer, Node>() {
            @Override   // that is called when a page has been selected by the application
            public Node call(Integer pageIndex) {
                VBox vBox = new VBox();

                Label approximatedFunctionLbl = new Label("Approximation" + pagination.getCurrentPageIndex());
                approximatedFunctionLbl.setStyle(" -fx-border-color:black; -fx-border-width: 1; -fx-border-style: solid;");
                vBox.getChildren().add(approximatedFunctionLbl);

                ListView<Point> listView = new ListView<>();
                listView.setEditable(true);
                listView.setPrefWidth(200);
                listView.setItems(controller.listDataSeries.get(pagination.getCurrentPageIndex()));
                vBox.getChildren().add(listView);

                return vBox;
            }
        });

        // pack chart and pagination to a box
        setTestCases();
        HBox hBox = new HBox();
        hBox.setSpacing(10);
        hBox.setPadding(new Insets(10, 10, 10, 10));
        hBox.getChildren().addAll(chart, pagination);

        stage.setScene(new Scene(hBox));
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}