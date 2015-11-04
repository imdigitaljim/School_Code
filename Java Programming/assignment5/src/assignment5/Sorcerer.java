package assignment5;

import java.util.Random;

public class Sorcerer extends Enemy {

	private String name = "Sorcerer";

	public Sorcerer() {
		health = 15;
		weakness = CombatType.SHARP;
		strength = CombatType.MAGIC;
	}

	public int fight() {
		Random r = new Random();
		int d = 10 + r.nextInt(10); // base + random
		return d;
	}

	public String getAbility(int i) {
		switch (i) {
		case 0:
			return "Magic Missile";
		case 1:
			return "FireBall";
		case 2:
			return "IceBreath";
		default:
			return "Invalid Input";
		}
	}

	public String toString() {
		return name;
	}
}
