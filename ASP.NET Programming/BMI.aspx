<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="header" runat="server">
    <title>BMI | Home Page</title>
    <style type="text/css">
        body
        {
            font-family: Lucida Console;
            background-color: #CCE0FF;
        }
        h1, h3
        {
            font-family: Elephant;
            color: #0066FF;
        }
    </style>
</head>
<body>
    <h1>
        Body Mass Index</h1>
    <p>
        Calculating BMI is one of the best methods for population assessment of overweight<br />
        and obesity. Because calculation requires only height and weight, it is inexpensive<br />
        and easy to use for clinicians and for the general public. The use of BMI allows<br />
        people to compare their own weight status to that of the general population. BMI<br />
        is calculated the same way for both adults and children.
    </p>
    
        <form id="bmi_form" runat="server">
        <b>
        <% int input_weight = 230;
           int input_height = 75;
           int BMI_calculation = (input_weight * 703) / (input_height * input_height);
           Response.Write("The given weight is: " + input_weight + " lbs <br />");
           Response.Write("The given height is: " + input_height + " inches <br />");
           Response.Write("The BMI of the values given are: " + BMI_calculation + "<br />");%>
               </b>
        </form>

    <br />
    <h3>
        BMI Categories:</h3>
    <br />
    Underweight = <18.5
    <br />
    Normal weight = 18.5–24.9
    <br />
    Overweight = 25–29.9
    <br />
    Obesity = BMI of 30 or greater
</body>
</html>
