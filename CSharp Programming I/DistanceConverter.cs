using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace P3JMB
{
    public partial class distanceConverterform : Form
    {
        public distanceConverterform()
        {
            InitializeComponent();
        }



        private void convertButton_Click(object sender, EventArgs e)
        {
            try
            {
                double distanceInput; // distance input
                int convFrom;
                int convTo;

                // collect the distance input from the field

                distanceInput = double.Parse(userInputbox.Text);

                convFrom = convertFromListBox.SelectedIndex; //conversion from selection variables
                convTo = convertToListBox.SelectedIndex; //conversion to selection variables

                if (convFrom != -1 && convTo != -1)
                {
                    switch (convFrom)
                    {
                        case 0:                    //inches
                            switch (convTo)
                            {
                                case 0:           //to inches
                                    userOutputbox.Text = distanceInput.ToString();
                                    break;
                                case 1:            //to feet
                                    distanceInput = distanceInput / 12;
                                    userOutputbox.Text = distanceInput.ToString("n2");
                                    break;
                                case 2:            //to yards
                                    distanceInput = distanceInput / 36;
                                    userOutputbox.Text = distanceInput.ToString("n2");
                                    break;
                            }
                            break;

                        case 1:                     //feet
                            switch (convTo)
                            {
                                case 0:            //to inches
                                    distanceInput = distanceInput * 12;
                                    userOutputbox.Text = distanceInput.ToString("n2");
                                    break;
                                case 1:            //to feet
                                    userOutputbox.Text = distanceInput.ToString();
                                    break;
                                case 2:            //to yards
                                    distanceInput = distanceInput / 3;
                                    userOutputbox.Text = distanceInput.ToString("n2");
                                    break;
                            }
                            break;

                        case 2:                       //yards
                            switch (convTo)
                            {
                                case 0:            //to inches
                                    distanceInput = distanceInput * 36;
                                    userOutputbox.Text = distanceInput.ToString("n2");
                                    break;
                                case 1:            //to feet
                                    distanceInput = distanceInput * 3;
                                    userOutputbox.Text = distanceInput.ToString("n2");
                                    break;
                                case 2:            //to yards
                                    userOutputbox.Text = distanceInput.ToString();
                                    break;
                            }
                            break;
                    }
                }
                else
                {
                    userOutputbox.Text = "Please select conversions"; // catching bad/no input
                }
            }

            catch (Exception ex) // catching bad/no input
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
