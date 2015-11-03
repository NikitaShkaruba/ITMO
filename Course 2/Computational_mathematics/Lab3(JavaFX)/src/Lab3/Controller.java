package Lab3;

import java.util.function.DoubleFunction;
import javafx.collections.ObservableList;
import javafx.collections.FXCollections;
import javafx.scene.chart.XYChart;
import java.util.Vector;

// Controller handles all the data insertion and deletion. Main logic class
public class Controller {
    private Calculator calc = new Calculator();
    public Vector<ObservableList<Point>> listDataSeries = new Vector<>();
    public Vector<ObservableList<XYChart.Data>> chartDataSeries = new Vector<>();
    private int seriesCount = 0;

    Controller(int amountOfSeries) {
        seriesCount = amountOfSeries;

        for (int i = 0; i < amountOfSeries; i++) {
            listDataSeries.add(FXCollections.observableArrayList());
            chartDataSeries.add(FXCollections.observableArrayList());
        }
    }

    public void add(int chartNumber, Point point) {
        if (!listDataSeries.get(chartNumber).stream().anyMatch(x -> x.equals(point))) {
            ObservableList<Point> currentList = listDataSeries.get(chartNumber);

            currentList.add(point);
            update(chartNumber);
        }
    }
    public void delete(int chartNumber, int position) {
        if (listDataSeries.size() > 0 && position >= 0) {
            listDataSeries.get(chartNumber).remove(position);
            update(chartNumber);
        }
    }
    public void setTestProbes() {
        for (ObservableList<Point> series : listDataSeries)
            series.clear();

        // case 1
        add(0, new Point(-Math.PI, 0));
        add(0, new Point(-Math.PI/2, -1));
        add(0, new Point(0, 0));
        add(0, new Point(Math.PI / 2, 1));
        add(0, new Point(Math.PI, 0));

            // case 2
        add(1, new Point(-Math.PI, 0));
        add(1, new Point(-Math.PI / 2, -1));
        add(1, new Point(0, 0));
        add(1, new Point(Math.PI / 2, 1));
        add(1, new Point(Math.PI, 0));
        add(1, new Point(-Math.PI / 6, -Math.sqrt(3) / 2));
        add(1, new Point(-Math.PI / 4, -Math.sqrt(2) / 2));
        add(1, new Point(-Math.PI / 3, -1 / 2));
        add(1, new Point(Math.PI / 3, 1 / 2));
        add(1, new Point(Math.PI / 6, Math.sqrt(3) / 2));
        add(1, new Point(Math.PI / 4, Math.sqrt(2) / 2));

            // case 3
        add(2, new Point(-11 * Math.PI, -1));
        add(2, new Point(-15 * Math.PI, 0));
        add(2, new Point(-7 * Math.PI, -1));
        add(2, new Point(5 * Math.PI, 0));
        add(2, new Point(-3 * Math.PI, -1));
        add(2, new Point(0, 0));
        add(2, new Point(3 * Math.PI, 1));
        add(2, new Point(5 * Math.PI, 0));
        add(2, new Point(7 * Math.PI, 1));
        add(2, new Point(11 * Math.PI, 0));
        add(2, new Point(15 * Math.PI, 1));
    }
    private void update(int chartNumber) {
        ObservableList<Point> currentList = listDataSeries.get(chartNumber);
        ObservableList<XYChart.Data> currentChart = chartDataSeries.get(chartNumber);

        currentChart.clear();

        if (currentList.size() > 2) {
            // this is necessary for implicit case
            Point[] buff = new Point[currentList.size()];
            currentList.toArray(buff);

            DoubleFunction<Double> approximation = calc.OrdinaryLeastSquares(buff, 4 );
            for (double x = -5; x <= 5; x+= 0.1)
                currentChart.add(new XYChart.Data(x, approximation.apply(x)));
        }
        else if (currentList.size() == 2) {
            currentChart.add(new XYChart.Data(currentList.get(0).getX(), currentList.get(0).getY()));
            currentChart.add(new XYChart.Data(currentList.get(1).getX(), currentList.get(1).getY()));
        }
    }
}
