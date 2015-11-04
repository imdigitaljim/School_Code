<%@ Page Language="C#" AutoEventWireup="true" CodeFile="NewStudent.aspx.cs"
    Inherits="NewStudent" %>

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
                                                New Student Registration</h1>
                                            <form id="registrationForm" runat="server">
                                            <p>
                                                Last name&nbsp;<asp:RequiredFieldValidator ID="lastNameValidate" runat="server" ControlToValidate="lastName"
                                                    Text="**Required field**" /><br />
                                                <asp:TextBox ID="lastName" runat="server" Width="265" /><br />
                                                First name&nbsp;<asp:RequiredFieldValidator ID="firstNameValidate" runat="server"
                                                    ControlToValidate="firstName" Text="**Required field**" /><br />
                                                <asp:TextBox ID="firstName" runat="server" Width="265" /><br />
                                                Telephone&nbsp;<asp:RequiredFieldValidator ID="telephoneValidate" runat="server"
                                                    ControlToValidate="telephone" Text="**Required field**" Display="Dynamic" /><asp:RegularExpressionValidator
                                                        ID="RegularExpressionValidator3" runat="server" ErrorMessage="**Invalid phone number**"
                                                        ValidationExpression="^(1 )?(\([0-9]{3}\) )?([1-9]{3}(\-[1-9]{4})$)" ControlToValidate="telephone" /><br />
                                                <asp:TextBox ID="telephone" runat="server" Width="265" /><br />
                                                E-mail&nbsp;<asp:RequiredFieldValidator ID="emailValidate" runat="server" ControlToValidate="email"
                                                    Text="**Required field**" Display="Dynamic" /><asp:RegularExpressionValidator ID="RegularExpressionValidator1"
                                                        runat="server" ErrorMessage="**Invalid e-mail address**" ControlToValidate="email"
                                                        ValidationExpression="^[_\w\-]+(\.[_\w\-]+)*@[\w\-]+(\.[\w\-]+)*(\.[\D]{2,3})$" /><br />
                                                <asp:TextBox ID="email" runat="server" Width="265" /><br />
                                                Confirm e-mail&nbsp;<asp:RequiredFieldValidator ID="confirmEmailValidate" runat="server"
                                                    ControlToValidate="confirmEmail" Text="**Required field**" Display="Dynamic" /><asp:RegularExpressionValidator
                                                        ID="RegularExpressionValidator2" runat="server" ErrorMessage="**Invalid e-mail address**"
                                                        ControlToValidate="confirmEmail" ValidationExpression="^[_\w\-]+(\.[_\w\-]+)*@[\w\-]+(\.[\w\-]+)*(\.[\D]{2,3})$" /><br />
                                                <asp:TextBox ID="confirmEmail" runat="server" Width="265" /><br />
                                                <asp:CompareValidator ID="compareEmail" runat="server" ControlToValidate="confirmEmail"
                                                    Operator="Equal" Display="Dynamic" ControlToCompare="email">**You did not enter the same value in the e-mail and e-mail confirmation fields**<br /></asp:CompareValidator></p>
                                            <p>
                                                <asp:Button ID="getStudentID" runat="server" Text="Get Student ID" /></p>
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
