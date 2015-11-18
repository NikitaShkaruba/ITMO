package Lab4;

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
    private Vector<Point> registeredPoints = new Vector();
    private Vector<Mark> marks = new Vector();
    private Point cursor = new Point(0, 0);
    private int R;

    public Model() {
        setR(20);
    }

    public Vector<Point> getScaledFigurePoints() {
        Vector<Point> scaledPoints = new Vector();

        // TODO: call server
        /*for (Enumeration<Point2D.Double> it = batFigure.getFigurePoints().elements(); it.hasMoreElements();) {
            Point2D.Double next = it.nextElement();
            scaledPoints.add(new Point((int)(next.x * R), (int)(next.y * R)));
        }*/

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
        // TODO: call server
        // this.marks.add(new Mark(point, batFigure.Contains(new Point2D.Double(point.x / (double) R, point.y / (double) R)))); // Caution! method BatFigure.Contains works with unscaled points
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

            // TODO: call server
            // m.isHighlighted = batFigure.Contains(buf);

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
