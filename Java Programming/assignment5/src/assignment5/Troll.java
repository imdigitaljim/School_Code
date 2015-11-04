package assignment5;

import java.util.Random;

public class Troll extends Enemy {

	private String name = "Troll";

	public Troll() {
		health = 30;
		weakness = CombatType.MELEE;
		strength = CombatType.SHARP;
	}

	public int fight() {
		Random r = new Random();
		int d = 5 + r.nextInt(4); // base + random
		return d;
	}

	public String getAbility(int i) {
		try {
			switch (i) {
			case 0:
				return "AxeThrow";
			case 1:
				return "Javelin";
			case 2:
				return "Scare";
			default:
					throw new IndexOutOfBoundsException();
			}
		} catch (IndexOutOfBoundsException e) { //required standard exception
			System.out
					.println("Random Ability Selection Failure: Integer Selection OutOfBounds");
			return null;
		}
	}

	public String toString() {
		return name;
	}
}
