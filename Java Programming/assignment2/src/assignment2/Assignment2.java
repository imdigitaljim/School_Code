package assignment2;
import java.util.Scanner;

public class Assignment2 
{
	public static void main(String[] args)
	{
		String name;
		Scanner input = new Scanner(System.in);
		int health;
		int battles;
		int age;
		int gold;
		
		System.out.printf("What is the Knight's name? ");
		name = input.nextLine();
		System.out.printf("What is %s's health? ", name);
		health = input.nextInt();
		System.out.printf("How many battles has %s been in? ", name);
		battles = input.nextInt();
		System.out.printf("What is %s's age? ", name);
		age = input.nextInt();
		System.out.printf("How much gold does %s have? ", name);
		gold = input.nextInt();
		input.close();
		
		System.out.printf("\n********** KNIGHT STATS***********************");
		System.out.printf("\n Name       : %s", name);
		System.out.printf("\n Health     : %d", health);
		System.out.printf("\n Battles    : %d", battles);
		System.out.printf("\n Age        : %d", age);
		System.out.printf("\n Gold       : %d", gold);
		System.out.printf("\n Gold Per Battle (GPB): %d", gold / battles);
		System.out.printf("\n*********************************************");
		
		
	}
}
