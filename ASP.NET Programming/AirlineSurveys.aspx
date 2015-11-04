<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>American Air | Survey</title>
     <style type="text/css">
        body
        {
            font-family: Lucida Console;
            background-color: #CCE0FF;
        }
        h1, h3
        {
            font-family: Elephant;
            color: red;
        }
    </style>
</head>
<body>
   <form id="form1" runat="server">
    <center>
        <h1>
            American Air Experience Survey
        </h1>
        <asp:Label ID="thank_you" Visible="false" runat="server" Text="Thank you for participating in this brief survey!"></asp:Label>
        <asp:Label ID="dateLabel" runat="server" Text="Your Flight Date:"></asp:Label>
        <asp:DropDownList ID="month" runat="server">
            <asp:ListItem>January</asp:ListItem>
            <asp:ListItem>February</asp:ListItem>
            <asp:ListItem>March</asp:ListItem>
            <asp:ListItem>April</asp:ListItem>
            <asp:ListItem>May</asp:ListItem>
            <asp:ListItem>June</asp:ListItem>
            <asp:ListItem>July</asp:ListItem>
            <asp:ListItem>August</asp:ListItem>
            <asp:ListItem>September</asp:ListItem>
            <asp:ListItem>October</asp:ListItem>
            <asp:ListItem>November</asp:ListItem>
            <asp:ListItem>December</asp:ListItem>
        </asp:DropDownList>
        <asp:DropDownList ID="day" runat="server">
            <asp:ListItem>1</asp:ListItem>
            <asp:ListItem>2</asp:ListItem>
            <asp:ListItem>3</asp:ListItem>
            <asp:ListItem>4</asp:ListItem>
            <asp:ListItem>5</asp:ListItem>
            <asp:ListItem>6</asp:ListItem>
            <asp:ListItem>7</asp:ListItem>
            <asp:ListItem>8</asp:ListItem>
            <asp:ListItem>9</asp:ListItem>
            <asp:ListItem>10</asp:ListItem>
            <asp:ListItem>11</asp:ListItem>
            <asp:ListItem>12</asp:ListItem>
            <asp:ListItem>13</asp:ListItem>
            <asp:ListItem>14</asp:ListItem>
            <asp:ListItem>15</asp:ListItem>
            <asp:ListItem>16</asp:ListItem>
            <asp:ListItem>17</asp:ListItem>
            <asp:ListItem>18</asp:ListItem>
            <asp:ListItem>19</asp:ListItem>
            <asp:ListItem>20</asp:ListItem>
            <asp:ListItem>21</asp:ListItem>
            <asp:ListItem>22</asp:ListItem>
            <asp:ListItem>23</asp:ListItem>
            <asp:ListItem>24</asp:ListItem>
            <asp:ListItem>25</asp:ListItem>
            <asp:ListItem>26</asp:ListItem>
            <asp:ListItem>27</asp:ListItem>
            <asp:ListItem>28</asp:ListItem>
            <asp:ListItem>29</asp:ListItem>
            <asp:ListItem>30</asp:ListItem>
            <asp:ListItem>31</asp:ListItem>
        </asp:DropDownList>
        <asp:DropDownList ID="year" runat="server">
            <asp:ListItem>2012</asp:ListItem>
            <asp:ListItem>2013</asp:ListItem>
            <asp:ListItem>2014</asp:ListItem>
        </asp:DropDownList>
        <br />
        <br />
        <asp:Label ID="time_label" runat="server" Text="Your Flight Time:"></asp:Label>
        <asp:DropDownList ID="hour" runat="server">
            <asp:ListItem>1</asp:ListItem>
            <asp:ListItem>2</asp:ListItem>
            <asp:ListItem>3</asp:ListItem>
            <asp:ListItem>4</asp:ListItem>
            <asp:ListItem>5</asp:ListItem>
            <asp:ListItem>6</asp:ListItem>
            <asp:ListItem>7</asp:ListItem>
            <asp:ListItem>8</asp:ListItem>
            <asp:ListItem>9</asp:ListItem>
            <asp:ListItem>10</asp:ListItem>
            <asp:ListItem>11</asp:ListItem>
            <asp:ListItem>12</asp:ListItem>
        </asp:DropDownList>
        <asp:DropDownList ID="minute" runat="server">
            <asp:ListItem>00</asp:ListItem>
            <asp:ListItem>05</asp:ListItem>
            <asp:ListItem>10</asp:ListItem>
            <asp:ListItem>15</asp:ListItem>
            <asp:ListItem>20</asp:ListItem>
            <asp:ListItem>25</asp:ListItem>
            <asp:ListItem>30</asp:ListItem>
            <asp:ListItem>35</asp:ListItem>
            <asp:ListItem>40</asp:ListItem>
            <asp:ListItem>45</asp:ListItem>
            <asp:ListItem>50</asp:ListItem>
            <asp:ListItem>55</asp:ListItem>
        </asp:DropDownList>
        <asp:DropDownList ID="am_pm" runat="server">
            <asp:ListItem>AM</asp:ListItem>
            <asp:ListItem>PM</asp:ListItem>
        </asp:DropDownList>
        <br />
        <br />
                <asp:Label ID="flightLabel" runat="server" Text="Your Flight Number:"></asp:Label>
        <asp:TextBox ID="flightNumber" Width="50" runat="server"></asp:TextBox>
        <br />
        <br />
        <asp:Label ID="question1" runat="server" Text="Friendliness of customer staff"></asp:Label>
        <asp:RadioButtonList ID="question1list" runat="server" 
            onselectedindexchanged="question1list_SelectedIndexChanged">
            <asp:ListItem>No Opinion</asp:ListItem>
            <asp:ListItem>Poor</asp:ListItem>
            <asp:ListItem>Fair</asp:ListItem>
            <asp:ListItem>Good</asp:ListItem>
            <asp:ListItem>Excellent</asp:ListItem>
        </asp:RadioButtonList>
        <br />
        <asp:Label ID="question2" runat="server" Text="Space for luggage storage"></asp:Label>
        <asp:RadioButtonList ID="question2list" runat="server">
            <asp:ListItem>No Opinion</asp:ListItem>
            <asp:ListItem>Poor</asp:ListItem>
            <asp:ListItem>Fair</asp:ListItem>
            <asp:ListItem>Good</asp:ListItem>
            <asp:ListItem>Excellent</asp:ListItem>
        </asp:RadioButtonList>
        <br />
        <asp:Label ID="question3" runat="server" Text="Comfort of seating"></asp:Label>
        <asp:RadioButtonList ID="question3list" runat="server">
            <asp:ListItem>No Opinion</asp:ListItem>
            <asp:ListItem>Poor</asp:ListItem>
            <asp:ListItem>Fair</asp:ListItem>
            <asp:ListItem>Good</asp:ListItem>
            <asp:ListItem>Excellent</asp:ListItem>
        </asp:RadioButtonList>
        <br />
        <asp:Label ID="question4" runat="server" Text="Cleanliness of aircraft"></asp:Label>
        <asp:RadioButtonList ID="question4list" runat="server">
            <asp:ListItem>No Opinion</asp:ListItem>
            <asp:ListItem>Poor</asp:ListItem>
            <asp:ListItem>Fair</asp:ListItem>
            <asp:ListItem>Good</asp:ListItem>
            <asp:ListItem>Excellent</asp:ListItem>
        </asp:RadioButtonList>
        <br />
        <asp:Label ID="question5" runat="server" Text="Noise level of aircraft"></asp:Label>
        <asp:RadioButtonList ID="question5list" runat="server">
            <asp:ListItem>No Opinion</asp:ListItem>
            <asp:ListItem>Poor</asp:ListItem>
            <asp:ListItem>Fair</asp:ListItem>
            <asp:ListItem>Good</asp:ListItem>
            <asp:ListItem>Excellent</asp:ListItem>
        </asp:RadioButtonList>
        <asp:Button ID="submit_button" runat="server" Text="Submit" OnClick="submit_click" /><br />
      
    </center>
    </form>
</body>
</html>
