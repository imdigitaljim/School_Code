package assignment4;

import java.util.Random;

public class Knight {
	private String[] randName = { "Lt. SpongeBob", "Capt Jack Sparrow",
			"Sir Jav-A-Lot", "Sir Rick Hurst", "Master Chief" };

	private String name;
	private BackPack bag;
	
	public BackPack getBag() {
		return bag;
	}

	public void setBag(BackPack b) {
		bag = b;
	}

	private int health;

	public void setHealth(int hp) {
		health = hp;
	}

	public void setName(String s) {
		name = s;
	}

	public String getWeaponName() {
		return bag.getWeapon().getName();
	}

	public String getWeakness() {
		return bag.getArmor().getWeakness();
	}

	public String getArmorName() {
		return bag.getArmor().getName();
	}

	public int getHealth() {
		return health;
	}

	public String getName() {
		return name;
	}

	public BackPack getBackPack() {
		return bag;
	}
	
	//isnt used meant for meeting writeup requirement
	public String toString()
	{
		String s = name + ", " + health + ", "
				+ getWeaponName() + ", " + getArmorName();
		return s;
	}
	Knight() {
		Random r = new Random();
		bag = new BackPack();
		bag.setArmor(4); // 4 is the
		bag.setWeapon(4); // random trigger
		health = 75 + r.nextInt(25);
		name = randName[r.nextInt(randName.length)];
	}

	Knight(int w, int a) {
		this();
		bag.setArmor(a);
		bag.setWeapon(w);

	}

	Knight(String n, int w, int a) {
		this(w,a);
		if ( n == null || n.length() == 0) {
			n = "Mr. Too Good for a Name";
		}
		setName(n);
	}

	public int fight() {
		return bag.getWeapon().getDamage();
	}

}
