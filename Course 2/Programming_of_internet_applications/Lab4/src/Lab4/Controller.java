package Lab4;

import javafx.util.Callback;
import jdk.nashorn.internal.codegen.CompilerConstants;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Iterator;
import java.util.Random;
import java.util.Vector;
import java.util.function.Function;

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

        view.graphPanel.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                Point temp = e.getPoint();
                temp.x -= view.graphPanel.getWidth() / 2;
                temp.y -= view.graphPanel.getHeight() / 2;
                temp.y *= -1;

                if (e.getClickCount() == 2)
                    model.addMark(temp);
                else {
                    model.setCursor(temp);
                    view.statPanel.xSpinner.setValue(temp.x);
                    view.statPanel.ySpinner.setValue(temp.y);
                }
                updateView();
            }

            @Override
            public void mousePressed(MouseEvent e) {
            }
            @Override
            public void mouseReleased(MouseEvent e) {
            }
            @Override
            public void mouseEntered(MouseEvent e) {
            }
            @Override
            public void mouseExited(MouseEvent e) {
            }
        });
        view.statPanel.xSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                model.setCursor(new Point((int) ((JSpinner) e.getSource()).getValue(), model.getCursor().y));
                updateView();
            }
        });
        view.statPanel.ySpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                model.setCursor(new Point(model.getCursor().x, (int) ((JSpinner) e.getSource()).getValue()));
                updateView();
            }
        });
        view.statPanel.RSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int v = ((JSlider)e.getSource()).getValue();
                model.setR(v);

                Iterator it = model.registeredPoints.iterator();
                while (it.hasNext()) {
                    Point buf = new Point((Point)it.next());

                    buf.x += view.graphPanel.getWidth()/2;
                    buf.y *= -1;
                    buf.y += view.graphPanel.getHeight()/2;

                    new Thread(new Runnable() {
                        Graphics g = view.graphPanel.getGraphics();

                        @Override
                        public void run() {
                            int maxSize = 12;
                            int normalSize = 6;

                            for (int size = 0; size < maxSize ; size++) {
                                g.setColor(Color.WHITE);
                                g.fillOval(buf.x - maxSize / 2, buf.y - maxSize / 2, maxSize, maxSize);

                                g.setColor(Color.BLACK);
                                g.fillOval(buf.x - size / 2, buf.y - size / 2, size, size);

                                /*view.graphPanel.repaint(buf.x - 6 / 2, buf.y - 6 / 2, 6, 6);*/
                                try { Thread.sleep(50); }
                                catch(Exception ex) {}
                            }
                            for (int size = maxSize; size > normalSize; size--) {
                                g.setColor(Color.WHITE);
                                g.fillOval(buf.x - maxSize / 2, buf.y - maxSize / 2, maxSize, maxSize);

                                g.setColor(Color.BLACK);
                                g.fillOval(buf.x - size / 2, buf.y - size / 2, size, size);

                                /*view.graphPanel.repaint(buf.x - 6 / 2, buf.y - 6 / 2, 6, 6);*/
                                try { Thread.sleep(50); }
                                catch(Exception ex) {}
                            }
                            view.graphPanel.repaint();
                        }
                    }).start();
                }
                model.registeredPoints.clear();

                updateView();
            }
        });
        view.statPanel.diceButt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Random dice = new Random();
                Point center = view.getGrapCenter();
                Point randomed = new Point(dice.nextInt(2*center.x) - center.x, dice.nextInt(2*center.y) - center.y);

                view.statPanel.xSpinner.setValue(randomed.x);
                view.statPanel.ySpinner.setValue(randomed.y);
                model.addMark(randomed);
                model.setCursor(randomed);
                updateView();
            }
        });
        view.statPanel.addButt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                model.addMark(view.getCursorPoint());
                updateView();
            }
        });
        view.statPanel.removeButt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                model.removeLastMark();
                updateView();
            }
        });
    }

    public void startApplication() {
        view.setVisible(true);
        updateView();
    }
    private void updateView(){
        view.graphPanel.updateFigure(model.getFigurePoints(), model.getR(), model.getMarks(), model.getCursor());
    }
}