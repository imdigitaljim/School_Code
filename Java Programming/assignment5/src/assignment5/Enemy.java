package assignment5;

import java.util.Random;

public abstract class Enemy {
	protected int health;
	protected CombatType weakness;
	protected CombatType strength;

	public int getHealth() {
		return health;
	}

	public void setHealth(int hp) {
		health = hp;
	}

	public int takeDamage(int dmg, CombatType t) throws InvalidDamageException {
		if (t == weakness) {
			dmg *= 2;
		} else if (t == strength) {
			dmg /= 2;
		}

		if (dmg < 0) {
			throw new InvalidDamageException();
		}
		health -= dmg;
		return dmg;
	}

	public abstract int fight();

	public abstract String getAbility(int i);

	public CombatType getWeakness() {
		return weakness;
	}

	public CombatType getCombatType() {
		return strength;
	}

	public static Enemy getRandomEnemy() {
		Random r = new Random();

		switch (r.nextInt(3)) {
		case 0:
			return new Ogre();
		case 1:
			return new Troll();
		case 2:
			return new Sorcerer();
		default:
			throw new IndexOutOfBoundsException();
		}

	}
}
