using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.IO;

public partial class _Default : System.Web.UI.Page
{

    protected void Page_Load(object sender, EventArgs e)
    {
        if (IsPostBack)
        {
            dateLabel.Visible = false;
            time_label.Visible = false;
            flightLabel.Visible = false;
                flightNumber.Visible = false;
            month.Visible = false;
            day.Visible = false;
            year.Visible = false;
            hour.Visible = false;
            minute.Visible = false;
            am_pm.Visible = false;
            question1.Visible = false;
            question2.Visible = false;
            question3.Visible = false;
            question4.Visible = false;
            question5.Visible = false;
            question1list.Visible = false;
            question2list.Visible = false;
            question3list.Visible = false;
            question4list.Visible = false;
            question5list.Visible = false;
            submit_button.Visible = false;
            thank_you.Visible = true;

        }
    }
    protected void submit_click(Object sender, EventArgs e)
    {
        //initialization for unique survey creation
        int fileCount = 0;
        bool doesItExist = false;
        string currentLoc = Request.PhysicalApplicationPath; //puts it into applicationpath root
        do
        {
            fileCount++;
            doesItExist = System.IO.File.Exists(currentLoc + "survey" + fileCount + ".txt");
        }
        while (doesItExist == true);

        StreamWriter w;
        w = System.IO.File.CreateText(currentLoc + "survey" + fileCount + ".txt");
        
        //write it in a form for potential entry into SQL later
        w.WriteLine(month.SelectedValue + "\t" + day.SelectedValue + "\t" + year.SelectedValue + "\t" + hour.SelectedValue + "\t" + minute.SelectedValue + "\t" + am_pm.SelectedValue + "\t" + flightNumber.Text + "\t" + question1list.SelectedValue + "\t" + question2list.SelectedValue + "\t" + question3list.SelectedValue + "\t" + question4list.SelectedValue + "\t" + question5list.SelectedValue);
        w.Close();

        //adding all the surveys into SQL database
        string DBconn = System.Configuration.ConfigurationManager.ConnectionStrings["AAS"].ConnectionString;
        using (SqlConnection sqlconn = new SqlConnection(DBconn))
        {

            sqlconn.Open();
            using (SqlCommand cmd = new SqlCommand(DBconn, sqlconn))
            {

                cmd.CommandText = "INSERT INTO SurveyResponseDB (Month, Day, Year, Hour, Minute, AMPM, FlightNumber, Question1, Question2, Question3, Question4, Question5) VALUES(@Month, @Day, @Year, @Hour, @Minute, @AMPM, @FlightNumber, @Question1, @Question2, @Question3, @Question4, @Question5);";

                cmd.Parameters.AddWithValue("@Month", month.SelectedValue);
                cmd.Parameters.AddWithValue("@Day", day.SelectedValue);
                cmd.Parameters.AddWithValue("@Year", year.SelectedValue);
                cmd.Parameters.AddWithValue("@Hour", hour.SelectedValue);
                cmd.Parameters.AddWithValue("@Minute", minute.SelectedValue);
                cmd.Parameters.AddWithValue("@AMPM", am_pm.SelectedValue);
                cmd.Parameters.AddWithValue("@FlightNumber", flightNumber.Text);
                cmd.Parameters.AddWithValue("@Question1", question1list.SelectedValue);
                cmd.Parameters.AddWithValue("@Question2", question2list.SelectedValue);
                cmd.Parameters.AddWithValue("@Question3", question3list.SelectedValue);
                cmd.Parameters.AddWithValue("@Question4", question4list.SelectedValue);
                cmd.Parameters.AddWithValue("@Question5", question5list.SelectedValue);
                cmd.ExecuteNonQuery();
            }

            sqlconn.Close();
        }
        

    }
    protected void question1list_SelectedIndexChanged(object sender, EventArgs e)
    {

    }
}