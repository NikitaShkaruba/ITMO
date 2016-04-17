package Lab9;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.primefaces.event.SlideEndEvent;
import org.primefaces.model.DefaultStreamedContent;
import org.primefaces.model.StreamedContent;

import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import java.awt.*;
import java.io.File;
import java.io.FileInputStream;

@ManagedBean(name="chart", eager=true)
@ApplicationScoped
public class Chart {
    private StreamedContent image;
    private float radius = 2;

    public Chart() {
       redrawChart();
    }

    private XYSeriesCollection calculateChart(float radius) {
        final XYSeries series = new XYSeries("Batman");
        float precision = 0.001f;

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

        return new XYSeriesCollection(series);
    }

    public StreamedContent getImage() {
        return image;
    }

    public void onRadiusChange(SlideEndEvent event) {
        setRadius(event.getValue());

        redrawChart();
    }

    public void redrawChart() {
        try {
            JFreeChart chart = ChartFactory.createXYLineChart("Chart", "X", "Y", calculateChart(radius), PlotOrientation.VERTICAL, true, true, false);

            XYPlot plot = (XYPlot) chart.getPlot();
            plot.setBackgroundPaint(new Color(0, 0, 0));
            plot.setDomainGridlinePaint(new Color(255, 255, 0xff));
            plot.setRangeGridlinePaint(new Color(0xff, 255, 254));
            plot.getRenderer().setSeriesPaint(0, new Color(255, 241, 0x00));

            File file = new File("batman.png");
            ChartUtilities.saveChartAsPNG(file, chart, 375, 300);

            image = new DefaultStreamedContent(new FileInputStream(file), "image/png");
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public float getRadius() {
        return radius;
    }
    public void setRadius(float value) {
        radius = value;
    }
}
