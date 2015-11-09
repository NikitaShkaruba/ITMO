package Lab4;

import javax.swing.*;
import java.util.*;
import java.awt.*;

/**
 * Created by Nikita Shkaruba on 11/5/2015.
 * This project have a Readme.md on my GitHub, check it out, if you misunderstand something (!)
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class View extends JFrame {
    public StatisticPanel statPanel = new StatisticPanel();
    public ChartPanel chartPanel = new ChartPanel();

    public View(String title) {
        super(title);
        setViewComponents();
    }
    public Point getChartCenter() {
        return new Point(this.chartPanel.getWidth()/2, this.chartPanel.getHeight()/2);
    }

    public Point getCursorPoint() {
        return new Point((int)statPanel.xSpinner.getValue(), (int)statPanel.ySpinner.getValue());
    }
    private void setViewComponents() {
        // Properties
        this.setMinimumSize(new Dimension(600, 334));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setLocation(200, 200);

        // Layout
        JPanel windowPanel = (JPanel)this.getContentPane();
        windowPanel.setLayout(new GridLayout());
        windowPanel.add(chartPanel);
        windowPanel.add(statPanel);
    }
}

class ChartPanel extends JPanel {
    private Polygon figure = new Polygon();
    private Vector<Point> radiusMarks = new Vector<>(4);
    private Vector<Mark> customMarks = new Vector<>();
    private Point center = new Point(0, 0); // I initialize it because of model dependencies
    private Point cursor;

    public ChartPanel() {
        this.setBackground(Color.white);
    }

    public void updateFigure(Vector<Point> figurePoints, int R, Vector<Mark> marks, Point cursor) {
        this.center = new Point(this.getWidth()/2, this.getHeight()/2);
        this.cursor = new Point(cursor.x + center.x, -cursor.y + center.y);

        // Transfer logical offset to chartPanel's absolute(no negative coordinates) offset
        figure.reset();
        Iterator<Point> it = figurePoints.iterator();
        while (it.hasNext()) {
            Point temp = it.next();
            temp.x += center.x;
            temp.y *= -1;
            temp.y += center.y;

            figure.addPoint(temp.x, temp.y);
        }

        // Get custom marks
        this.customMarks.clear();
        Iterator<Mark> it2 = marks.iterator();
        while (it2.hasNext()) {
            Mark temp = it2.next();
            temp.x += center.x;
            temp.y *= -1;
            temp.y += center.y;

            this.customMarks.add(temp);
        }

        // Compute radius marks
        radiusMarks.clear();
        radiusMarks.add(0, new Point(center.x, -R * 7 + center.y));
        radiusMarks.add(0, new Point(center.x + R * 7, center.y));
        radiusMarks.add(0, new Point(center.x, R * 7 + center.y));
        radiusMarks.add(0, new Point(center.x - R * 7, center.y));

        this.repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        printFigure(g);
        printAxes(g);
        printLabels(g);
        printMarks(g);
        printCursor(g);
    }
    private void printAxes(Graphics g) {
        int h = this.getHeight();
        int w = this.getWidth();

        g.setColor(new Color(50, 50, 50));
        g.drawLine(0 + 10, h / 2, w - 10, h / 2);
        g.drawLine(w / 2, 0 + 10, w / 2, h - 10);
    }
    private void printFigure(Graphics g) {
        g.setColor(new Color(241, 250, 0));
        g.fillPolygon(figure);

        g.setColor(Color.BLACK);
        g.drawPolygon(figure);
    }
    private void printLabels(Graphics g) {
        // Print R Marks

        for (Point mark: radiusMarks) {
            g.setColor(new Color(250, 59, 78));
            g.fillOval(mark.x-3, mark.y -3, 6, 6);

            g.setColor(new Color(59, 59, 59));
            g.drawOval(mark.x - 3, mark.y - 3, 6, 6);
        }

        g.setColor(new Color(50, 50, 50));
        for (Integer i = -120; i <= 120; i += 30) {
            printMark(g, new Point(center.x + i, center.y), i.toString(), 4);
            printMark(g, new Point(center.x, center.y - i), i.toString(), 4);
        }
    }
    private void printMarks(Graphics g) {
        for (Mark mark: customMarks) {
            if (mark.isHighlighted) {
                g.setColor(new Color(100, 255, 253));
                g.fillOval(mark.x-3, mark.y -3, 6, 6);

                g.setColor(new Color(59, 59, 59));
                g.drawOval(mark.x - 3, mark.y - 3, 6, 6);
            } else {
                g.setColor(Color.BLACK);
                g.fillOval(mark.x - 3, mark.y - 3, 6, 6);

                g.setColor(new Color(226, 219, 226));
                g.drawOval(mark.x - 3, mark.y - 3, 6, 6);
            }
        }
    }
    private void printCursor(Graphics g) {
        g.setColor(Color.BLACK);
        g.drawOval(cursor.x - 4, cursor.y - 4, 8, 8);
    }
    private void printMark(Graphics g, Point point, String label, int radius) {
        g.drawString(label, point.x, point.y + radius/2);
        g.fillOval(point.x - radius/2, point.y - radius/2, radius, radius);
    }
}

class StatisticPanel extends JPanel {
    public JLabel xLabel = new JLabel("x: ");
    public JSpinner xSpinner = new JSpinner();
    public JLabel yLabel = new JLabel("y: ");
    public JSpinner ySpinner = new JSpinner();
    public JLabel RLabel = new JLabel("R: ");
    public JSlider RSlider = new JSlider(JSlider.HORIZONTAL, 0, 20, 20);
    public JButton diceButt = new JButton("Roll the dice");
    public JButton addButt = new JButton("Add");
    public JButton removeButt = new JButton("Remove");
    {
        xSpinner.setValue(0);
        ySpinner.setValue(0);

        RSlider.setMajorTickSpacing(5);
        RSlider.setMinorTickSpacing(1);
        RSlider.setPaintTicks(true);
        RSlider.setPaintLabels(true);
    }

    public StatisticPanel() {
        // Set panel properties
        this.setBackground(Color.WHITE);
        this.setLayout(new GridBagLayout());

        // Actual Layout: If you don't know what is constraints(!), just read about GridBagLayout
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.NONE;

        // Set buttons  /// It comes first because i want to mess around constraints as few as possible
        c.gridy = 3;
        c.gridx = 0;
        this.add(addButt, c);
        c.gridx = 1;
        this.add(removeButt, c);
        c.gridx = 2;
        this.add(diceButt, c);

        // Set labels
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

        // Set spinners
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
}