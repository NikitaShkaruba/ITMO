import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class WebFormServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        response.setCharacterEncoding("UTF-8");
        writeStaticPageContent(request, response);
    }

    private void writeStaticPageContent(HttpServletRequest request, HttpServletResponse response) {
        try (PrintWriter writer = response.getWriter()) {
            writer.write("<!DOCTYPE html> \n");
            writer.write("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\n ");
            writer.write("<head> \n");
            writer.write("  <meta charset=\"UTF-8\">\n ");
            writer.write("  <title>Lab 7 - Servlets</title>\n");
            writer.write("  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js\"></script> \n");
            writer.write("  <style>\n");
            writer.write("      .redBorder {\n");
            writer.write("          border: 1px solid #ff0000\n");
            writer.write("      }\n");
            writer.write("  </style>");
            writer.write("</head>\n");
            writer.write("\n");

            writer.write("<body>\n");
            writer.write("<div id=\"wrap\">\n");
            writer.write("   <div id=\"header\">\n");
            writer.write("       <h3>\n");
            writer.write("           Старался: Никита Шкаруба <br/>\n");
            writer.write("           Группа: P3218 <br/>\n");
            writer.write("           Вариант: 424\n");
            writer.write("       </h3>\n");
            writer.write("   </div>\n");
            writer.write("   <div id=\"content\">\n");

            // Xes
            writer.write("       <form method=\"get\" action=\"WebForm\" class=\"boxa\">\n");
            writer.write("           <div id=\"xes\" class=\"inputs\">\n");
            writer.write("               <label>x: </label>\n");
            for (int i = -3; i < 5; i++) {
                writer.write("               <label>\n");
                writer.write("                 <input type=\"radio\" name=\"x\" value=\"" + i + "\" required/> \n");
                writer.write("                 " + i + "\n");
                writer.write("               </label> \n");
            }
            writer.write("           </div>\n");

            // Y
            writer.write("           <div id=\"ys\">\n");
            writer.write("               <label>\n");
            writer.write("                   y:\n");
            writer.write("                   <input id=\"y\" type=\"text\" required/>\n");
            writer.write("               </label>\n");
            writer.write("           </div>\n");

            // Rs
            writer.write("           <div id=\"rs\">\n");
            writer.write("               <label>r: </label>\n");
            for (double i = 1; i <= 3; i += 0.5) {
                writer.write("               <label>\n");
                writer.write("                  <input type=\"checkbox\" name=\"r\" value=\"" + i + "\" required/>\n");
                writer.write("                  " + i + "\n");
                writer.write("              </label>\n");
            }
            writer.write("           </div>\n");

            writer.write("            <input type=\"submit\" value=\"Проверить точку\">\n");
            writer.write("       </form>\n");
            writer.write("   </div>\n");
            writer.write("  <script> \n");
            writer.write("  $(\"input[name*='r'\").on('click', function() {\n");
            writer.write("      var $box = $(this);\n");
            writer.write("      if ($box.is(\":checked\")) {\n");
            writer.write("          var group = \"input:checkbox[name='\" + $box.attr(\"name\") + \"']\";\n");
            writer.write("          $(group).prop(\"checked\", false);\n");
            writer.write("          $box.prop(\"checked\", true);\n");
            writer.write("      } else {\n");
            writer.write("          $box.prop(\"checked\", false);\n");
            writer.write("      }\n");
            writer.write("  });\n");
            writer.write("  </script>\n");
            //writer.write("          $(this).val() // get the current value of the input field \n");
            writer.write("  <script> \n");
            writer.write("  $('#y').keyup(function() { \n");
            writer.write("      if (Math.random() % 1 == 0) { \n");
            writer.write("          ");
            writer.write("  });");
            writer.write("  </script>\n");
            writer.write("</div>\n");
            writer.write("</body>\n");
            writer.write("</html> \n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
