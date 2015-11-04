<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
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
                                        <h1>
                                            <img src="images/h_well.gif" width="69" height="29" border="0" alt="" /></h1>
                                        <img src="images/pic1.jpg" width="137" height="91" border="0" alt="" align="left"
                                            style="margin-right: 10px;" />
                                        <p>
                                            Welcome to Central Valley Utilities energy efficiency school! We offer a variety
                                            of energy efficiency classes for home owners and professional contractors. The goal
                                            of our classes is to promote green technologies that will hopefully stop and even
                                            reverse the threat of global warming. To sign up for a course, click the the New
                                            Students button. If you are a current student, enter your student ID number and
                                            click the Returning Students button to register for new classes or to review your
                                            current schedule.</p>
                                        <form id="returnStudent" runat="server">
                                        <asp:TextBox ID="studentID" runat="server" />
                                        &nbsp;<asp:Button ID="Button1" runat="server" Text="Returning Students" />&nbsp;<asp:Literal
                                            ID="validateMessage" runat="server" />&nbsp;<asp:RequiredFieldValidator ID="idValidator"
                                                runat="server" ErrorMessage="**You must enter your student ID**" ControlToValidate="studentID" />
                                        </form>
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
                    2010 © Copyright Central Valley Utilities. All rights reserved. Read Legal policy
                    and Privacy policy.</div>
            </div>
        </div>
    </div>
</body>
</html>
