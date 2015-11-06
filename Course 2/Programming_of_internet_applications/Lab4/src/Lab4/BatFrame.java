package Lab4;

import javax.swing.*;
import java.awt.*;
import java.util.*;

/**
 * Created by Nikita Shkaruba on 10/22/2015.
 */
public class BatFrame extends JFrame {
    public SPanel statPanel = new SPanel();
    public GPanel graphPanel = new GPanel();

    public BatFrame (String title) {
        super(title);

        setViewComponents();
        graphPanel.setPreferredSize(new Dimension(300, 300));
    }
    private void setViewComponents() {
        // Properties
        this.setMinimumSize(new Dimension(600, 300));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setLocation(200, 200);

        // Layout
        JPanel windowPanel = (JPanel)this.getContentPane();
        windowPanel.setLayout(new GridLayout());
        windowPanel.add(graphPanel);
        windowPanel.add(statPanel);
    }
}

class GPanel extends JPanel {
    private Polygon figure = new Polygon();
    private Vector<Point> RMarks = new Vector<>(4);
    private Vector<Mark> marks = new Vector<>();
    private Point center = new Point(0, 0);

    public GPanel() {
        this.setBackground(Color.white);
    }

    public void updateFigure(Vector<Point> figurePoints, int R, Vector<Mark> marks) {
        center = new Point(this.getWidth()/2, this.getHeight()/2);

        figure.reset();
        Iterator<Point> iter = figurePoints.iterator();
        while (iter.hasNext()) {
            Point temp = iter.next();
            temp.x += center.x;
            temp.y *= -1;
            temp.y += center.y;

            figure.addPoint(temp.x, temp.y);
        }

        this.marks.clear();
        Iterator<Mark> iter2 = marks.iterator();
        while (iter2.hasNext()) {
            Mark temp = iter2.next();
            temp.x += center.x;
            temp.y *= -1;
            temp.y += center.y;

            this.marks.add(temp);
        }

        RMarks.clear();
        RMarks.add(0, new Point(center.x, -R + center.y));
        RMarks.add(0, new Point(center.x + R, center.y));
        RMarks.add(0, new Point(center.x, R + center.y));
        RMarks.add(0, new Point(center.x - R, center.y));

        this.repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        printFigure(g);
        printAxes(g);
        printLabels(g);
        printMarks(g);
    }
    private void printAxes(Graphics g) {
        int h = this.getHeight();
        int w = this.getWidth();

        g.setColor(new Color(50, 50, 50));
        g.drawLine(0 + 20, h / 2, w - 20, h / 2);
        g.drawLine(w / 2, 0 + 20, w / 2, h - 20);
    }
    private void printFigure(Graphics g) {
        g.setColor(new Color(100, 95, 100));

        g.fillPolygon(figure);
    }
    private void printLabels(Graphics g) {
        // Print R Marks
        g.setColor(new Color(250, 44, 123));
        for (Point mark: RMarks)
            g.fillOval(mark.x-3, mark.y -3, 6, 6);


        g.setColor(new Color(50, 50, 50));
        for (Integer i = -120; i <= 120; i += 30) {
            printMark(g, new Point(center.x + i, center.y), i.toString(), 4);
            printMark(g, new Point(center.x, center.y - i), i.toString(), 4);
        }
    }
    private void printMarks(Graphics g) {
        for (Mark mark: marks) {
            if (mark.isHighlighted)
                g.setColor(new Color(43, 255, 29));
            else
                g.setColor(new Color(255, 174, 174));

            g.fillOval(mark.x-3, mark.y -3, 6, 6);
        }
    }
    private void printMark(Graphics g, Point point, String label, int radius) {
        g.drawString(label, point.x, point.y + radius/2);
        g.fillOval(point.x - radius/2, point.y - radius/2, radius, radius);
    }
}



class SPanel extends JPanel {
    public SPanel() {
        // Properties
        this.setBackground(new Color(226, 219, 226));
        this.setLayout(new GridBagLayout());

        // Layout: If you don't know what it is, just read about GridBagLayout
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.NONE;

        // Labels
        c.gridx = GridBagConstraints.HORIZONTAL;
        c.insets = new Insets(0, 20, 0, 0);
        c.gridwidth = 1;
        c.gridx = 0;
        c.gridy = 0;
        this.add(xLabel, c);
        c.gridy = 1;
        this.add(yLabel, c);
        c.gridy = 2;
        this.add(RLabel, c);

        // Spinners
        c.fill = GridBagConstraints.HORIZONTAL;
        c.insets = new Insets(2, 0, 2, 60);
        c.gridwidth = 5;
        c.weightx = 1;
        c.gridx = 1;
        c.gridy = 0;
        this.add(xSpinner, c);
        c.gridy = 1;
        this.add(ySpinner, c);
        c.gridy = 2;
        this.add(RSlider, c);
    }

    // Visible only in this package. That's the decision
    JLabel xLabel = new JLabel("x: ");
    JSpinner xSpinner = new JSpinner();
    JLabel yLabel = new JLabel("y: ");
    JSpinner ySpinner = new JSpinner();
    JLabel RLabel = new JLabel("R: ");
    JSlider RSlider = new JSlider(JSlider.HORIZONTAL, 0, 120, 75);
    {
        xSpinner.setValue(60);
        ySpinner.setValue(60);

        RSlider.setMajorTickSpacing(30);
        RSlider.setMinorTickSpacing(10);
        RSlider.setPaintTicks(true);
        RSlider.setPaintLabels(true);
    }
}
