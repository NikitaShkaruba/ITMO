package Lab4;

import javafx.beans.property.SimpleDoubleProperty;
import java.util.function.DoubleFunction;
import java.util.function.BiFunction;
import java.util.Vector;

/**
 * Created by Nikita on 11/3/2015.
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class Model {
    private Vector<Point> sourcePoints;
    private Vector<Point> EulerPoints;
    public Point start;
    public Double last;
    public Double precision;

    public Model() {
        sourcePoints = new Vector<>();
        for (double x = -5; x < 5; x += 0.05)
            sourcePoints.add(new Point(x, 3*Math.pow(x,2) - Math.pow(x,3) - 2));

        EulerPoints = new Vector<>();
        // For the friendly user meeting ^)
        start = new Point(-1, 2);
        last = 5.0;
        precision = 0.01;
    }

    public Vector<Point> getSourcePoints() {
        // y = -2 + 3x^2 - x^3
        return sourcePoints;
    }
    public Vector<Point> getMyFuncChart() {
        // y' = 6x - 3x^2
        return EulerPoints;
    }

    public void updateEulerFunction() {
        EulerPoints.clear();

        DoubleFunction polynom = OrdinaryLeastSquares(Euler((Double x, Double y) -> { return 6*x - 3*Math.pow(x, 2); }, start, last, 0.01), 3);
        for(double i = start.getX(); i < last; i += 0.01) { // Low precision
            EulerPoints.add(new Point(i, (double)polynom.apply(i)));
        }
    }
    private Vector<Point> Euler(BiFunction<Double, Double, Double> fn, Point start, double last, double precision) {
        Vector<Point> result = new Vector<>();
        result.add(start);

        precision = Math.sqrt(precision);     // Look up Wikipedia for proof
        for (double i = start.getX() + precision; i < last; i += precision) {
            Point prev = result.lastElement();
            result.add(new Point(i, prev.getY() + ((i - prev.getX())*fn.apply(prev.getX(), prev.getY()))));
        }

        return result;
    }
    public DoubleFunction<Double> OrdinaryLeastSquares(Vector<Point> points, int polynomRang) {
        // Matrix system is bA = c
        // All the +-1 is the additions due to counting from 0
        int bLength = polynomRang + 1;
        double[][] bc = new double[bLength][bLength+1];

        // compute b
        for (int k = 0; k < bLength; k++)
            for (int l = 0; l < bLength; l++)
                for (int i = 0; i < points.size(); i++)
                    bc[k][l] += Math.pow(points.get(i).getX(), k + l);

        // compute c
        for (int k = 0; k < bLength; k++)
            for (int i = 0; i < points.size(); i++)
                bc[k][bLength] += Math.pow(points.get(i).getX(), k) * points.get(i).getY();

        final double[] bb = Gauss(bc);
        // approximated function. Don't be ashamed of lambda's
        return (x) -> calculatePolynom(x, bb);
    }
    public double calculatePolynom(double x, double[] coefficients) {
        double sum = 0;

        for (int i = 0; i < coefficients.length; i++)
            sum += Math.pow(x, i)*coefficients[i];

        return sum;
    }
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

    @Override
    public boolean equals(Object pretendent) {
        if (!(pretendent instanceof Point))
            return false;

        Point temp = (Point)pretendent;
        return temp.getX() == this.getX() && temp.getY() == this.getY();
    }
}