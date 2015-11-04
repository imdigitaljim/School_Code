package assignment3;
/*
Bach, James
COP-3252
Assignment 3
1/25/2015
*/

public class Stars 
{
	
	private int rows, columns;
	public int getRows() 
	{
		return rows;
	}
	
	public void setRows(int r) 
	{
		rows = r;
	}
	
	public int getColumns() 
	{
		return columns;
	}
	
	public void setColumns(int c) 
	{
		columns = c;
	}
	
	Stars(int c, int r)
	{
		columns = c;
		rows = r;	
	}
	
	public String getStars() 
	{
		String stars = "";
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				stars = stars + "*   ";
			}
			stars = stars + "\n";
			if (i % 2 == 0)
			{
				stars = stars + "  ";
			}	
		}
		return stars;
	}


	
}
