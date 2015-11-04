package assignment4;

/*
Bach, James
COP-3252
Assignment 4
1/25/2015
*/

public class KnightDriver 
{
	public static void main( String[] args)
	{
		while (true)
		{
			GUIWindow knightGUI = new GUIWindow();
			Knight user = knightGUI.getUserKnight();
			//System.out.println(user.toString());
			Knight computer = knightGUI.getAIKnight();
			//System.out.println(computer.toString());
			knightGUI.beginCombat(user, computer);
			if (!knightGUI.restartGame())
			{
				System.exit(0);
			}
		}
	}
	

}
