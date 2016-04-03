<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lab 7 - Servlets</title>
    <link rel="stylesheet" type="text/css" href="../resources/css/default.css"/>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
    <style>
        .redBorder {
            border: 1px solid #ff0000;
        }
    </style>
</head>

<body>
<div id="wrap">
    <div id="header">
        <h3>
            Старался: Никита Шкаруба <br/>
            Группа: P3218 <br/>
            Вариант: 424
        </h3>
    </div>
    <div id="content">
        <img src="../resources/images/chart.jpg">
        <form method="get" action="WebForm" class="box">
            <div id="xes" class="inputs">
                <label>x: </label>
                <%
                    for (int i = -4; i <= 4; i++) {
                %>
                <label>
                    <input type="button" name="x" value="<%= i %>"/>
                    <%= i %>
                </label>
                <%
                    }
                %>
                <label id="xErrorMessage" style="color: red">Select x!</label>
            </div>
            <div id="ys">
                <label>
                    y:
                    <input id="dangerInput" type="text"/>
                </label>
                <label id="yErrorMessage" style="color: red">Input correct Numeric Y!</label>
            </div>
            <div id="rs">
                <label>r: </label>
                <%
                    for (int i = -4; i <= 4; i++) {
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
        </form>
    </div>
</div>
</body>

<script>
    // x change hanler
    $("input[name='x']").on('click', function () {
        if (!isXValid()) {
            $('#xErrorMessage').text("Select X!");
            $('#submit').attr('disabled', 'disabled');
        } else {
            $('#xErrorMessage').text("");

            if (validateAll() == true) {
                $('#submit').removeAttr('disabled');
            }
        }
    });
    // y change handler
    $('#dangerInput').on('change keyup paste inputc', function() {
        var value = $('#dangerInput').val();

        if (isNaN(value) || $.trim(value).length === 0) {
            $('#yErrorMessage').text("Input correct numeric Y!");

            $('#submit').attr('disabled', 'disabled');
        } else if (value < -3 || value > 3) {
            $('#yErrorMessage').text("Y is out of bounds {-3, 3}");

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
        var checkboxes = document.getElementsByName('x');

        for (var i = 0; i < checkboxes.length; i++) {
            if (checkboxes[i].checked) {
                return true;
            }
        }
        return false;
    }
    function isYValid() {
        var value = $('#dangerInput').val();

        return (!isNaN(value) && $.trim(value).length !== 0 && value >= -3 && value <= 3);
    }
    function isRValid() {
        return $('input[name="r"]:checked').val() != null;
    }

    function validateAll() {
        return isXValid() && isYValid() && isRValid();
    }
</script>
</html>
