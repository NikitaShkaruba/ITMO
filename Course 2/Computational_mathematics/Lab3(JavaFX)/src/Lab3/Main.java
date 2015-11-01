package Lab3;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;
import java.util.ArrayList;

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
                    bc[k][l] += Math.pow(points[i].x, k + l);

        // compute c
        for (int k = 0; k < bLength; k++)
            for (int i = 0; i < points.length; i++)
                bc[k][bLength] += Math.pow(points[i].x, k) * points[i].y;

        final double[] bb = Gauss(bc);
        // approximated function. Don't be ashamed of lambda's
        return (x) -> calculatePolynom(x, bb);
    }
}

class Point {
    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    double x, y;
}

public class Main extends Application {
    @Override
    public void start(Stage stage) {
        OrdinaryLeastSquaresCalcuator calc = new OrdinaryLeastSquaresCalcuator();
        stage.setTitle("Approximator(Lab 3)");
        //defining the axes
        final NumberAxis xAxis = new NumberAxis();
        final NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("y");
        xAxis.setLabel("x");

        // creating the chart
        final LineChart<Number,Number> lineChart =
                new LineChart<Number,Number>(xAxis,yAxis);
        lineChart.setCreateSymbols(false);


        // defining a series 0
        XYChart.Series sinSeries = new XYChart.Series();
        sinSeries.setName("Sin(x)");
        for (double x = -5; x < 5; x+=0.05)
            sinSeries.getData().add(new XYChart.Data(x, Math.sin(x)));

        // defining a series 1
        ArrayList<Point> points = new ArrayList();
        points.add(new Point(-Math.PI, 0));
        points.add(new Point(-Math.PI, 0));
        points.add(new Point(-Math.PI/2, -1));
        points.add(new Point(0, 0));
        points.add(new Point(Math.PI/2, 1));
        points.add(new Point(Math.PI, 0));

        Point[] d = new Point[points.size()];
        points.toArray(d);
        DoubleFunction<Double> computedFunc = calc.OrdinaryLeastSquares(d, 4);
        XYChart.Series app1Series = new XYChart.Series();
        app1Series.setName("Approximated 1");
        for (double x = -5; x < 5; x+=0.05)
            app1Series.getData().add(new XYChart.Data(x, computedFunc.apply(x)));

        // defining a series 2
        points.add(new Point(-Math.PI/6, -Math.sqrt(3)/2));
        points.add(new Point(-Math.PI/4, -Math.sqrt(2)/2));
        points.add(new Point(-Math.PI/3, 1/2));
        points.add(new Point(Math.PI/3, 1/2));
        points.add(new Point(Math.PI/4, Math.sqrt(2)/2));
        points.add(new Point(Math.PI/6, Math.sqrt(3)/2));

        d = new Point[points.size()];
        points.toArray(d);
        computedFunc = calc.OrdinaryLeastSquares(d, 4);
        XYChart.Series app2Series = new XYChart.Series();
        app2Series.setName("Approximated 2");
        for (double x = -5; x < 5; x+=0.05)
            app2Series.getData().add(new XYChart.Data(x, computedFunc.apply(x)));

        // defining a series 3
        points.get(3).y = 3;

        d = new Point[points.size()];
        points.toArray(d);
        computedFunc = calc.OrdinaryLeastSquares(d, 4);
        XYChart.Series app3Series = new XYChart.Series();
        app3Series.setName("Approximated 3");
        for (double x = -5; x < 5; x+=0.05)
            app3Series.getData().add(new XYChart.Data(x, computedFunc.apply(x)));

        // defining a series 4
        points = new ArrayList();
        points.add(new Point(-15*Math.PI, 0));
        points.add(new Point(-11*Math.PI/2, 1));
        points.add(new Point(-7*Math.PI/2, 1));
        points.add(new Point(-5*Math.PI, 0));
        points.add(new Point(0, 0));
        points.add(new Point(5*Math.PI, 0));
        points.add(new Point(7*Math.PI/2, -1));
        points.add(new Point(11*Math.PI/2, -1));
        points.add(new Point(15*Math.PI, 0));

        d = new Point[points.size()];
        points.toArray(d);
        computedFunc = calc.OrdinaryLeastSquares(d, 4);
        XYChart.Series app4Series = new XYChart.Series();
        app4Series.setName("Approximated 4");
        for (double x = -5; x < 5; x+=0.05)
            app4Series.getData().add(new XYChart.Data(x, computedFunc.apply(x)));

        Scene scene = new Scene(lineChart,800,600);
        lineChart.getData().addAll(sinSeries, app1Series, app2Series, app3Series, app4Series);

        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}