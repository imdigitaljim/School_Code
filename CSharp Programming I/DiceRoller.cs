using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace P4JMB
{
    public partial class simGui : Form
    {
        public simGui()
        {
            InitializeComponent();
        }

        //roll button
        private void buttonRoll_Click(object sender, EventArgs e)
        {
            int randLeftRoll;
            int randRightRoll;
            Random rand = new Random();

            randLeftRoll = rand.Next(6);  //random roll for left d6
            randRightRoll = rand.Next(6); //random roll for right d6
            
            
            /* verification of functionality of all numbers vs pictures
            MessageBox.Show((randLeftRoll+1) + " " + (randRightRoll+1));
            */


            //switch for left d6 visibility
            switch (randLeftRoll)
            {
                case 0:
                    leftOne.Visible = true;
                    leftTwo.Visible = false;
                    leftThree.Visible = false;
                    leftFour.Visible = false;
                    leftFive.Visible = false;
                    leftSix.Visible = false;
                    break;

                case 1:
                    leftOne.Visible = false;
                    leftTwo.Visible = true;
                    leftThree.Visible = false;
                    leftFour.Visible = false;
                    leftFive.Visible = false;
                    leftSix.Visible = false;
                    break;

                case 2:
                    leftOne.Visible = false;
                    leftTwo.Visible = false;
                    leftThree.Visible = true;
                    leftFour.Visible = false;
                    leftFive.Visible = false;
                    leftSix.Visible = false;
                    break;

                case 3:
                    leftOne.Visible = false;
                    leftTwo.Visible = false;
                    leftThree.Visible = false;
                    leftFour.Visible = true;
                    leftFive.Visible = false;
                    leftSix.Visible = false;
                    break;

                case 4:
                    leftOne.Visible = false;
                    leftTwo.Visible = false;
                    leftThree.Visible = false;
                    leftFour.Visible = false;
                    leftFive.Visible = true;
                    leftSix.Visible = false;
                    break;

                case 5: 
                    leftOne.Visible = false;
                    leftTwo.Visible = false;
                    leftThree.Visible = false;
                    leftFour.Visible = false;
                    leftFive.Visible = false;
                    leftSix.Visible = true;
                    break;
            }



            //switch for right d6 visibility
            switch (randRightRoll)
            {
                case 0:
                    rightOne.Visible = true;
                    rightTwo.Visible = false;
                    rightThree.Visible = false;
                    rightFour.Visible = false;
                    rightFive.Visible = false;
                    rightSix.Visible = false;
                    break;

                case 1:
                    rightOne.Visible = false;
                    rightTwo.Visible = true;
                    rightThree.Visible = false;
                    rightFour.Visible = false;
                    rightFive.Visible = false;
                    rightSix.Visible = false;
                    break;

                case 2:
                    rightOne.Visible = false;
                    rightTwo.Visible = false;
                    rightThree.Visible = true;
                    rightFour.Visible = false;
                    rightFive.Visible = false;
                    rightSix.Visible = false;
                    break;

                case 3:
                    rightOne.Visible = false;
                    rightTwo.Visible = false;
                    rightThree.Visible = false;
                    rightFour.Visible = true;
                    rightFive.Visible = false;
                    rightSix.Visible = false;
                    break;

                case 4:
                    rightOne.Visible = false;
                    rightTwo.Visible = false;
                    rightThree.Visible = false;
                    rightFour.Visible = false;
                    rightFive.Visible = true;
                    rightSix.Visible = false;
                    break;

                case 5:
                    rightOne.Visible = false;
                    rightTwo.Visible = false;
                    rightThree.Visible = false;
                    rightFour.Visible = false;
                    rightFive.Visible = false;
                    rightSix.Visible = true;
                    break;
            }

        }

        //exit button
        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }




    }
}
