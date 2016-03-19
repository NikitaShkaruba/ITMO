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
            writer.write("" +
            "<!DOCTYPE html> \n" +
            "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\n " +
            "<head> \n" +
            "  <meta charset=\"UTF-8\">\n " +
            "  <title>Lab 7 - Servlets</title>\n" +
            "  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js\"></script> \n" +
            "  <style>\n" +
            "      .redBorder {\n" +
            "          border: 1px solid #ff0000\n" +
            "      }\n" +
            "  </style>\n" +
            "</head>\n" +
            "\n" +
            "<body>\n" +
            "<div id=\"wrap\">\n" +
            "   <div id=\"header\">\n" +
            "       <h3>\n" +
            "           Старался: Никита Шкаруба <br/>\n" +
            "           Группа: P3218 <br/>\n" +
            "           Вариант: 424\n" +
            "       </h3>\n" +
            "   </div>\n" +
            "   <div id=\"content\">\n" +
            "\n" +
            "       <!-- Xes -->\n" +
            "       <form method=\"get\" action=\"\">\n" +
            "           <div id=\"xes\" class=\"inputs\">\n" +
            "               <label>x: </label>\n");
            for (int i = -3; i < 5; i++) {
                writer.write("               <label>\n" +
                "                 <input type=\"radio\" name=\"x\" value=\"" + i + "\" /> \n" +
                "                 " + i + "\n" +
                "               </label> \n");
            }
            writer.write("" +
            "           <label id=\"xErrorMessage\" style=\"color: red\">Select x!</label>\n" +
            "           </div>\n" +
            "\n" +
            "           <!-- Y -->\n" +
            "           <div id=\"ys\">\n" +
            "               <label>\n" +
            "                   y:\n" +
            "                   <input id=\"y\" name=\"y\" type=\"text\"/>\n" +
            "               </label>\n" +
            "               <label id=\"yErrorMessage\" style=\"color: red\">Input correct numeric Y!</label>\n" +
            "           </div>\n" +
            "\n" +
            "           <!-- Rs -->\n" +
            "           <div id=\"rs\">\n" +
            "               <label>r: </label>\n");
            for (double i = 1; i <= 3; i += 0.5) {
                writer.write("" +
                "                  <label>\n" +
                "                  <input type=\"checkbox\" name=\"r\" value=\"" + i + "\" />\n" +
                "                  " + i + "\n" +
                "              </label>\n");
            }
            writer.write("" +
            "               <label id=\"rErrorMessage\" style=\"color: red\">Select r!</label>\n" +
            "           </div>\n" +
            "\n" +
            "            <input id=\"submit\" type=\"submit\" disabled=\"true\" value=\"Проверить точку\">\n" +
            "       </form>\n" +
            "   </div>\n" +
            "</div>\n" +
            "</body>\n" +
            "\n" +
            "<script>\n" +
            "// x validator \n" +
            "$(\"input[name='x']\").on('click', function () { \n" +
            "   if (!isXSelected()) { \n" +
            "       $('#xErrorMessage').text(\"Select X!\"); \n" +
            "       $('#submit').attr('disabled', 'disabled'); \n" +
            "   } else { \n" +
            "       $('#xErrorMessage').text(\"\"); \n" +
            "       if (validateAll() == true) { \n" +
            "           $('#submit').removeAttr('disabled'); \n" +
            "       } \n" +
            "   } \n" +
            "}); \n" +
            "// y validator \n" +
            "$('#y').on('change keyup paste inputc', function() { \n" +
            "   var value = $('#y').val(); \n" +
            "   if (isNaN(value) || $.trim(value).length === 0) { \n" +
            "       $('#yErrorMessage').text(\"Input correct numeric Y!\"); \n" +
            "       $('#submit').attr('disabled', 'disabled'); \n" +
            "   } else if (value < -3 || value > 3) { \n" +
            "       $('#yErrorMessage').text(\"Y is out of bounds {-3, 3}\"); \n" +
            "       $('#submit').attr('disabled', 'disabled'); \n" +
            "   } else { \n" +
            "       $('#yErrorMessage').text(\"\"); \n" +
            "       if (validateAll() == true) \n" +
            "           $('#submit').removeAttr('disabled'); \n" +
            "   } \n" +
            "}); \n" +
            "// r validator \n" +
            "$(\"input[name*='r']\").on('click', function () { \n" +
            "   var $box = $(this); \n" +
            "   if ($box.is(\":checked\")) { \n" +
            "       var group = \"input:checkbox[name='\" + $box.attr(\"name\") + \"']\"; \n" +
            "       $(group).prop(\"checked\", false); \n" +
            "       $box.prop(\"checked\", true); \n" +
            "       $('#rErrorMessage').text(\"\"); \n" +
            "       if (validateAll() == true) \n" +
            "           $('#submit').removeAttr('disabled'); \n" +
            "   } else { \n" +
            "       $box.prop(\"checked\", false); \n" +
            "       $('#rErrorMessage').text(\"Select R!\"); \n" +
            "       $('#submit').attr('disabled', 'disabled'); \n" +
            "   } \n" +
            "}); \n\n" +
            "function isXSelected() { \n" +
            "   var chx = document.getElementsByName('x'); \n" +
            "   for (var i = 0; i < chx.length; i++) { \n" +
            "       if (chx[i].checked) { \n" +
            "           return true; \n" +
            "       } \n" +
            "   } \n" +
            "   return false; \n" +
            "} \n" +
            "function isYValid() { \n" +
            "   var value = $('#y').val();  \n" +
            "   return (!isNaN(value) && $.trim(value).length !== 0 && value >= -3 && value <= 3);\n" +
            "} \n" +
            "function isRSelected() {\n" +
            "   return $('input[name=\"r\"]:checked').val() != null;\n" +
            "}\n\n" +
            "function validateAll() {\n" +
            "   return isXSelected() && isYValid() && isRSelected(); \n" +
            "}\n" +
            "</script>\n" +
            "</html> \n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
