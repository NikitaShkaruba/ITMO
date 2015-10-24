import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import javax.swing.*;
import java.awt.*;

/**
 * Created by Nikita Shkaruba on 10/22/2015.
 */
public class BatFrame extends JFrame {
    private SPanel statPanel = new SPanel();
    private GPanel graphPanel = new GPanel();

    public BatFrame (String title) {
        super(title);
        setViewComponents();

        // Event Listeners(handlers)
        statPanel.xSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                graphPanel.selectedPoint.x = (int)((JSpinner)e.getSource()).getValue();
                graphPanel.repaint();
            }
        });
        statPanel.ySpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                graphPanel.selectedPoint.y = (int)((JSpinner)e.getSource()).getValue();
                graphPanel.repaint();
            }
        });
        statPanel.RSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                graphPanel.R = (int)((JSlider)e.getSource()).getValue();
                graphPanel.repaint();
            }
        });
        graphPanel.addMouseListener(new MouseListener() {
            @Override // refactor this, omg. The whole your view of the project!
            public void mouseClicked(MouseEvent e) {
                Point temp = e.getPoint();
                transformPointToDecart(temp);

                statPanel.xSpinner.setValue(temp.x);
                statPanel.ySpinner.setValue(temp.y);
                if (compute(temp))
                    graphPanel.doContains = true;
                else
                    graphPanel.doContains = false;

                graphPanel.repaint();
            }

            @Override public void mousePressed(MouseEvent e) {}
            @Override public void mouseReleased(MouseEvent e) {}
            @Override public void mouseEntered(MouseEvent e) {}
            @Override public void mouseExited(MouseEvent e) {}
        });
        Runnable animTask = new Runnable()  {
            @Override
            public void run() {
                boolean growing = true;

                // I dunno why this is not working. It will work in debug!!!
                while (true) {
                    if (graphPanel.doContains) {
                        if (growing)
                            graphPanel.pointSize++;
                        else
                            graphPanel.pointSize --;

                        if (graphPanel.pointSize == 9)
                            growing = false;
                        if (graphPanel.pointSize == 2)
                            growing = true;

                        graphPanel.repaint();
                        try {
                            Thread.sleep(100);
                        } catch(InterruptedException ex) {} // !
                    } else {
                        graphPanel.pointSize = 3;
                    }
                }
            }
        };
        new Thread(animTask).start();
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
    private boolean compute(Point point) {
        if  (point.y > 0)
            return (point.x < 0 && Math.pow(point.x, 2) + Math.pow(point.y, 2) < Math.pow(graphPanel.R/2, 2));
        if (point.y < 0)
            return (point.x > -graphPanel.R && point.y > -graphPanel.R/2 && point.y > -graphPanel.R/2 + point.x);
        if (point.y == 0)
            return (point.x > -graphPanel.R/2 && point.x < 0);

        return (0 == -0);
    }
    private void transformPointToDecart(Point point) {
        Point center = graphPanel.getCenterPoint();

        point.x -= center.x;
        point.y -= center.y;
        point.y *= -1;
    }
}
