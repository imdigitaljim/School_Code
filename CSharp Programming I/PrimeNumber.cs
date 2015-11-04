using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace P5JMB1
{
    public partial class primeWindow : Form
    {
        public primeWindow()
        {
            InitializeComponent();
        }

        private void primeButton_Click(object sender, EventArgs e) //prime calculate buttons
        {
            try
            {
                int primeNumber;
                int detectPrime;
                Boolean IsPrime = false;
                double primeRemainder;
                primeNumber = int.Parse(primeBox.Text);
                if (primeNumber > 2)
                {
                    for (detectPrime = 2; detectPrime < primeNumber; detectPrime++)
                    {
                        primeRemainder = primeNumber % detectPrime; //calculate remainder
                        if (primeRemainder == 0)
                        {
                            IsPrime = false; //set to not be prime
                            detectPrime = primeNumber; //break loop
                        }

                        if (detectPrime == primeNumber - 1)
                        {
                            if (primeRemainder != 0)
                            {
                                IsPrime = true; //set to be prime
                                detectPrime = primeNumber; //break loop

                            }


                        }

                    }

                    if (IsPrime == false)
                    {
                        primeDeclarebox.Text = "False";
                    }

                    if (IsPrime == true)
                    {
                        primeDeclarebox.Text = "True";
                    }
                }
                else
                {
                    if (primeNumber == 2)
                    {
                        primeDeclarebox.Text = "Prime Number!"; //easier to seperate from the other calculations
                    }
                    else primeDeclarebox.Text = "Number too low!"; // catch all for lower numbers
                }
            }
            catch (Exception ex) // catching wrong inputs
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            this.Close(); //exit button
        }
        
    }
}

