using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

public partial class ReturningStudent : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Request.QueryString["studentID"] == "")
            Response.Redirect("Default.aspx");
        else
            curID.Text = "<p>Student ID: "
                + Request.QueryString["studentID"]
                + "&nbsp;<a href='ReviewSchedule.aspx?studentID="
                + Request.QueryString["studentID"]
                + "'>Review Current Schedule</a></p>";
        if (Page.IsPostBack)
        {
            Page.Validate();
            if (Page.IsValid)
            {
                registrationForm.Visible = false;
                regMessage.Visible = true;
                string studentID = Request.QueryString["studentID"];
                string selectedClass = "";
                string selectedDays = "";
                string selectedTime = "";
                for (int i = 0; i < className.Items.Count; ++i)
                {
                    if (className.Items[i].Selected)
                        selectedClass = className.Items[i].Value;
                }
                for (int i = 0; i < days.Items.Count; ++i)
                {
                    if (days.Items[i].Selected)
                        selectedDays = days.Items[i].Value;
                }
                for (int i = 0; i < time.Items.Count; ++i)
                {
                    if (time.Items[i].Selected)
                        selectedTime = time.Items[i].Value;
                }
                SqlConnection dbConnection = new SqlConnection("Data Source=.\\SQLEXPRESS;Integrated Security=true");
                try
                {
                    dbConnection.Open();
                    dbConnection.ChangeDatabase("ConservationSchool");
                    string classInfo = "INSERT INTO registration VALUES('"
                        + studentID + "', '" + selectedClass
                        + "', '" + selectedDays + "', '" + selectedTime + "')";
                    SqlCommand sqlCommand = new SqlCommand(
                        classInfo, dbConnection);
                    sqlCommand.ExecuteNonQuery();
                    regMessage.Text = "<p>You are registered for "
                        + selectedClass + " on " + selectedDays + ", " + selectedTime;
                    regMessage.Text += "<p>Click your browser's Back button to register for more classes.</p>";
                }
                catch (SqlException exception)
                {
                    Response.Write("<p>Error code " + exception.Number
                        + ": " + exception.Message + "</p>");
                }
                dbConnection.Close();


            }
        }

    }
}
