using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace P6JMB
{
    public partial class nameSearch : Form
    {
        public nameSearch()
        {
            InitializeComponent();
        }
        private void BoyNames()
        {
            boyPopularCheck.Text = "";
            const int arraySize = 200;
            string[] boyArray = new String[arraySize];
            int boyIndex = 0;
            String boyNameCheck = boyInput.Text;
            Boolean boyPopular = false;

            try
            {
                //open boy file
                StreamReader inputBoyFile = File.OpenText("BoyNames.txt");
                //read into array
                while (!inputBoyFile.EndOfStream)
                {
                    boyArray[boyIndex] = inputBoyFile.ReadLine();
                    boyIndex++;
                }

            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            try
            {
                for (int i = 0; i < boyIndex; i++)
                {
                    if (string.Equals(boyNameCheck,boyArray[i],StringComparison.CurrentCultureIgnoreCase))
                    {
                        boyPopular = true;
                        i = boyIndex;
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            if (boyPopular == true)
            {
                boyPopularCheck.Text = "Popular";
            }
            if (boyPopular == false)
            {
                if (boyNameCheck != "")
                {
                    boyPopularCheck.Text = "Not Popular";
                }
            }
            }
       

        private void girlNames()
        {
            girlPopularCheck.Text = "";
            const int arraySize = 200;
            string[] girlArray = new String[arraySize];
            int girlIndex = 0;
            String girlNameCheck = girlInput.Text;
            Boolean girlPopular = false;

            try
            {

                //open girl file
                StreamReader inputGirlFile = File.OpenText("GirlNames.txt");
                //read into array
                while (!inputGirlFile.EndOfStream)
                {
                    girlArray[girlIndex] = inputGirlFile.ReadLine();
                    girlIndex++;
                }
            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
             try
            {
                for (int i = 0; i < girlIndex; i++)
                {
                    if (string.Equals(girlNameCheck, girlArray[i], StringComparison.CurrentCultureIgnoreCase))
                    {
                        girlPopular = true;
                        i = girlIndex;
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            if (girlPopular == true)
            {
                girlPopularCheck.Text = "Popular";
            }
            if (girlPopular == false)
            {
                if (girlNameCheck != "")
                {
                    girlPopularCheck.Text = "Not Popular";
                }
            }
            
       
        }
        

        private void exitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        
        //from MSDN.MICROSOFT.COM
        //ADDED FOR FUNCTIONALITY
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Escape) this.Close();
            return base.ProcessCmdKey(ref msg, keyData);
        }
        

        private void clearButton_Click(object sender, EventArgs e)
        {
            boyInput.Text = "";
            girlInput.Text = "";
            boyPopularCheck.Text = "";
            girlPopularCheck.Text = "";

        }

        private void boyCheckButton_Click(object sender, EventArgs e)
        {
            BoyNames();
        }

        private void girlCheckButton_Click(object sender, EventArgs e)
        {
            girlNames();
        }



    }
}
