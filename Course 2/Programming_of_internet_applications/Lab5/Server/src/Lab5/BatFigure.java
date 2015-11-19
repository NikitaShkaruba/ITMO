package Lab5;

import java.awt.*;
import java.awt.geom.Point2D;
import java.util.Vector;

/**
 * Created by nikita on 11/18/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */
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
    public static Point2D.Double Parse(String str) {
        String[] splitted = str.split(",");
        return new Point2D.Double(new java.lang.Double(splitted[0]), new java.lang.Double(splitted[1]));
    }
}