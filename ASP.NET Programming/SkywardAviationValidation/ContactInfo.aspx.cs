using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["flyerID"] == null)
            Response.Redirect("Login.aspx");
        if (profileForm.ActiveStep.StepType
           == WizardStepType.Start)
            hiddenPassword.Value = password.Text;
        SqlConnection dbConnection = new SqlConnection("Data Source=.\\SQLEXPRESS;AttachDbFilename=C:\\DonsData\\Course Technology\\0324-2\\Chapter.09\\Chapter\\SkywardAviation\\App_Data\\SkywardAviation.mdf;Integrated Security=True;User Instance=True");
        dbConnection.Open();
        try
        {
            SqlCommand sqlCommand = new SqlCommand("SELECT * FROM FrequentFlyers WHERE flyerID = " + Session["flyerID"], dbConnection);
            SqlDataReader userInfo = sqlCommand.ExecuteReader();
            if (userInfo.Read())
            {
                firstName.Text = userInfo["first"].ToString();
                lastName.Text = userInfo["last"].ToString();
                telephone.Text = userInfo["phone"].ToString();
                email.Text = userInfo["email"].ToString();
                confirmEmail.Text = userInfo["email"].ToString();
                creditcard.Text = userInfo["cardType"].ToString();
                expireMonth.Text = userInfo["expireMonth"].ToString();
                expireYear.Text = userInfo["expireYear"].ToString();
                cardnumber.Text = userInfo["cardNumber"].ToString();
                cardholder.Text = userInfo["cardholder"].ToString();
                address.Text = userInfo["address"].ToString();
                city.Text = userInfo["city"].ToString();
                state.Text = userInfo["state"].ToString();
                zip.Text = userInfo["zip"].ToString();
                travelerType.Text = userInfo["travelerType"].ToString();
                homeAirport.Text = userInfo["homeAirport"].ToString();
                serviceClass.Text = userInfo["class"].ToString();
                seatPreference.Text = userInfo["seat"].ToString();
                mealRequest.Text = userInfo["meal"].ToString();
                updateOK.Text = "<p>Account successfully updated.</p><p><a href='ffClubPage.aspx'>Account Profile page</a></p>";
            }
            else
            {
                profileForm.Visible = false;
                updateErrors.Text = "<p>Invalid frequent flyer number!</p>";
            }
            userInfo.Close();
        }
        catch (SqlException exception)
        {
            Response.Write("<p>Error code " + exception.Number
                + ": " + exception.Message + "</p>");
        }
        dbConnection.Close();
    }
    protected void Page_LoadComplete(object sender, EventArgs e)
    {
        if (profileForm.ActiveStep.StepType
            == WizardStepType.Complete)
        {
            SqlConnection dbConnection = new SqlConnection("Data Source=.\\SQLEXPRESS;AttachDbFilename=C:\\DonsData\\Course Technology\\0324-2\\Chapter.09\\Chapter\\SkywardAviation\\App_Data\\SkywardAviation.mdf;Integrated Security=True; User Instance=True");
            try
            {
                dbConnection.Open();
                SqlCommand sqlCommand = new SqlCommand(
                    "UPDATE FrequentFlyers SET "
                    + "last= '" + lastName.Text + "',"
                    + "first ='" + firstName.Text + "',"
                    + "phone ='" + telephone.Text + "',"
                    + "email='" + email.Text + "',"
                    + "password='" + hiddenPassword.Value + "',"
                    + "cardtype='" + creditcard.Text + "',"
                    + "expireMonth ='" + expireMonth.Text + "',"
                    + "expireYear ='" + expireYear.Text + "',"
                    + "cardnumber ='" + cardnumber.Text + "',"
                    + "cardholder ='" + cardholder.Text + "',"
                    + "address ='" + address.Text + "',"
                    + "city ='" + city.Text + "',"
                    + "state ='" + state.Text + "',"
                    + "zip ='" + zip.Text + "',"
                    + "travelerType = '" + travelerType.Text + "',"
                    + "homeAirport ='" + homeAirport.Text + "',"
                    + "class ='" + serviceClass.Text + "',"
                    + "seat ='" + seatPreference.Text + "',"
                    + "meal ='" + mealRequest.Text + "' WHERE flyerID = "
                    + Session["flyerID"], dbConnection);
                sqlCommand.ExecuteNonQuery();
            }
            catch (SqlException exception)
            {
                updateOK.Text = "<p>Error code " + exception.Number
                    + ": " + exception.Message + "</p>";
            }
            dbConnection.Close();
        }
    }

}
