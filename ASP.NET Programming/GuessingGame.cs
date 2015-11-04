using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            string selectedWord = wordSelect();
            string output_Word = encryptWord(selectedWord);
            chosen_word.Text = selectedWord;
            display_word.Text = output_Word;
        }
    }

    protected string wordSelect()
    {
        Random r = new Random();
        int word_SeeD = r.Next(0, 5);
        string[] secret_Words = new string[] { "paradox", "monkey", "giraffe", "gators", "liberty" };
        string theWord = secret_Words[word_SeeD];
        return theWord;
    }
    protected string encryptWord(string chosen)
    {
        string hiddenWord = "";
        for (int i = 0; i < chosen.Length; i++)
        {
            hiddenWord += "*";

        }
        return hiddenWord;
    }

    protected void main_game()
    {

        char[] inputLetter = input_guess.Text.ToCharArray();
        char[] actualLetters = chosen_word.Text.ToCharArray();
        char[] replaceLetters = display_word.Text.ToCharArray();
        if (chosen_word.Text.Contains(input_guess.Text) == true)
        {
            for (int i = 0; i < chosen_word.Text.Length; i++)
            {
                if (actualLetters[i] == inputLetter[0])
                {
                    replaceLetters[i] = inputLetter[0];
                    display_word.Text = String.Join("", replaceLetters);
                    input_guess.Text = "";

                }

            }


        }

    }

    protected void guess_click(Object Source, EventArgs e)
    {
        if (input_guess.Text == "")
        {
            input_guess.Text = "Enter a letter";

        }
        else
        {
            main_game();
        }

        if (display_word.Text == chosen_word.Text)
        {
            win_Condition.Visible = true;
            button.Visible = false;
            input_guess.Visible = false;
            tip.Visible = false;
        }








    }


}