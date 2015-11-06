package Lab4;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/**
 * Created by Nikita Shkaruba on 11/5/2015.
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class Controller {
    private BatFrame view;
    private Model model;

    public Controller() {
        model = new Model();
        view = new BatFrame("Lab 4");

        view.statPanel.RSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int v = ((JSlider)e.getSource()).getValue();
                model.setR(v);
                view.graphPanel.updateFigure(model.getFigurePoints(), model.getR(), model.getMarks());
            }
        });
        view.graphPanel.addMouseListener(new MouseListener() {
            @Override // refactor this, omg. The whole your view of the project!
            public void mouseClicked(MouseEvent e) {
                Point temp = e.getPoint();
                temp.x -= view.graphPanel.getWidth()/2;
                temp.y -= view.graphPanel.getHeight()/2;
                temp.y *= -1;

                model.addMark(temp);
                /*statPanel.xSpinner.setValue(temp.x);
                statPanel.ySpinner.setValue(temp.y); */
                view.graphPanel.updateFigure(model.getFigurePoints(), model.getR(), model.getMarks());
            }

            @Override public void mousePressed(MouseEvent e) {}
            @Override public void mouseReleased(MouseEvent e) {}
            @Override public void mouseEntered(MouseEvent e) {}
            @Override public void mouseExited(MouseEvent e) {}
        });
    }

    public void startApplication() {
        view.setVisible(true);

    }
}