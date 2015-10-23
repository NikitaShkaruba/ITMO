import javax.swing.*;
import java.awt.*;

/**
 * Created by Nikita on 10/22/2015.
 */
public class SPanel extends JPanel {
    public SPanel() {
        this.setBackground(new Color(18, 30, 49));
        this.setLayout(new BorderLayout(4, 4));
        this.add(lbl1, BorderLayout.CENTER);
        this.add(lbl2, BorderLayout.EAST);
        this.add(lbl3, BorderLayout.SOUTH);
    }

    JLabel lbl1 = new JLabel("Label 1");
    JLabel lbl2 = new JLabel("Label 2");
    JLabel lbl3 = new JLabel("Label 3");
}
