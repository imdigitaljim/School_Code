//Project 1
//COP2552 
//Orion Constellation
//James Bach
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace P1JMB
{
    public partial class starWind : Form
    {
        //initialization of designer code

        public starWind()
        {
            InitializeComponent();
        }


        // show label buttons => setting all labels to Visible = true;

        private void showStar_Click(object sender, EventArgs e)
        {
            betelgeuseLabel.Visible = true;
            meissaLabel.Visible = true;
            mintakaLabel.Visible = true;
            alnilamLabel.Visible = true;
            alnitakLabel.Visible = true;
            saiphLabel.Visible = true;
            rigelLabel.Visible = true;
        }
        // hide label buttons => setting all labels to Visible = false;
        private void hideStar_Click(object sender, EventArgs e)
        {
            betelgeuseLabel.Visible = false;
            meissaLabel.Visible = false;
            mintakaLabel.Visible = false;
            alnilamLabel.Visible = false;
            alnitakLabel.Visible = false;
            saiphLabel.Visible = false;
            rigelLabel.Visible = false;
        }

        // exit program button
        private void exitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void orionImage_Click(object sender, EventArgs e)
        {

        }


       
    }
}
