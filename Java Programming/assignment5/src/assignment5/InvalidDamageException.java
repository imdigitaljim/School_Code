package assignment5;

public class InvalidDamageException extends Exception{

	private static final long serialVersionUID = 1L;
	public InvalidDamageException()//required custom exception
	{
		System.out.println("Damage taken cannot be negative");
	}
}
