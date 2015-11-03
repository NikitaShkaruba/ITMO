package Lab3;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.chart.XYChart;

import java.util.Vector;
import java.util.function.DoubleFunction;

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
        assert(chartNumber <= seriesCount); // remove this later
        //if (listDataSeries.get(chartNumber).contains(point)
        ObservableList<Point> currentList = listDataSeries.get(chartNumber);
        ObservableList<XYChart.Data> currentChart = chartDataSeries.get(chartNumber);

        currentList.add(point);

        if (currentList.size() > 2) {
            // this is necessary for implicit case
            Point[] buff = new Point[currentList.size()];
            currentList.toArray(buff);

            DoubleFunction<Double> approximation = calc.OrdinaryLeastSquares(buff, 4 );
            currentChart.clear();
            for (double x = -5; x < 5; x+=0.05)
                currentChart.add(new XYChart.Data(x, approximation.apply(x)));
        }
    }

/*    public void update(int chartNumber, int pos, Double val){
        chartDataSeries.get(chartNumber).set(pos, new XYChart.Data<>(chartDataSeries.get(chartNumber).get(pos).getXValue(), val));
    }*/
}
