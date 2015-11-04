using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace P2JMB
{
    public partial class sentenceBuild : Form
    {
        public sentenceBuild()
        {
            InitializeComponent();
        }

        //setting button clicks to output Label
        private void lowerAbutton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "a";

        }
        private void upperAbutton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "A";
        }

        private void spaceButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + " ";
        }

        private void lowerAnbutton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "an";
        }

        private void upperAnbutton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "An";
        }

        private void lowerThebutton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "the";
        }

        private void upperThebutton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "The";
        }

        private void manButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "man";
        }

        private void womanButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "woman";
        }

        private void dogButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "dog";
        }

        private void catButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "cat";
        }

        private void carButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "car";
        }

        private void bicycleButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "bicycle";
        }

        private void beautButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "beautiful";
        }

        private void bigButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "big";
        }

        private void spokeButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "spoke";
        }

        private void smallButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "small";
        }

        private void strangeButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "strange";
        }

        private void lookedButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "looked at";
        }

        private void rodeButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "rode";
        }

        private void droveButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "drove";
        }

        private void laughButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "laughed at";
        }

        private void periodButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + ".";
        }

        private void exclamButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = outputLabel.Text + "!";
        }


        //close program
        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        //reset Label
        private void clearButton_Click(object sender, EventArgs e)
        {
            outputLabel.Text = "";
        }

        private void sentenceBuild_Load(object sender, EventArgs e)
        {

        }

       
       }
}
