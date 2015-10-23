import com.sun.corba.se.impl.orbutil.graph.Graph;

import javax.swing.*;
import java.awt.*;

/**
 * Created by Nikita on 10/22/2015.
 */
public class BatFrame extends JFrame {
    public BatFrame (String title) {
        super(title);

        this.setMinimumSize(new Dimension(600, 300));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setLocation(200, 200);

        JPanel windowPanel = (JPanel)this.getContentPane();
        windowPanel.setLayout(new GridLayout());
        windowPanel.add(graphPanel);
        windowPanel.add(statPanel);
    }

    private SPanel statPanel = new SPanel();
    private GPanel graphPanel = new GPanel();
}
