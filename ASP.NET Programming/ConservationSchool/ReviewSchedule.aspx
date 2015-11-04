<%@ Page Language="C#" AutoEventWireup="true" CodeFile="ReviewSchedule.aspx.cs" Inherits="ReviewSchedule" %>

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
                                                Current Schedule</h1>
                                            <form id="scheduleForm" runat="server">
                                            <asp:Literal ID="schedule" runat="server" />
                                            </form>
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
