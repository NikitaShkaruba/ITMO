import javax.swing.*;
import java.awt.*;

/**
 * Created by Nikita on 10/22/2015.
 */
class GPanel extends JPanel {
    public Point selectedPoint = new Point(60, 60);
    public int pointSize = 3;
    public int R = 100;

    private Point center;
    public boolean doContains = false;

    public GPanel() {
        this.setBackground(Color.white);
    }
    public Point getCenterPoint() {
        return center;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        center = new Point(this.getWidth()/2, this.getHeight() / 2);

        printFigure(g);
        printAxes(g);
        printLabels(g);
        printSelectedPoint(g);
    }
    private void printFigure(Graphics g) {
        int[] xPoints = { -R, -R, 0, R/2, -R };
        int[] yPoints = { 0, -R/2, -R/2, 0, 0};

        setOffset(xPoints, center.x);
        reverse(yPoints);
        setOffset(yPoints, center.y);

        g.setColor(new Color(51, 153, 255));
        g.fillPolygon(xPoints, yPoints, 5);
        g.fillArc(center.x - R / 2, center.y - R / 2, R, R, 90, 90);
    }
    private void printAxes(Graphics g) {
        int h = this.getHeight();
        int w = this.getWidth();

        g.setColor(new Color(50, 50, 50));
        g.drawLine(0 + 20, h / 2, w - 20, h / 2);
        g.drawLine(w / 2, 0 + 20, w / 2, h - 20);
    }
    private void printLabels(Graphics g) {
        g.setColor(new Color(250, 59, 78));
        g.fillOval(center.x - R - 3, center.y - 3, 6, 6);
        g.fillOval(center.x + R - 3, center.y - 3, 6, 6);
        g.fillOval(center.x - 3, center.y - R - 3, 6, 6);
        g.fillOval(center.x - 3, center.y + R - 3, 6, 6);

        g.setColor(new Color(50, 50, 50));
        for (Integer i = -120; i <= 120; i += 30) {
            printMark(g, new Point(center.x + i, center.y), i.toString(), 4);
            printMark(g, new Point(center.x, center.y - i), i.toString(), 4);
        }
    }
    private void printMark(Graphics g, Point point, String label, int radius) {
        g.drawString(label, point.x, point.y + radius/2);
        g.fillOval(point.x - radius/2, point.y - radius/2, radius, radius);
    }
    private void printSelectedPoint(Graphics g) {
        if (doContains)
            g.setColor(new Color(43, 255, 29));
        else
            g.setColor(new Color(255, 137, 0));

        g.drawString(" " + selectedPoint.x + ", " + selectedPoint.y, center.x + selectedPoint.x, center.y - selectedPoint.y);
        g.fillOval(center.x + selectedPoint.x - pointSize/2, center.y - selectedPoint.y + pointSize/2, pointSize, pointSize);
    }

    private void setOffset(int[] points, int offset) {
        for (int i = 0; i < points.length; i++)
            points[i] += offset;
    }
    private void reverse(int[] points) {
        for (int i = 0; i < points.length; i++)
            points[i] *= -1;
    }
}