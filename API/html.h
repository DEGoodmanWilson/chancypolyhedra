//
// Created by Don Goodman-Wilson on 11/06/2017.
//

#pragma once

namespace dice
{

const std::string index{R"(
<html>
<head>
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css"
          integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
    <!-- Optional theme -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css"
          integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">

    <title>Chancy Polyhedra</title>

</head>

<body>

<div class="container">
    <div class="row">
        <div class="col-xs-12 col-md-6 col-md-offset-3">

            <div class="jumbotron">
                <h1>Chancy Polyhedra</h1>
                <p class="lead">
                    Roll 2d6 for awesomeness.
                </p>
            </div>

            <div class="input-group">
                <input type="text" class="form-control" id="diceexpr" placeholder="Roll the dice...">
                <span class="input-group-btn">
                    <button class="btn btn-default" id="dice" type="button">Go!</button>
                </span>
            </div><!-- /input-group -->
            <h2>Result: <span id="diceresult">(nothing yet…)</span></h2>
        </div>
    </div>
</div>

<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
<!-- Include all compiled plugins (below), or include individual files as needed -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>


<script>
    $(document).ready(function () {
        $('#dice').on('click', function (e) {
//            TODO this should not be a hard-coded domain
            $.get("http://chancypolyhedra.now.sh/v1/" + $('#diceexpr').val(), function(data, status){
                res = $.parseJSON(data);
                $('#diceresult').text(res['result']);
            });
        });
    });
</script>
</body>
</html>
)"};

} //namespace dice