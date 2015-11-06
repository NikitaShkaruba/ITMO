package Lab4;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import javax.swing.*;
import java.awt.*;
import java.beans.PropertyChangeSupport;
import java.util.Enumeration;
import java.util.Vector;

/**
 * Created by Nikita on 11/5/2015.
 */
public class Model {
    public Vector<Mark> marks = new Vector<>();
    private Vector<Point> figurePoints;
    private int R;

    public Model() {
        // Compute first state
        setR(70);
        InitializeFigure();
    }

    public int getR() {
        return R;
    }
    public void setR(int R) {
        this.R = R;

        RecalculateMarks();
        // Dream: notify Figure has changed
        //callFuigureChanged();
    }
    public Vector<Point> getFigurePoints() {
        Vector<Point> scaledPoints = new Vector<>();

        for (Enumeration<Point> it = figurePoints.elements(); it.hasMoreElements();) {
            Point next = it.nextElement();
            scaledPoints.add(new Point(next.x * R, next.y * R));
        }

        return scaledPoints;
    }

    public void addMark(Point point) {
        this.marks.add(new Mark(point, doContains(point)));
    }
    public Vector<Mark> getMarks() {
        Vector<Mark> buf = new Vector<Mark>();
        for (Mark m: marks)
            buf.add(new Mark(m));

        return buf;
    }

    private void InitializeFigure() {
        figurePoints = new Vector<>(4);

        figurePoints.addElement(new Point(1, 1));
        figurePoints.addElement(new Point(1, -1));
        figurePoints.addElement(new Point(-1, -1));
        figurePoints.addElement(new Point(-1, 1));
    }
    private void RecalculateMarks() {
        for (Mark m: marks)
            m.isHighlighted = doContains(m);
    }
    private boolean doContains(Point point) {
        return (point.x > -R && point.x < R && point.y < R && point.y > -R);
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

class BatEquatation {
    private Vector<Point> figure = new Vector<>();
    private int R;

    public BatEquatation(int R) {

    }

    private Vector<Point> computeLeftWing() {
        Vector<Point> temp = new Vector<>();

        for (int y = -R/3; y < R/3; y++) {
            temp.add(new Point((int)(7*Math.sqrt(1 - y*y/3)), y));
        }

        return temp;
    }
    private Vector<Point> computeLeftNeck() {
        Vector<Point> temp = new Vector<>();

        for (int x = -R*3/7; x < -R*1/7; x++) {
            temp.add(new Point(x, (int)((6*Math.sqrt(10)/7 + (1.5 - 0.5*Math.abs(x)))* (6*Math.sqrt(10)/14)*Math.sqrt(4 - (Math.pow(Math.abs(x) - 1, 2))))));
        }

        return temp;
    }
    private Vector<Point> computeLeftHead() {
        Vector<Point> temp = new Vector<>();

        for (int x = -R*1/7; x < -R*0.5/7; x++) {
            temp.add(new Point(x, 9 - 8* Math.abs(x)));
        }

        return temp;
    }
    private Vector<Point> computeTop() {
        Vector<Point> temp = new Vector<>();

        for (int x = -R/7/2; x < R/7/2; x++) {
            temp.add(new Point(x, (int)(2.25*R/3)));
        }

        return temp;
    }
    private Vector<Point> computeRightHead() {
        Vector<Point> temp = new Vector<>();

        for (int x = (int)(R*0.5/7); x < R*1/7; x++) {
            temp.add(new Point(x, 9 - 8* Math.abs(x)));
        }

        return temp;
    }
    private Vector<Point> computeRightNeck() {
        Vector<Point> temp = new Vector<>();

        for (int x = -R*3/7; x < -R*1/7; x++) {
            temp.add(new Point(x, (int)((6*Math.sqrt(10)/7 + (1.5 - 0.5*Math.abs(x)))* (6*Math.sqrt(10)/14)*Math.sqrt(4 - (Math.pow(Math.abs(x) - 1, 2))))));
        }

        return temp;
    }
    private Vector<Point> computeRightWing() {
        Vector<Point> temp = new Vector<>();

        for (int y = -R/3; y < R/3; y++) {
            temp.add(new Point((int)(-7*Math.sqrt(1 - y*y/3)), y));
        }

        return temp;
    }
    private Vector<Point> computeBot() {
        Vector<Point> temp = new Vector<>();

        for (int x = R*4/7; x < -R*4/7; x--) {
            temp.add(new Point(x, (int)((Math.abs(x/2)*(3*Math.sqrt(33)*7/112)*Math.pow(x, 2)-3)+ Math.sqrt(1 - Math.pow(Math.abs(1 - (Math.abs(x) - 2)-1), 2)))));
        }

        return temp;
    }
}