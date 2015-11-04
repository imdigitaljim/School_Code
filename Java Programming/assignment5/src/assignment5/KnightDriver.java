package assignment5;

/*
Bach, James
COP-3252
Assignment 5
3/20/2015
*/

public class KnightDriver 
{
	public static void main( String[] args)
	{
		while (true)
		{
			CombatWindow knightGUI = new CombatWindow();
			knightGUI.beginCombat();
			if (!knightGUI.restartGame())
			{
				System.exit(0);
			}
		}
	}
	

}
