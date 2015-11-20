package Lab5;

import java.awt.*;
import java.awt.geom.Point2D;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;

/**
 * Created by nikita on 11/18/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */
public class Model {
    BatmanFigure batmanFigure;
    private Vector<Point> registeredPoints = new Vector();
    private Vector<Mark> marks = new Vector();
    private Point cursor = new Point(0, 0);
    private int R;

    public Model() {
        batmanFigure = new BatmanFigure(0.001);
        setR(20);
    }

    public Vector<Point> getScaledFigurePoints() {
        Vector<Point> scaledPoints = new Vector();

        for (Enumeration<Point2D.Double> it = batmanFigure.getFigurePoints().elements(); it.hasMoreElements();) {
            Point2D.Double next = it.nextElement();
            scaledPoints.add(new Point((int)(next.x * R), (int)(next.y * R)));
        }

        return scaledPoints;

        // TODO: get Figure Points from server
        /*for (Enumeration<Point2D.Double> it = batFigure.getFigurePoints().elements(); it.hasMoreElements();) {
            Point2D.Double next = it.nextElement();
            scaledPoints.add(new Point((int)(next.x * R), (int)(next.y * R)));
        }*/
    }
    public Vector<Point2D.Double> getUnscaledMarks() {
        Vector<Point2D.Double> unscaledPoints = new Vector(marks.size());

        for (int i = 0; i < marks.size(); i++) {
            unscaledPoints.add(new Point2D.Double(marks.elementAt(i).getX() / (double)R, marks.elementAt(i).getY() / (double)R));
        }

        return unscaledPoints;
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
    }

    public void addMark(Point point, Mark.States state) {

        this.marks.add(new Mark(point, state));
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
    public void recalculateMarks(Vector<Mark.States> newStates) {
        for (int i = 0; i < marks.size(); i++) {
            if (marks.elementAt(i).state == Mark.States.outside && newStates.elementAt(i) == Mark.States.in)
                registerToAnimate(marks.elementAt(i));
            marks.elementAt(i).state = newStates.elementAt(i);
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

    private Vector<Point2D.Double> figure = new Vector();
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

    public Mark.States Contains(Point2D.Double point) { // Enhance this method
        if (point.y > 0) {
            // under top part of wings
            if (Math.abs(point.x) >= 2.0)
                return (Math.pow(point.x, 2)/49.0 + Math.pow(point.y, 2)/6.0 <= 1)? Mark.States.in : Mark.States.outside;
            // under shoulders
            if (Math.abs(point.x) >= 1 && Math.abs(point.x) < 2.0)
                return (point.y < (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(point.x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(point.x)-1.0, 2)) + 5.7)? Mark.States.in : Mark.States.outside;
            // under head sides
            if (Math.abs(point.x) >= 0.75 && Math.abs(point.x) < 1.0)
                return (point.y < 9-8*Math.abs(point.x))? Mark.States.in : Mark.States.outside;
            // under ears
            if (Math.abs(point.x) >= 0.5 && Math.abs(point.x) < 0.75)
                return (point.y < 3*Math.abs(point.x) + 0.75)? Mark.States.in : Mark.States.outside;
            // under forehead
            if (Math.abs(point.x) < 0.5)
                return (point.y < 2.25)? Mark.States.in : Mark.States.outside;
        }

        if (point.y <= 0) {
            // over bottom part of wings
            if (Math.abs(point.x) < 3.75)
                return (point.y > ((Math.abs(point.x/2)- (3*Math.sqrt(33) - 7)/112*point.x*point.x - 3) + Math.sqrt(1 - (Math.pow(Math.abs(Math.abs(point.x)-2)-1 ,2)))))? Mark.States.in : Mark.States.outside;
            // over tail
            if (Math.abs(point.x) >= 3.75)
                return (Math.pow(point.x, 2)/49.0 + Math.pow(point.y, 2)/6.0 <= 1)? Mark.States.in : Mark.States.outside;
        }

        // For readability and compiler sake
        return Mark.States.suspended;
    }
}
