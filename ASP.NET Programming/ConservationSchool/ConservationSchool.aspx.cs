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
        if (Page.IsPostBack)
        {
            Page.Validate();
            if (Page.IsValid)
            {
                SqlConnection dbConnection = new SqlConnection("Data Source=.\\SQLEXPRESS;Integrated Security=true");
                try
                {
                    dbConnection.Open();
                    dbConnection.ChangeDatabase("ConservationSchool");
                    string SQLString = "SELECT * FROM students WHERE studentID=" + studentID.Text;
                    SqlCommand checkIDTable = new SqlCommand(SQLString, dbConnection);
                    SqlDataReader idRecords = checkIDTable.ExecuteReader();
                    if (idRecords.Read())
                    {
                        Response.Redirect("ReturningStudent.aspx?studentID=" + studentID.Text);
                        idRecords.Close();
                    }
                    else
                    {
                        validateMessage.Text = "<p>**Invalid student ID**</p>";
                        idRecords.Close();
                    }
                }
                catch (SqlException exception)
                {
                    Response.Write("<p>Error code " + exception.Number
                        + ": " + exception.Message + "</p>");
                }
            }
        }
    }
}
