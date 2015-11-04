using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    BankAccount checking = new BankAccount();
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void submit_click(Object sender, EventArgs e)
    {
        try
        {
            current_balance.Text = setbalance_amount.Text;
            decimal balance = Convert.ToDecimal(current_balance.Text);
            current_balance.Text = Convert.ToString(Math.Round(balance, 2));

            if (balance > 0)
            {

                setbalance_label.Visible = false;
                setbalance_amount.Visible = false;
                setbalance_button.Visible = false;
                deposit_amount.Visible = true;
                deposit_label.Visible = true;
                deposit_button.Visible = true;
                withdraw_amount.Visible = true;
                withdraw_label.Visible = true;
                withdraw_button.Visible = true;
                interest_button.Visible = true;
                interest_amount.Visible = true;
                interest_label.Visible = true;
            }
            else
            {

                setbalance_amount.Text = "Cannot have negative or 0 balance";
            }

        }
        catch (Exception)
        {
            current_balance.Text = "0";
            setbalance_amount.Text = "Invalid, Enter X.XX";
        }



    }
    protected void deposit_click(Object sender, EventArgs e)
    {
        try
        {
            decimal balance = Convert.ToDecimal(current_balance.Text);
            decimal adjustment = Convert.ToDecimal(deposit_amount.Text);

            current_balance.Text = Convert.ToString(Math.Round(checking.deposit(balance, adjustment), 2));
            deposit_amount.Text = "";
            interest_amount.Text = "";
            withdraw_amount.Text = "";
        }
        catch (Exception)
        {
            deposit_amount.Text = "Entry invalid, please try again";
            interest_amount.Text = "";
            withdraw_amount.Text = "";
        }

    }
    protected void withdraw_click(Object sender, EventArgs e)
    {
        try
        {
            decimal balance = Convert.ToDecimal(current_balance.Text);
            decimal adjustment = Convert.ToDecimal(withdraw_amount.Text);

            if (balance >= adjustment)
            {
                current_balance.Text = Convert.ToString(Math.Round(checking.withdraw(balance, adjustment), 2));
                deposit_amount.Text = "";
                interest_amount.Text = "";
                withdraw_amount.Text = "";
            }
            else
            {
                withdraw_amount.Text = "You cannot overdraw";
            }
        }
        catch (Exception)
        {
            withdraw_amount.Text = "Entry invalid, please try again";
            deposit_amount.Text = "";
            interest_amount.Text = "";
        }
    }
    protected void interest_click(Object sender, EventArgs e)
    {

        try
        {


            decimal balance = Convert.ToDecimal(current_balance.Text);
            decimal adjustment = Convert.ToDecimal(interest_amount.Text);
            current_balance.Text = Convert.ToString(Math.Round(checking.interest(balance, adjustment), 2));
            deposit_amount.Text = "";
            interest_amount.Text = "";
            withdraw_amount.Text = "";
        }
        catch (Exception)
        {
            interest_amount.Text = "Entry invalid, please try again";
            withdraw_amount.Text = "";
            deposit_amount.Text = "";
        }
    }
}


public class BankAccount : System.Web.UI.Page
{
    public decimal withdraw(decimal balance, decimal withdrawl)
    {
        balance= balance - withdrawl;
        return balance;
    }
    public decimal interest(decimal balance, decimal interest)
    {
        balance= balance + (balance * (interest / 100));
        return balance;
    }
    public decimal deposit(decimal balance, decimal deposit)
    {
        balance= balance + deposit;
        return balance;
    }
    
}
