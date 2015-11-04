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
        SqlConnection dbConnection = new SqlConnection(
    "Data Source=.\\SQLEXPRESS;Integrated Security=true");
        try
        {
            dbConnection.Open();
            dbConnection.ChangeDatabase("forecast");
            string retString = "SELECT * FROM outlook ORDER BY city";
            SqlCommand outlookCommand =
                new SqlCommand(retString, dbConnection);
            SqlDataReader outlookRecords
                = outlookCommand.ExecuteReader();
            if (outlookRecords.Read())
            {
                Response.Write("<table width='100%' border='1'>");
                Response.Write("<tr><th>City</th><th>State</th><th>Day</th><th>High</th><th>Low</th><th>Conditions</th></tr>");
                do
                {
                    Response.Write("<tr>");
                    Response.Write("<td>" + outlookRecords["city"]
                        + "</td>");
                    Response.Write("<td>" + outlookRecords["state"]
                        + "</td>");
                    Response.Write("<td>" + outlookRecords["day"]
                        + "</td>");
                    Response.Write("<td>" + outlookRecords["high"]
                        + "</td>");
                    Response.Write("<td>" + outlookRecords["low"]
                        + "</td>");
                    Response.Write("<td>"
                        + outlookRecords["conditions"] + "</td>");
                    Response.Write("</tr>");
                } while (outlookRecords.Read());
                Response.Write("</table>");
            }
            else
                Response.Write("<p>Your query returned no results.</p>");
            outlookRecords.Close();
        }
        catch (SqlException exception)
        {
            Response.Write("<p>Error code " + exception.Number
                + ": " + exception.Message + "</p>");
        }
        dbConnection.Close();
        addForecast("INSERT INTO outlook VALUES('Tucson', 'AZ', 'Tuesday', 102, 72, 'Partly cloudy')");
        addForecast("INSERT INTO outlook VALUES('Williamsburg', 'VA', 'Wednesday', 90, 71, 'Mostly clear')");

    }
    protected void addForecast(string newRecord)
    {
        SqlConnection dbConnection = new SqlConnection(
            "Data Source=DGOSSELI-LAP\\SQLEXPRESS;Integrated Security=true");
        try
        {
            dbConnection.Open();
            dbConnection.ChangeDatabase("forecast");
            SqlCommand outlookCommand = new SqlCommand(
                newRecord, dbConnection);
            outlookCommand.ExecuteNonQuery();
            Response.Write("<p>Successfully added record.</p>");
        }
        catch (SqlException exception)
        {
            Response.Write("<p>Error code " + exception.Number
                + ": " + exception.Message + "</p>");
        }

        dbConnection.Close();

    }
}
