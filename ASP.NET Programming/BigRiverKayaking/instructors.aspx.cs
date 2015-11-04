using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class instructors : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
    
    }

    void TableHighlightReset()
    {
        Jardina.BackColor = System.Drawing.Color.White;
        Reimer.BackColor = System.Drawing.Color.White;
        Cheung.BackColor = System.Drawing.Color.White;
        Miolla.BackColor = System.Drawing.Color.White;
        Lembright.BackColor = System.Drawing.Color.White;
        Yaron.BackColor = System.Drawing.Color.White;
    }
    protected void instructor_Clicked(Object sender, ImageMapEventArgs e)
    {
        
        switch (e.PostBackValue)
        {
            case "Jardina":
                TableHighlightReset();
                Jardina.BackColor = System.Drawing.Color.Cyan;
                break;
            case "Cheung":
                TableHighlightReset();
                Cheung.BackColor = System.Drawing.Color.Cyan;
                break;
            case "Reimer":
                TableHighlightReset();
                Reimer.BackColor = System.Drawing.Color.Cyan;
                break;
            case "Miolla":
                TableHighlightReset();
                Miolla.BackColor = System.Drawing.Color.Cyan;
                break;
            case "Lembright":
                TableHighlightReset();
                Lembright.BackColor = System.Drawing.Color.Cyan;
                break;
            case "Yaron":
                TableHighlightReset();
                Yaron.BackColor = System.Drawing.Color.Cyan;
                break;

        }
    }
}
