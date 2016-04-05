import javafx.util.Pair;

import javax.servlet.RequestDispatcher;
import javax.servlet.http.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.Map;

public class ControllerServlet extends HttpServlet {
    @Override
    public void init() {
        // Create global context History parameter
        getServletContext().setAttribute("HitHistoryList",new ArrayList<Pair<Date, Boolean>>());
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        if (isAreaCheck(request.getParameterMap())) {
            try {
                getServletContext().getNamedDispatcher("AreaCheck").forward(request,response);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        } else {
            try {
                getServletContext().getNamedDispatcher("WebForm").forward(request,response);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    private boolean isAreaCheck(Map<String, String[]> map) {
        return map.get("x") != null && map.get("x").length == 1 && isDouble(map.get("x")[0]) &&
               map.get("y") != null && map.get("y").length == 1 && isDouble(map.get("y")[0]) &&
               map.get("r") != null && map.get("r").length == 1 && isDouble(map.get("r")[0]) &&
               Double.valueOf(map.get("r")[0]) >= 1.0 && Double.valueOf(map.get("r")[0]) <= 3;
    }
    private boolean isDouble(String s) {
        try {
            Double.valueOf(s);
            return true;
        } catch (Exception ex) {
            return false;
        }
    }
}
