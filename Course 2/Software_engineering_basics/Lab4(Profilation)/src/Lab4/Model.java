package Lab4;

import java.awt.geom.Point2D;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;
import java.awt.*;
import MBeans.*;

/**
 * Created by Nikita Shkaruba on 11/5/2015.
 * This project have a Readme.md on my GitHub, check it out, if you misunderstand something (!)
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class Model {
    private BatmanFigure batFigure;
    private Vector<Point> registeredPoints = new Vector<>();
    private Vector<Mark> marks = new Vector<>();
    private Point cursor = new Point(0, 0);
    private int R;
    public PointCounter pointCounter = new PointCounter();

    public Model() {
        batFigure = new BatmanFigure(0.001);
        setR(20);
    }

    public Vector<Point> getScaledFigurePoints() {
        Vector<Point> scaledPoints = new Vector<>();

        for (Enumeration<Point2D.Double> it = batFigure.getFigurePoints().elements(); it.hasMoreElements();) {
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

    public int getR() {
        return R;
    }
    public void setR(int R) {
        this.R = R;

        recalculateMarks();
    }

    public void addMark(Point point) {
        boolean doContains = batFigure.Contains(new Point2D.Double(point.x / (double) R, point.y / (double) R));
        this.marks.add(new Mark(point, doContains)); // Caution! method BatFigure.Contains works with unscaled points

        if (doContains)
            pointCounter.addHitPoint();
        else
            pointCounter.addMissPoint();
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

    public Vector<Point> getRegisteredPoints() {
        return registeredPoints;
    }
    public void clearRegisteredPoints() {
        registeredPoints.clear();
    }

    private void recalculateMarks() {
        for (Mark m: marks) {
            boolean wasHihlighted = m.isHighlighted;
            Point2D.Double buf = new Point2D.Double(m.x / (double)R, m.y / (double)R);

            m.isHighlighted = batFigure.Contains(buf);

            if (!m.isHighlighted && wasHihlighted)
                registerToAnimate(m);
        }
    }
    private void registerToAnimate(Point point) {
        // Sry for this unrefactored method. I don't really sure somebody will look at it ^)
        Iterator<Point> it = registeredPoints.iterator();

        // It's like registeredPoints.Contains(point) by logic
        while(it.hasNext()) {
            Point next = it.next();

            if (next.equals(it)) {
                return;
            }
        }

        registeredPoints.add(point);
    }
}

class BatmanFigure {

    private Vector<Point2D.Double> figure = new Vector<>();
    public BatmanFigure(double precision) {
        // Add left wing
        for (double y = -2.07; y <= 2.35; y += precision)
            figure.add(new Point2D.Double(-7.0 * Math.sqrt(1 - y*y/6.0), y));

        // Add left Shoulder
        for (double x = -2.3; x <= -1; x += precision)
            figure.add(new Point2D.Double(x, (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(x)-1.0, 2)) + 5.7));

        // Add left hand side
        for (double x = -1.0; x <= -0.75; x += precision)
            figure.add(new Point2D.Double(x, 9-8*Math.abs(x)));

        // Add left ear
        for (double x = -0.75; x < -0.5; x += precision)
            figure.add(new Point2D.Double(x, 3*Math.abs(x) + 0.75));

        // Add forehead
        for (double x = -0.5; x <= 0.5; x += precision)
            figure.add(new Point2D.Double(x, 2.25));

        // Add right ear
        for (double x = 0.5; x <= 0.75; x += precision)
            figure.add(new Point2D.Double(x, 3*Math.abs(x) + 0.75));

        // Add right hand side
        for (double x = 0.75; x <= 1; x += precision)
            figure.add(new Point2D.Double(x, 9-8*Math.abs(x)));

        // Add right shoulder
        for (double x = 1.0; x <= 2.3; x += precision)
            figure.add(new Point2D.Double(x, (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(x)-1.0, 2)) + 5.7));

        // Add right wing
        for (double y = 2.35; y >= -2.1; y -= precision)
            figure.add(new Point2D.Double(7.0 * Math.sqrt(1 - y * y / 6.0), y));

        // Add ... legs and tail ??? :D
        for (double x = 3.8; x >= -3.8; x -= precision)
            figure.add(new Point2D.Double(x, (Math.abs(x/2)- (3*Math.sqrt(33) - 7)/112*x*x - 3) + Math.sqrt(1 - (Math.pow(Math.abs(Math.abs(x)-2)-1 ,2)))));
    }

    public Vector<Point2D.Double> getFigurePoints() {
        return figure;
    }

    public boolean Contains(Point2D.Double point) { // Enhance this method
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

class Mark extends Point {
    public boolean isHighlighted;

    public Mark(Mark src) {
        super(src);

        this.isHighlighted = src.isHighlighted;
    }
    public Mark(Point src, boolean isHighlighted) {
        super(src);
        this.isHighlighted = isHighlighted;
    }
}
