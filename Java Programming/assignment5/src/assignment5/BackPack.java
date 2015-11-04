package assignment5;

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
			wpn = new Stick();
			break;
		case 1:
			wpn = new BattleAxe();
			break;
		case 2:
			wpn = new MagicStaff();
			break;
		case 3:
			wpn = new Fists();
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
			arm = new MageCloak();
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

		public abstract CombatType getCombatType();

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
		protected String armName;

		public String getName() {
			return armName;
		}

		public void setArmName(String a) {
			armName = a;
		}

	}

	public class Stick extends Weapon {
		Stick() {
			damage = 5;
			wpnName = "Stick";

		}

		public CombatType getCombatType() {
			return CombatType.NONE;
		}
	}

	public class BattleAxe extends Weapon {
		BattleAxe() {
			damage = 6;
			wpnName = "BattleAxe";
		}

		public CombatType getCombatType() {
			return CombatType.SHARP;
		}
	}

	public class MagicStaff extends Weapon {
		MagicStaff() {
			damage = 7;
			wpnName = "Magic Staff";
		}

		public CombatType getCombatType() {
			return CombatType.MAGIC;
		}
	}

	public class Fists extends Weapon {
		Fists() {
			damage = 8;
			wpnName = "Fists";
		}

		public CombatType getCombatType() {
			return CombatType.MELEE;
		}
	}

	public class Cloth extends Armor {
		public Cloth() {
			armName = "Cloth";
		}
	}

	public class Leather extends Armor {
		Leather() {
			armName = "Leather";
		}
	}

	public class Mail extends Armor {
		Mail() {
			armName = "Mail";
		}
	}

	private class MageCloak extends Armor {
		MageCloak() {
			armName = "Mage Cloak";
		}
	}
}