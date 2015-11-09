package Lab4;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;
import java.beans.PropertyChangeSupport;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;

/**
 * Created by Nikita on 11/5/2015.
 */
public class Model {
    BatmanFigure batFigure = new BatmanFigure(0.001);
    public Vector<Point> registeredPoints = new Vector<>();
    private Vector<Mark> marks = new Vector<>();
    private Vector<Point2D.Double> figurePoints;
    private Point cursor = new Point(0, 0);
    private int R;

    public Model() {
        // Compute first state
        setR(20);
        InitializeFigure();
    }

    public int getR() {
        return R;
    }
    public void setR(int R) {
        this.R = R;

        RecalculateMarks();
        // My Dream: notify view thru controller
        // callFuigureChanged();
    }
    public Vector<Point> getFigurePoints() {
        Vector<Point> scaledPoints = new Vector<>();

        for (Enumeration<Point2D.Double> it = figurePoints.elements(); it.hasMoreElements();) {
            Point2D.Double next = it.nextElement();
            scaledPoints.add(new Point((int)(next.x * R), (int)(next.y * R)));
        }

        return scaledPoints;
    }
    public Point getCursor() {
        return cursor;
    }
    public void setCursor(Point point) {
        this.cursor = point;
    }
    public void addMark(Point point) {
        Point2D.Double buf = new Point2D.Double(point.x / (double)R, point.y / (double)R); // For unscaled doContains
        this.marks.add(new Mark(point, batFigure.doContains(buf)));
    }
    public void removeLastMark() {
        if (marks.size() != 0)
            marks.removeElementAt(marks.size()-1);
    }
    public Vector<Mark> getMarks() {
        Vector<Mark> buf = new Vector<Mark>();
        for (Mark m: marks)
            buf.add(new Mark(m));

        return buf;
    }

    private void InitializeFigure() {
        figurePoints = new Vector<>();

        figurePoints.addAll(batFigure.getFigurePoints());
    }
    private void RecalculateMarks() {
        for (Mark m: marks) {
            boolean previous = m.isHighlighted;
            Point2D.Double buf = new Point2D.Double(m.x / (double)R, m.y / (double)R);

            m.isHighlighted = batFigure.doContains(buf);

            if (m.isHighlighted == false && previous == true)
                register(m);
        }
    }
    public void register(Point point) {
        Iterator<Point> it = registeredPoints.iterator();

        while(it.hasNext()) {
            Point next = it.next();

            if (next.equals(it)) {
                return;
            }
        }

        registeredPoints.add(point);
    }
}

class Mark extends Point {
    public boolean isHighlighted;

    public Mark(Mark m) {
        this.x = m.x;
        this.y = m.y;

        this.isHighlighted = m.isHighlighted;
    }
    public Mark(Point point, boolean isHighlighted) {
        super(point);
        this.isHighlighted = isHighlighted;
    }
}

class BatmanFigure {
    Vector<Point2D.Double> figure = new Vector<>();

    public BatmanFigure(double precision) {
        // Left wing
        for (double y = -2.07; y <= 2.35; y += precision)
            figure.add(new Point2D.Double(-7.0 * Math.sqrt(1 - y*y/6.0), y));

        // Left Shoulder
        for (double x = -2.3; x <= -1; x += precision)
            figure.add(new Point2D.Double(x, (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(x)-1.0, 2)) + 5.7));

        // Left Hand side
        for (double x = -1.0; x <= -0.75; x += precision)
            figure.add(new Point2D.Double(x, 9-8*Math.abs(x)));

        // Left ear
        for (double x = -0.75; x < -0.5; x += precision)
            figure.add(new Point2D.Double(x, 3*Math.abs(x) + 0.75));

        // Forehead
        for (double x = -0.5; x <= 0.5; x += precision)
            figure.add(new Point2D.Double(x, 2.25));

        // Right ear
        for (double x = 0.5; x <= 0.75; x += precision)
            figure.add(new Point2D.Double(x, 3*Math.abs(x) + 0.75));

        // Right Hand side
        for (double x = 0.75; x <= 1; x += precision)
            figure.add(new Point2D.Double(x, 9-8*Math.abs(x)));

        // Right Shoulder (!)
        for (double x = 1.0; x <= 2.3; x += precision)
            figure.add(new Point2D.Double(x, (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(x)-1.0, 2)) + 5.7));

        // Right wing
        for (double y = 2.35; y >= -2.1; y -= precision)
            figure.add(new Point2D.Double(7.0 * Math.sqrt(1 - y * y / 6.0), y));

        // Legs and tail
        for (double x = 3.8; x >= -3.8; x -= precision)
            figure.add(new Point2D.Double(x, (Math.abs(x/2)- (3*Math.sqrt(33) - 7)/112*x*x - 3) + Math.sqrt(1 - (Math.pow(Math.abs(Math.abs(x)-2)-1 ,2)))));

    }

    public Vector<Point2D.Double> getFigurePoints() {
        return figure;
    }
    public boolean doContains(Point2D.Double point) { // Enhance this method
        if (point.y > 0) {
            // under top part of wings
            if (Math.abs(point.x) >= 2.0)
                return Math.pow(point.x, 2)/49.0 + Math.pow(point.y, 2)/6.0 <= 1;
            // under shoulders
            if (Math.abs(point.x) >= 1 && Math.abs(point.x) < 2.0)
                return point.y < (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(point.x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(point.x)-1.0, 2)) + 5.7;
            // under head sides
            if (Math.abs(point.x) >= 0.75 && Math.abs(point.x) < 1.0)
                return point.y < 9-8*Math.abs(point.x);
            // under ears
            if (Math.abs(point.x) >= 0.5 && Math.abs(point.x) < 0.75)
                return point.y < 3*Math.abs(point.x) + 0.75;
            // under forehead
            if (Math.abs(point.x) < 0.5)
                return point.y < 2.25;
        }

        if (point.y <= 0) {
            // over bottom part of wings
            if (Math.abs(point.x) < 3.75)
                return point.y > ((Math.abs(point.x/2)- (3*Math.sqrt(33) - 7)/112*point.x*point.x - 3) + Math.sqrt(1 - (Math.pow(Math.abs(Math.abs(point.x)-2)-1 ,2))));
            // over tail
            if (Math.abs(point.x) >= 3.75)
                return Math.pow(point.x, 2)/49.0 + Math.pow(point.y, 2)/6.0 <= 1;
        }

        // For readability and compiler sake
        return false;
    }
}