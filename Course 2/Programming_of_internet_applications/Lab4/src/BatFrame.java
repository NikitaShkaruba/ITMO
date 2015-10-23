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

        statPanel.xSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                graphPanel.sPoint.x = (int)((JSpinner)e.getSource()).getValue();
                graphPanel.repaint();
            }
        });
        statPanel.ySpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                graphPanel.sPoint.y = (int)((JSpinner)e.getSource()).getValue();
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
            @Override // refactor this, omg. Whole your view!
            public void mouseClicked(MouseEvent e) {
                Point temp = e.getPoint();
                temp.x -= graphPanel.center.x;
                temp.y -= graphPanel.center.y;
                temp.y *= -1;
                graphPanel.sPoint = temp;

                graphPanel.repaint();
            }

            @Override public void mousePressed(MouseEvent e) {}
            @Override public void mouseReleased(MouseEvent e) {}
            @Override public void mouseEntered(MouseEvent e) {}
            @Override public void mouseExited(MouseEvent e) {}
        });
    }

    private void setViewComponents() {
        // Dirty method
        this.setMinimumSize(new Dimension(600, 300));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setLocation(200, 200);

        JPanel windowPanel = (JPanel)this.getContentPane();
        windowPanel.setLayout(new GridLayout());
        windowPanel.add(graphPanel);
        windowPanel.add(statPanel);
    }
}
