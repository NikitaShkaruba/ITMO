package Lab9;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.primefaces.model.DefaultStreamedContent;
import org.primefaces.model.StreamedContent;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.io.File;
import java.io.FileInputStream;
import java.util.List;

public class Chart {
    private float radius = 2;

    private XYSeries calculateChartSeries(float radius) {
        final XYSeries series = new XYSeries("Batman");
        float precision = 0.01f;

        // Add left wing
        for (double y = -2.07; y <= 2.35; y += precision)
            series.add((-7.0 * Math.sqrt(1 - y*y/6.0)) * radius, y * radius);

        // Add left Shoulder
        for (double x = -2.3; x <= -1; x += precision)
            series.add(x * radius, ((6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(x)-1.0, 2)) + 5.7) * radius);

        // Add left hand side
        for (double x = -1.0; x <= -0.75; x += precision)
            series.add(x * radius, (9-8*Math.abs(x)) * radius);

        // Add left ear
        for (double x = -0.75; x < -0.5; x += precision)
            series.add(x * radius, (3*Math.abs(x) + 0.75) * radius);

        // Add forehead
        for (double x = -0.5; x <= 0.5; x += precision)
            series.add(x * radius, 2.25 * radius);

        // Add right ear
        for (double x = 0.5; x <= 0.75; x += precision)
            series.add(x * radius, (3*Math.abs(x) + 0.75)* radius);

        // Add right hand side
        for (double x = 0.75; x <= 1; x += precision)
            series.add(x * radius, (9-8*Math.abs(x)) * radius);

        // Add right shoulder
        for (double x = 1.0; x <= 2.3; x += precision)
            series.add(x*radius, ((6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(x)-1.0, 2)) + 5.7) * radius);

        // Add right wing
        for (double y = 2.35; y >= -2.1; y -= precision)
            series.add((7.0 * Math.sqrt(1 - y * y / 6.0)) * radius, y * radius);

        // Add ... legs and tail ??? :D
        for (double x = 3.8; x >= -3.8; x -= precision)
            series.add(x * radius, ((Math.abs(x/2)- (3*Math.sqrt(33) - 7)/112*x*x - 3) + Math.sqrt(1 - (Math.pow(Math.abs(Math.abs(x)-2)-1 ,2)))) * radius);

        return series;
    }
    private XYSeries calculateHitPointSeries(List<Point2D.Float> points) {
        final XYSeries series = new XYSeries("Hits");

        for(Point2D.Float point: points)
            if (isHit(point))
                series.add(point.x, point.y);

        return series;
    }
    private XYSeries calculateMissPointSeries(List<Point2D.Float> points) {
        final XYSeries series = new XYSeries("Misses");

        for(Point2D.Float point: points)
            if (!isHit(point))
                series.add(point.x, point.y);

        return series;
    }

    private boolean isHit(Point2D.Float point) {
        Point2D.Float copy = new Point2D.Float();
        copy.x = point.x / radius;
        copy.y = point.y / radius;

        if (copy.y > 0) {
            // under top part of wings
            if (Math.abs(copy.x) >= 2.0)
                return Math.pow(copy.x, 2)/49.0 + Math.pow(copy.y, 2)/6.0 <= 1;
            // under shoulders
            if (Math.abs(copy.x) >= 1 && Math.abs(copy.x) < 2.0)
                return copy.y < (6.0*Math.sqrt(10)/7.0 + (1.5-0.5*Math.abs(copy.x)))-(6.0*Math.abs(10)/14.0)*Math.sqrt(4-Math.pow(Math.abs(copy.x)-1.0, 2)) + 5.7;
            // under head sides
            if (Math.abs(copy.x) >= 0.75 && Math.abs(copy.x) < 1.0)
                return copy.y < 9-8*Math.abs(copy.x);
            // under ears
            if (Math.abs(copy.x) >= 0.5 && Math.abs(copy.x) < 0.75)
                return copy.y < 3*Math.abs(copy.x) + 0.75;
            // under forehead
            if (Math.abs(copy.x) < 0.5)
                return copy.y < 2.25;
        }

        if (copy.y <= 0) {
            // over bottom part of wings
            if (Math.abs(copy.x) < 3.75)
                return copy.y > ((Math.abs(copy.x/2)- (3*Math.sqrt(33) - 7)/112*copy.x*copy.x - 3) + Math.sqrt(1 - (Math.pow(Math.abs(Math.abs(copy.x)-2)-1 ,2))));
            // over tail
            if (Math.abs(copy.x) >= 3.75)
                return Math.pow(copy.x, 2)/49.0 + Math.pow(copy.y, 2)/6.0 <= 1;
        }

        // For readability and compiler sake
        return false;
    }

    public float getRadius() {
        return radius;
    }
    public void setRadius(float value) {
        radius = value;
    }
    public StreamedContent getImage(List log) {
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(calculateChartSeries(radius));
        dataset.addSeries(calculateHitPointSeries(log));
        dataset.addSeries(calculateMissPointSeries(log));

        JFreeChart chart = ChartFactory.createScatterPlot("Chart", "X", "Y", dataset, PlotOrientation.VERTICAL, true, true, false);
        XYPlot plot = (XYPlot) chart.getPlot();

        // Set plot colors
        plot.setBackgroundPaint(new Color(0, 0, 0));
        plot.setDomainGridlinePaint(new Color(255, 255, 0xff));
        plot.setRangeGridlinePaint(new Color(0xff, 255, 254));

        // Series customization
        XYItemRenderer renderer = plot.getRenderer();
        renderer.setSeriesShape(0, new Ellipse2D.Double(0,0,1,1));
        renderer.setSeriesPaint(0, new Color(255, 241, 0));
        renderer.setSeriesPaint(1, new Color(0, 255, 0));
        renderer.setSeriesPaint(2, new Color(255, 0, 0));

        // Set axis ranges
        ValueAxis domainAxis = plot.getDomainAxis();
        ValueAxis rangeAxis = plot.getRangeAxis();
        domainAxis.setRange(-7.0 * 6, 7.0 * 6);
        rangeAxis.setRange(-7.0 * 4, 7.0 * 4);

        try {
            File file = new File("batman.png");
            ChartUtilities.saveChartAsPNG(file, chart, 375, 300);
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            return new DefaultStreamedContent(new FileInputStream(new File("batman.png")), "image/png");
        } catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
