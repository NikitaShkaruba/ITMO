package Lab3;

import javafx.application.Application;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ListView;
import javafx.scene.control.Pagination;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.util.Vector;
import java.util.function.DoubleFunction;

class OrdinaryLeastSquaresCalcuator {
    public double[] Gauss(double[][] A) {
        int n = A.length;

        // Get triangular matrix
        for (int i=0; i<n; i++) {
            // Search for maximum in this column
            double maxEl = Math.abs(A[i][i]);
            int maxRow = i;
            for (int k=i+1; k<n; k++) {
                if (Math.abs(A[k][i]) > maxEl) {
                    maxEl = Math.abs(A[k][i]);
                    maxRow = k;
                }
            }

            // Swap maximum row with current row (column by column)
            double[] tmp = A[maxRow];
            A[maxRow] = A[i];
            A[i] = tmp;

            // // Subtract (Max row) * c - Make all rows below this one 0 in current column
            for (int k=i+1; k<n; k++) {
                double c = A[k][i]/A[i][i];
                for (int j=i; j<n+1; j++) {
                    A[k][j] -= c * A[i][j];
                }
            }
        }

        // Solve equation Ax=b for an upper triangular matrix A
        double[] x = new double[n];
        for (int i=n-1; i>=0; i--) {
            x[i] = A[i][n]/A[i][i];
            for (int k=i-1;k>=0; k--) {
                A[k][n] -= A[k][i] * x[i];
            }
        }
        return x;
    }
    public double calculatePolynom(double x, double[] coefficients) {
        double sum = 0;
        for (int i = 0; i < coefficients.length; i++)
            sum += Math.pow(x, i)*coefficients[i];

        return sum;
    }
    public DoubleFunction<Double> OrdinaryLeastSquares(Point[] points, int polynomRang) {
        // Matrix system is bA = c
        // All the +-1 is the additions due to counting from 0
        int bLength = polynomRang + 1;
        double[][] bc = new double[bLength][bLength+1];

        // compute b
        for (int k = 0; k < bLength; k++)
            for (int l = 0; l < bLength; l++)
                for (int i = 0; i < points.length; i++)
                    bc[k][l] += Math.pow(points[i].getX(), k + l);

        // compute c
        for (int k = 0; k < bLength; k++)
            for (int i = 0; i < points.length; i++)
                bc[k][bLength] += Math.pow(points[i].getX(), k) * points[i].getY();

        final double[] bb = Gauss(bc);
        // approximated function. Don't be ashamed of lambda's
        return (x) -> calculatePolynom(x, bb);
    }
}

class Point {
    public SimpleDoubleProperty x, y;

    Point(double x, double y) {
        this.x = new SimpleDoubleProperty(x);
        this.y = new SimpleDoubleProperty(y);
    }

   public double getX() {
        return x.get();
    }
    public void setX(Double x) {
        this.x.set(x);
    }
    public double getY() {
        return y.get();
    }
    public void setY(Double y) {
        this.y.set(y);
    }

    @Override
    public String toString() {
        return String.format("%.2f", x.get()) + " , " + String.format("%.2f", y.get());
    }
}

class ListController {
    public Vector<ObservableList<Point>> listDataSeries = new Vector<>();
    public Vector<ObservableList<XYChart.Data>> chartDataSeries = new Vector<>();
    private int seriesCount = 0;

    ListController(int amountOfSeries) {
        seriesCount = amountOfSeries;

        for (int i = 0; i < amountOfSeries; i++) {
            listDataSeries.add(FXCollections.observableArrayList());
            chartDataSeries.add(FXCollections.observableArrayList());
        }
    }

    public void add(int chartNumber, Point point) {
        assert(chartNumber <= seriesCount); // remove this later

        listDataSeries.get(chartNumber).add(point);
        chartDataSeries.get(chartNumber).add(new XYChart.Data(point.x.get(), point.y.get()));
    }
    /*public void update(int position, Double value) {
        chartDataSeries.set(position, new XYChart.Data(chartDataSeries.get(position).getXValue(), value));
    }*/
}

public class Main extends Application {
    final NumberAxis xAxis = new NumberAxis();
    final NumberAxis yAxis = new NumberAxis();
    private LineChart<Number,Number> lineChart;
    private Pagination pagination = new Pagination(3);

    private OrdinaryLeastSquaresCalcuator calc = new OrdinaryLeastSquaresCalcuator();
    private ListController controller = new ListController(3);

    private void initializeGraphic(){
        yAxis.setLabel("y");
        xAxis.setLabel("x");

        lineChart = new LineChart<Number,Number>(xAxis,yAxis);
        lineChart.setCreateSymbols(false);
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

        lineChart.getData().add(getSinChart());
        for (int i = 0; i < controller.chartDataSeries.size(); i++) {
            XYChart.Series temp = new XYChart.Series(controller.chartDataSeries.get(i));
            temp.setName("Approximation " + i);
            lineChart.getData().add(temp);
        }

        // Synchronized with chart coords mouse listener! AWESOME!
        Node chartBackground = lineChart.lookup(".chart-plot-background");
        chartBackground.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                controller.add(pagination.getCurrentPageIndex(), new Point((double)xAxis.getValueForDisplay(event.getX()),(double)yAxis.getValueForDisplay(event.getY())));
            }
        });

        pagination.setPageFactory(new Callback<Integer, Node>() {
            @Override   // that is called when a page has been selected by the application
            public Node call(Integer pageIndex) {
                ListView<Point> listView = new ListView<Point>();
                listView.setEditable(false);
                listView.setPrefWidth(200);
                listView.setItems(controller.listDataSeries.get(pageIndex));

                return listView;
            }
        });


        ListView<Point> listView = new ListView<Point>();
        listView.setEditable(false);
        listView.setPrefWidth(200);
        listView.setItems(controller.listDataSeries.get(0));

        HBox hBox = new HBox();
        hBox.setSpacing(10);
        hBox.setPadding(new Insets(10, 10, 10, 10));
        hBox.getChildren().addAll(lineChart, pagination);

        stage.setScene(new Scene(hBox));
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}