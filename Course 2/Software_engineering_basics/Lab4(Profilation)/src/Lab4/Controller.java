package Lab4;

import MBeans.PointCounter;

import javax.management.MXBean;
import javax.swing.event.ChangeListener;
import java.awt.Point;
import java.awt.event.ActionListener;
import javax.swing.event.ChangeEvent;
import java.awt.event.MouseListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.util.Iterator;
import java.util.Random;
import javax.swing.*;
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
public class Controller {
    private View view;
    private Model model;

    public Controller() {
        model = new Model();
        view = new View("Lab 4");

        view.chartPanel.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                Point temp = e.getPoint();
                temp.x -= view.chartPanel.getWidth() / 2;
                temp.y -= view.chartPanel.getHeight() / 2;
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

                Iterator it = model.getRegisteredPoints().iterator();
                while (it.hasNext()) {
                    Point buf = new Point((Point)it.next());

                    buf.x += view.chartPanel.getWidth()/2;
                    buf.y *= -1;
                    buf.y += view.chartPanel.getHeight()/2;

                    new Thread(new Runnable() {
                        Graphics g = view.chartPanel.getGraphics();

                        @Override
                        public void run() {
                            int maxSize = 12;
                            int normalSize = 6;

                            for (int size = 0; size < maxSize ; size++) {
                                g.setColor(Color.WHITE);
                                g.fillOval(buf.x - maxSize / 2, buf.y - maxSize / 2, maxSize, maxSize);

                                g.setColor(Color.BLACK);
                                g.fillOval(buf.x - size / 2, buf.y - size / 2, size, size);

                                /*view.chartPanel.repaint(buf.x - 6 / 2, buf.y - 6 / 2, 6, 6);*/
                                try { Thread.sleep(50); }
                                catch(Exception ex) {}
                            }
                            for (int size = maxSize; size > normalSize; size--) {
                                g.setColor(Color.WHITE);
                                g.fillOval(buf.x - maxSize / 2, buf.y - maxSize / 2, maxSize, maxSize);

                                g.setColor(Color.BLACK);
                                g.fillOval(buf.x - size / 2, buf.y - size / 2, size, size);

                                /*view.chartPanel.repaint(buf.x - 6 / 2, buf.y - 6 / 2, 6, 6);*/
                                try { Thread.sleep(50); }
                                catch(Exception ex) {}
                            }
                            view.chartPanel.repaint();
                        }
                    }).start();
                }
                model.clearRegisteredPoints();

                updateView();
            }
        });
        view.statPanel.diceButt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Random dice = new Random();
                Point center = view.getChartCenter();
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
        view.chartPanel.updateFigure(model.getScaledFigurePoints(), model.getR(), model.getMarks(), model.getCursor());
    }

    public PointCounter getPointCounterMBean() {
        return model.pointCounter;
    }
}