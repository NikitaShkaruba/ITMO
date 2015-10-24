import javax.swing.*;
import java.awt.*;

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
