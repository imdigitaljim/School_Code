package assignment3;
/*
Bach, James
COP-3252
Assignment 3
1/25/2015
*/

public class Knight 
{
	private String name;
	private int health, battles, age, gold;

	public Knight(String n,int h,int b,int a,int g)
	{
		name = n;
		health = h;
		battles = b;
		age = a;
		gold = g;
	}
	
	public int getHealth() 
	{
		return health;
	}
	public void setHealth(int h) 
	{
		health = h;
	}
	
	public int getBattles() 
	{
		return battles;
	}
	
	public void setBattles(int b) 
	{
		battles = b;
	}
	
	public int getAge() 
	{
		return age;
	}
	
	public void setAge(int a) 
	{
		age = a;
	}
	
	public int getGold() 
	{
		return gold;
	}
	
	public void setGold(int g) 
	{
		gold = g;
	}
	
	public String getName() 
	{
		return name;
	}
	
	public void setName(String n) 
	{
		name = n;
	}
}
