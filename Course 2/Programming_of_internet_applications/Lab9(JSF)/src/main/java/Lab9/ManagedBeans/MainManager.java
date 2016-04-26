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
    private List<Point2D.Float> pointsLog = new ArrayList<>();
    private Chart chart = new Chart();
    private float nextX;
    private float nextY;

    public void addPoint(float x, float y) {
        pointsLog.add(0, new Point2D.Float(x, y));

        // free lst if it's too large
        if (pointsLog.size() > 10)
            pointsLog.remove(pointsLog.size()-1);
    }

    public void addCurrentPoint() {
        addPoint(nextX, nextY);
    }
    public List<Point2D.Float> getPointsLog() {
        return pointsLog;
    }
    public StreamedContent getChartImage() {
        return chart.getImage(pointsLog);
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
        chart.getImage(pointsLog);
    }
}
