import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;

public class AreaCheckServlet extends HttpServlet {
    @Override
    public void init() {
        int x = 5;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        try(PrintWriter writer = response.getWriter()) {

            writer.println("<html><body>");
            writer.println("<p>Hello from <b>AreaCheck</b> servlet doGet()</p>");
            writer.println("</body></html>");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
