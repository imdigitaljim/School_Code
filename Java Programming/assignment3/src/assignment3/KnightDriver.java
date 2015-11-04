package assignment3;
/*
Bach, James
COP-3252
Assignment 3
1/25/2015
*/
import javax.swing.JOptionPane; // program uses JOptionPane

public class KnightDriver 
{
	
	public static void main( String[] args)
	{
		
		String name = JOptionPane.showInputDialog(
				"Enter your knight's name:", "Sir Jav-a-lot");
		int health = Integer.parseInt(JOptionPane.showInputDialog(
				"Enter your knight's health:", "12"));
		int battles = Integer.parseInt(JOptionPane.showInputDialog(
				"Enter your knight's battles:", "6"));
		int age = Integer.parseInt(JOptionPane.showInputDialog(
				"Enter your knight's age:", "25"));
		int gold = Integer.parseInt(JOptionPane.showInputDialog(
				"Enter your knight's gold:", "100"));
		int columns = Integer.parseInt(JOptionPane.showInputDialog(
				"Enter number of star columns:", "10"));
		int rows = Integer.parseInt(JOptionPane.showInputDialog(
				"Enter number of star rows:", "10"));
		Knight myKnight = new Knight(name, health, battles, age, gold);
		Stars myStars = new Stars(columns, rows);
		String knightInfo = String.format(
					"Knight Name: %s\nKnight Health: %d\n"
					+ "Knight Battles: %d\nKnight Age: %d\n"
					+ "Knight Gold: %d\n",
					myKnight.getName(),myKnight.getHealth(),
					myKnight.getBattles(),myKnight.getAge(),
					myKnight.getGold());
		String starInfo = myStars.getStars();
		JOptionPane.showMessageDialog(null, knightInfo + starInfo);
	}


}
