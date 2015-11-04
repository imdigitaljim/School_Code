<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Guessing Game</title>
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
    <form id="guessform" runat="server">
    <center>
        <h1>
            Guessing Game!</h1>
        <asp:Label ID="display_word" runat="server" Text="test"></asp:Label><br />
        <asp:Label ID="tip" Text="Enter a letter" runat="server"></asp:Label><br />
        <asp:TextBox ID="input_guess" runat="server" Text="" /><br />
        <asp:Button ID="button" runat="server" Text="Guess" OnClick="guess_click" /><br />
        <asp:Label ID="chosen_word" runat="server" Visible="false" Text=""></asp:Label>
        <asp:Label ID="win_Condition" runat="server" Visible="false" Text="You found the word!"></asp:Label>
    </center>
    </form>
</body>
</html>
