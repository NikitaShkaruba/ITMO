import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

/**
 * Created by Nikita on 10/22/2015.
 */
public class SPanel extends JPanel {
    public SPanel() {
        this.setBackground(new Color(226, 219, 226));
        this.setLayout(new GridBagLayout());

        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.NONE;

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


        //c.weightx = 1;
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
        this.add(RSpinner, c);

        /*ChangeListener xSpinListener = new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {

            }
        }; */
    }

    JLabel xLabel = new JLabel("x: "); JSpinner xSpinner = new JSpinner();
    JLabel yLabel = new JLabel("y: "); JSpinner ySpinner = new JSpinner();
    JLabel RLabel = new JLabel("R: "); JSpinner RSpinner = new JSpinner();
    {
        xSpinner.setValue(20);
        ySpinner.setValue(20);
        RSpinner.setValue(100);
    }
}
