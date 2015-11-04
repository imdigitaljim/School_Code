package assignment5;

import java.util.Random;

public class Ogre extends Enemy {
	
	private String name = "Ogre";

	public Ogre() {
		health = 40;
		weakness = CombatType.MAGIC;
		strength = CombatType.MELEE;
	}

	public int fight() {
		Random r = new Random();
		int d = 4 + r.nextInt(8); // base + random
		return d;
	}

	public String getAbility(int i) {
		switch (i) {
		case 0:
			return "Smash";
		case 1:
			return "Break";
		case 2:
			return "Tackle";
		default:
			return "Invalid Input";
		}
	}

	public String toString() {
		return name;
	}
}
