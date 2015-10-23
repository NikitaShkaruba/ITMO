import javax.swing.*;
import java.awt.*;

/**
 * Created by Nikita on 10/22/2015.
 */
public class GPanel extends JPanel {
    public Point sPoint = new Point(20, 20); // Selected Point
    public int R = 100;

    public GPanel() {
        this.setBackground(Color.white);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Point center = new Point(this.getWidth()/2, this.getHeight()/2);
        printFigure(g, center);
        printAxes(g);
        printLabels(g, center);
        printSelectedPoint(g, center);
    }
    private void printFigure(Graphics g, Point offset) {
        int[] xPoints = { -R, -R, 0, R/2, -R };
        int[] yPoints = { 0, -R/2, -R/2, 0, 0};

        setOffset(xPoints, offset.x);
        reverse(yPoints);
        setOffset(yPoints, offset.y);

        g.setColor(new Color(51, 153, 255));
        g.fillPolygon(xPoints, yPoints, 5);
        g.fillArc(offset.x - R / 2, offset.y - R / 2, R, R, 90, 90);
    }
    private void printAxes(Graphics g) {
        int h = this.getHeight();
        int w = this.getWidth();

        g.setColor(new Color(50, 50, 50));
        g.drawLine(0 + 20, h / 2, w - 20, h / 2);
        g.drawLine(w / 2, 0 + 20, w / 2, h - 20);
    }
    private void printLabels(Graphics g, Point offset) {
        g.setColor(new Color(250, 59, 78));
        g.fillOval(offset.x - R, offset.y - 3, 6, 6);
        g.fillOval(offset.x + R, offset.y - 3, 6, 6);
        g.fillOval(offset.x - 3, offset.y - R, 6, 6);
        g.fillOval(offset.x - 3, offset.y + R, 6, 6);

        g.setColor(new Color(50, 50, 50));
        for (Integer i = -120; i <= 120; i += 30) {
            printMark(g, new Point(offset.x + i, offset.y - 2), i.toString());
            printMark(g, new Point(offset.x - 2, offset.y - i), i.toString());
        }

    }
    private void printMark(Graphics g, Point point, String label) {
        g.drawString(label, point.x, point.y);
        g.fillOval(point.x, point.y, 4, 4);
    }
    private void printSelectedPoint(Graphics g, Point offset) {
        g.setColor(new Color(100, 255, 253));
        g.drawString(" " + sPoint.x + ", " + sPoint.y, offset.x + sPoint.x, offset.y - sPoint.y);
        g.fillOval(offset.x + sPoint.x, offset.y - sPoint.y, 6, 6);
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
