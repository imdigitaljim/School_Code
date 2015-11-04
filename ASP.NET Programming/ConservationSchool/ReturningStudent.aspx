<%@ Page Language="C#" AutoEventWireup="true" CodeFile="ReturningStudent.aspx.cs"
    Inherits="ReturningStudent" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=windows-1251" />
    <link href="conservation.css" type="text/css" rel="stylesheet" />
    <title>Central Valley Utilities</title>
</head>
<body>
    <div id="page">
        <div id="top">
            <div id="menu">
                <a href="Default.aspx" id="b1"></a><a href="NewStudent.aspx" id="b3"></a><a href="ReturningStudent.aspx"
                    id="b4"></a>
            </div>
        </div>
        <div id="l">
        </div>
        <div style="background: url(images/l.gif) repeat-y 0px 0px;">
            <div style="background: url(images/lt.gif) no-repeat 0px 0px;">
                <div style="background: url(images/lb.gif) no-repeat 0px 100%; padding-left: 50px;">
                    <div style="background: url(images/r.gif) repeat-y 100% 0px;">
                        <div style="background: url(images/rt.gif) no-repeat 100% 0px;">
                            <div style="background: url(images/rb.gif) no-repeat 100% 100%; padding-right: 50px;">
                                <div id="c">
                                    <div style="padding: 30px;">
                                        <div id="col_l">
                                            <h1>
                                                Class Registration</h1>
                                            <form id="registrationForm" runat="server">
                                            <asp:Literal ID="curID" runat="server" />
                                            <p>
                                                <strong>Select the class you would like to take:</strong><br />
                                                <p>
                                                    <asp:RadioButtonList ID="className" runat="server">
                                                        <asp:ListItem Value="Solar Power Basics" Selected="True">Solar Power Basics</asp:ListItem>
                                                        <asp:ListItem Value="Green Construction Techniques">Green Construction Techniques</asp:ListItem>
                                                        <asp:ListItem Value="Commercial Energy Management">Commercial Energy Management</asp:ListItem>
                                                        <asp:ListItem Value="Creating a Green Office">Creating a Green Office</asp:ListItem>
                                                        <asp:ListItem Value="Residential Energy Management">Residential Energy Management</asp:ListItem>
                                                    </asp:RadioButtonList>
                                                </p>
                                                <p>
                                                    <strong>Available Days and Times:</strong><br />
                                                    <asp:ListBox ID="days" runat="server" Rows="1">
                                                        <asp:ListItem Selected="True">Mondays and Wednesdays</asp:ListItem>
                                                        <asp:ListItem>Tuesdays and Thursdays</asp:ListItem>
                                                        <asp:ListItem>Wednesdays and Fridays</asp:ListItem>
                                                    </asp:ListBox>
                                                    <asp:ListBox ID="time" runat="server" Rows="1">
                                                        <asp:ListItem Selected="True">9 a.m. - 11 a.m.</asp:ListItem>
                                                        <asp:ListItem>1 p.m. - 3 p.m.</asp:ListItem>
                                                        <asp:ListItem>6 p.m. - 8 p.m.</asp:ListItem>
                                                    </asp:ListBox>
                                                    <p>
                                                        <asp:Button ID="register" runat="server" Text="Register" /></p>
                                            </form>
                                            <asp:Literal ID="regMessage" runat="server" Visible="False" /><div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div id="f">
            <div id="fl">
                <div id="fr">
                    2010 © Copyright Central Valley Utilities. All rights reserved.</div>
            </div>
        </div>
    </div>
</body>
</html>
