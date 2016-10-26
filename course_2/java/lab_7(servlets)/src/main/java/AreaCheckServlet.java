import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.awt.*;
import java.awt.geom.Point2D;
import java.io.PrintWriter;
import java.util.Map;

public class AreaCheckServlet extends HttpServlet {
    @Override
    public void init() {
        int x = 5;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        double x = Double.valueOf(request.getParameterMap().get("x")[0]);
        double y = Double.valueOf(request.getParameterMap().get("y")[0]);
        double r = Double.valueOf(request.getParameterMap().get("r")[0]);
        boolean isInArea = calculateIsInArea(new Point2D.Double(x, y), r);

        response.setCharacterEncoding("UTF-8");

        try(PrintWriter writer = response.getWriter()) {
            writeStaticPageContent(writer, x, y, r, isInArea);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean calculateIsInArea(Point2D.Double point, double radius) {
        double x = point.getX();
        double y = point.getY();

        if (x >= 0 && y >= 0)
            return y <= -2*x + radius;
        if (x >= 0 && y <= 0)
            return x <= radius && y >= -radius/2;
        if (x <= 0 && y <= 0)
            return Math.pow(x, 2) + Math.pow(y, 2) <= Math.pow(radius/2, 2);
        if (x < 0 && y > 0)
            return false;

        // for the compiler's sake
        return false;
    }
    private void writeStaticPageContent(PrintWriter responseWriter, double x, double y, double r, boolean isInArea) {
        responseWriter.write("" +
        "<!DOCTYPE html>  \n" +
        "<html lang=\"en\"> \n" +
        "<head> \n" +
        "    <meta charset=\"UTF-8\"> \n" +
        "    <title>Area check</title> \n" +
        "</head> \n" +
        " \n" +
        "<body> \n" +
        "    <table border=\"1\"> \n" +
        "        <tr> \n" +
        "            <th>x</th> \n" +
        "            <th>y</th> \n" +
        "            <th>r</th> \n" +
        "        </tr> \n" +
        "        <tr> \n" +
        "            <td>" + x + "</td> \n" +
        "            <td>" + y + "</td> \n" +
        "            <td>" + r + "</td> \n" +
        "        </tr> \n" +
        "    </table> \n" +
        "    <div> \n" +
        "        <label>Точка <b>" + (isInArea? "В фигуре." : "Не в фигуре.") + "</b></label> \n" +
        "        <br/> <br/> \n" +
        "        <a href=\"/Lab7/\">Назад</a> \n" +
        "    </div> \n" +
        "</body> \n" +
        "</html>");
    }
}
