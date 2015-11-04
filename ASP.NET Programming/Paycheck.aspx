<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link href="Pay.css" rel="stylesheet" type="text/css" />
    <title>Paycheck | Results</title>
</head>
<body>
    <div class="paybordr bodystyle">
        <center>
            <h2>
                Your Weekly Income:</h2>
            <br />
            <% try
               {
                   payroll();
               }
               catch
               {
                   errorsreturn();
               }         
            %>
            <script runat="server">
        
    
                void payroll()
                {
                    double payhours = Convert.ToDouble(Request.QueryString["hours"]);
                    double paywage = Convert.ToDouble(Request.QueryString["wage"]);
                    Response.Write("You entered " + payhours + " hours and $" + paywage + " per hour <br /><br />");
                    Response.Write("Your gross earnings are $" + payvalue(payhours, paywage));

                }

                string payvalue(double hours, double wage)
                {
                    double pay;
                    double overtimeearnings;
                    double overtimehours;
                    string payreturn;
                    if (hours > 40)
                    {
                        overtimehours = hours - 40;
                        hours = 40;
                        overtimeearnings = overtimehours * wage * 1.5;
                        pay = hours * wage + overtimeearnings;
                    }
                    else { pay = hours * wage; }

                    payreturn = Convert.ToString(pay);
                    return payreturn;
                }
                void errorsreturn()
                {
                    Response.Write("You have entered incorrect info. <br /> Please go back try again.");
                }  
            </script>
            <br />
            <br />
            <br />
        </center>
    </div>
</body>
</html>
