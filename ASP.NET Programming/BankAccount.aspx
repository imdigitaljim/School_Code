<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
      <h1> $<asp:Label ID="current_balance" runat="server" Text="0" /></h1>
        <asp:Label ID="setbalance_label" runat="server" Text="Enter Starting Balance"></asp:Label><br />
        <asp:TextBox ID="setbalance_amount" runat="server"></asp:TextBox>
        <asp:Button ID="setbalance_button" runat="server" OnClick="submit_click" Text="Button" ></asp:Button>
        
        <asp:Label ID="deposit_label" runat="server" Text="Deposit Amount" Visible="false"></asp:Label><br />
        <asp:TextBox ID="deposit_amount" runat="server" Visible="false"></asp:TextBox>
        <asp:Button ID="deposit_button" runat="server" Text="Deposit" OnClick="deposit_click" Visible="false"></asp:Button> <br />
        <asp:Label ID="withdraw_label" runat="server" Text="Withdraw Amount" Visible="false"></asp:Label><br />
        <asp:TextBox ID="withdraw_amount" runat="server" Visible="false"></asp:TextBox>
        <asp:Button ID="withdraw_button" runat="server" Text="Withdraw" OnClick="withdraw_click" Visible="false" ></asp:Button><br />
        <asp:Label ID="interest_label" runat="server" Text="Interest Percentage" Visible="false"></asp:Label><br />
        <asp:TextBox ID="interest_amount" runat="server" Visible="false"></asp:TextBox>
        <asp:Button ID="interest_button" runat="server" Text="Apply Interest" OnClick="interest_click" Visible="false"></asp:Button><br />
    </div>
    </form>
</body>
</html>
