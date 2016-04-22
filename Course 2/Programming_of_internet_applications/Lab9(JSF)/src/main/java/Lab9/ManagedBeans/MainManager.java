package Lab9.ManagedBeans;

import org.primefaces.model.StreamedContent;
import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;
import Lab9.Chart;

@ManagedBean(name="mainManager", eager=true)
@ApplicationScoped
public class MainManager {
    List<Point2D.Float> pointLog = new ArrayList<>();
    private Chart chart = new Chart();
    private float nextX;
    private float nextY;

    public void addPoint(float x, float y) {
        pointLog.add(0, new Point2D.Float(x, y));

        // free lst if it' large
        if (pointLog.size() > 10)
            pointLog.remove(pointLog.size()-1);
    }

    public void addCurrentPoint() {
        addPoint(nextX, nextY);
    }
    public List<Point2D.Float> getPointLog() {
        return pointLog;
    }
    public StreamedContent getChartImage() {
        return chart.getImage(pointLog);
    }

    public float getX() {
        return nextX;
    }
    public void setX(float value) {
        nextX = value;
    }
    public float getY() {
        return nextY;
    }
    public void setY(float value) {
        nextY = value;
    }
    public float getRadius() {
        return chart.getRadius();
    }
    public void setRadius(float value) {
        chart.setRadius(value);
    }
    public void redrawChart() {
        chart.getImage(pointLog);
    }
}
