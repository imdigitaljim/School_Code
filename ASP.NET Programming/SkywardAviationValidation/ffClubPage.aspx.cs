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
        else
        {
            SqlConnection dbConnection = new SqlConnection("Data Source=.\\SQLEXPRESS;AttachDbFilename=C:\\DonsData\\Course Technology\\0324-2\\Chapter.09\\Chapter\\SkywardAviation\\App_Data\\SkywardAviation.mdf;Integrated Security=True;User Instance=True");
            dbConnection.Open();
            try
            {
SqlCommand sqlCommand = new SqlCommand("SELECT flyerID, first, last FROM FrequentFlyers WHERE flyerID = "
    + Session["flyerID"], dbConnection);
                SqlDataReader userInfo = sqlCommand.ExecuteReader();
                if (userInfo.Read())
                {
                    flyerIDValue.Text = Session["flyerID"].ToString(); 
                    firstName.Text = userInfo["first"].ToString();
                    lastName.Text = userInfo["last"].ToString();
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

    }
    protected void logout_Click(object sender, EventArgs e)
    {
        Response.Cookies["flyerID"].Expires = DateTime.Now.AddDays(-1);
        Response.Redirect("Login.aspx");

    }
}
