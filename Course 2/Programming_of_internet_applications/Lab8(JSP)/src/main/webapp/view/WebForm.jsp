<%@ page pageEncoding="UTF-8" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.Date" %>
<%@ page import="javafx.util.Pair" %>
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lab 7 - Servlets</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
</head>

<body>
<div id="wrap">
    <div id="header">
        <h3>
            Старался: Никита Шкаруба <br/>
            Группа: P3218 <br/>
            Вариант: 989
        </h3>
    </div>
    <div id="content">
        <img id="chart" borer="2" src="<%= request.getContextPath() %>/resources/images/Chart.png" />

        <br/>

        <fieldset>
            <legend>Interface:</legend>
            <form method="get" action="WebForm" class="box">
                <div id="xes" class="inputs">
                    <label>x: </label>
                    <%
                        for (int i = -4; i <= 4; i++) {
                    %>
                    <label>
                        <input type="button" name="x" value="<%= i %>"/>
                    </label>
                    <%
                        }
                    %>

                    <label id="xErrorMessage" style="color: red">Select x!</label>
                    <input id="hiddenX" type='hidden' name='x' value="sht" />
                </div>

                <div id="ys">
                    <label>
                        y:
                        <input id="dangerInput" name="y" type="text"/>
                    </label>
                    <label id="yErrorMessage" style="color: red">Input correct Numeric Y!</label>
                </div>

                <div id="rs">
                    <label>r: </label>
                    <%
                        for (float i = 1; i <= 3; i += 0.5) {
                    %>
                    <label>
                        <input type="checkbox" name="r" value="<%= i %>"/>
                        <%= i %>
                    </label>
                    <%
                        }
                    %>
                    <label id="rErrorMessage" style="color: red">Select R!</label>
                </div>

                <input id="submit" type="submit" disabled="true" value="Проверить точку">
                <label>Также, релизовано простое нажатие мышью на график, при условии, что установлен Радиус{r}</label>
            </form>
        </fieldset>

        <h3>История:</h3>
        <ul>
            <% for(Pair<Date, Boolean> isHit: (ArrayList<Pair<Date, Boolean>>)application.getAttribute("HitHistoryList")) { %>
                    <li><b><%= (isHit.getValue()? "Попадание" : "Промах")%></b> <%= " - " + isHit.getKey().toString() %></li>
            <% } %>
        </ul>
    </div>
</div>
</body>

<script>
    // Mouse point picker
    var chart = document.getElementById("chart");
    chart.onmousedown = tryRedirect;

    function FindPosition(oElement) {
        for(var posX = 0, posY = 0; oElement; oElement = oElement.offsetParent) {
            posX += oElement.offsetLeft;
            posY += oElement.offsetTop;
        }
        return [ posX, posY ];
    }

    function tryRedirect(e) {
        var ImgPos = FindPosition(chart);
        var r =$('input[name="r"]:checked').val();

        var x = (e.pageX - ImgPos[0] - chart.clientWidth/2);    // pixels count
        x = x / (chart.clientWidth / 2);                        // pixels / axis width
        x = x * 1.28 * r;                                       // relative to R
        var y = -(e.pageY - ImgPos[1] - chart.clientHeight/2);
        y = y / (chart.clientHeight / 2);
        y = y * 1.35 * r;

        if (isRValid())
            window.location = "/Lab8/WebForm?x=" + x + "&y=" + y + "&r=" + r ;
        else
            alert("Не могу выполнить запрос, т.к. r не выбран.")
    }

    // x change handler
    $("input[name='x']").on('click', function () {
        var xes = $("input[name='x']");

        // Paint everything
        for (var i = 0; i < xes.size(); i++) {
            if (xes[i] != this)
                xes[i].style.background = '#dddddd';
            else
                xes[i].style.background = '#008800';
        }

        $('#xErrorMessage').text("");
        document.getElementById("hiddenX").value = this.value;

        if (validateAll() == true) {
            $('#submit').removeAttr('disabled');
        }
    });
    // y change handler
    $('#dangerInput').on('change keyup paste inputc', function() {
        var value = $('#dangerInput').val();

        if (isNaN(value) || $.trim(value).length === 0) {
            $('#yErrorMessage').text("Input correct numeric Y!");

            $('#submit').attr('disabled', 'disabled');
        } else if (value < -5 || value > 3) {
            $('#yErrorMessage').text("Y is out of bounds {-5, 3}");

            $('#submit').attr('disabled', 'disabled');
        } else {
            $('#yErrorMessage').text("");

            if (validateAll() == true)
                $('#submit').removeAttr('disabled');
        }
    });
    // r change handler
    $("input[name*='r']").on('click', function () {
        var $box = $(this);

        if ($box.is(":checked")) {
            var group = "input:checkbox[name='" + $box.attr("name") + "']";
            $(group).prop("checked", false);
            $box.prop("checked", true);
            $('#rErrorMessage').text("");

            if (validateAll() == true)
                $('#submit').removeAttr('disabled');
        } else {
            $box.prop("checked", false);
            $('#rErrorMessage').text("Select R!");
            $('#submit').attr('disabled', 'disabled');
        }
    });

    function isXValid() {
        var xes = $("input[name='x']");

        for (var i = 0; i < xes.size(); i++)
            if (xes[i].style.background == "rgb(0, 136, 0)")
                return true;

        return false;
    }
    function isYValid() {
        var value = $('#dangerInput').val();

        return (!isNaN(value) && $.trim(value).length !== 0 && value >= -5 && value <= 3);
    }
    function isRValid() {
        return $('input[name="r"]:checked').val() != null;
    }

    function validateAll() {
        return isXValid() && isYValid() && isRValid();
    }
</script>
</html>
