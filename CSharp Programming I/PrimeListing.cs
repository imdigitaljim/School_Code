using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace P5JMB2
{
    public partial class primeListWindow : Form
    {
        public primeListWindow()
        {
            InitializeComponent();
            IsPrime();

        }
        private void IsPrime()
        {

            int detectPrime; //declare variables
            int primeNumber;
            double primeRemainder;
            bool IsPrime = false;
            
            primeList.Items.Add(2);//added seperate for simple calculation
            for (primeNumber = 1; primeNumber < 101; primeNumber+=2)
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
                            IsPrime = true; //
                            detectPrime = primeNumber; //break loop

                        }


                    }
                    if (IsPrime == true)
                    {
                        primeList.Items.Add(primeNumber); //boolean for listing
                    }

                }

            }
        }

    }

}
