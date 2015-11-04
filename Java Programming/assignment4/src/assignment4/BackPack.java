package assignment4;

import java.util.Random;

public class BackPack {
	private Weapon wpn;
	private Armor arm;
	public Weapon getWeapon() {
		return wpn;
	}
	public Armor getArmor() {
		return arm;
	}
	public void setWeapon(int w) {
		switch (w) {
		case 0:
			wpn = new LongSword();
			break;
		case 1:
			wpn = new BattleAxe();
			break;
		case 2:
			wpn = new Spear();
			break;
		case 3:
			wpn = new Warhammer();
			break;
		case 4:
			Random r = new Random();
			setWeapon(r.nextInt(4));
			break;
		default:
			System.exit(0);
			break;
		}
	}
	public void setArmor(int a) {
	
		switch (a) {
		case 0:
			arm = new Cloth();
			break;
		case 1:
			arm = new Leather();
			break;
		case 2:
			arm = new Mail();
			break;
		case 3:
			arm = new Plate();
			break;
		case 4:
			Random r = new Random();
			setArmor(r.nextInt(4));
			break;
		default:
			System.exit(0);
			break;
		}
	}

	public abstract class Weapon {
		protected String wpnName;
		protected int damage;
		
		public void setName(String w) {
			wpnName = w;
		}
		public String getName() {
			return wpnName;
		}
		public void setDamage(int d) {
			damage = d;
		}		

		public int getDamage() {
			return damage;
		}
	}

	public abstract class Armor {
		protected String weakness;
		protected String armName;

		public String getName() {
			return armName;
		}
		public String getWeakness() {
			return weakness;
		}
		public void setWeakness(String w) {
			weakness = w;
		}
		public void setArmName(String a) {
			armName = a;
		}

	}

	public class LongSword extends Weapon {
		LongSword() {
			damage = 5;
			wpnName = "LongSword";

		}
	}

	public class BattleAxe extends Weapon {
		BattleAxe() {
			damage = 6;
			wpnName = "BattleAxe";
		}
	}

	public class Spear extends Weapon {
		Spear() {
			damage = 7;
			wpnName = "Spear";
		}
	}

	public class Warhammer extends Weapon {
		Warhammer() {
			damage = 8;
			wpnName = "Warhammer";
		}
	}

	public class Cloth extends Armor {
		public Cloth() {
			weakness = "LongSword";
			armName = "Cloth";
		}
	}

	public class Leather extends Armor {
		Leather() {
			weakness = "BattleAxe";
			armName = "Leather";
		}
	}

	public class Mail extends Armor {
		Mail() {
			weakness = "Spear";
			armName = "Mail";
		}
	}

	private class Plate extends Armor {
		Plate() {
			weakness = "Warhammer";
			armName = "Plate";
		}
	}
}