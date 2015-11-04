package assignment5;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

public class CombatWindow {
	private JFrame knightApp;
	private JLabel[] inStats;
	private JLabel[] aiStats;
	private JPanel pnlStats;
	private String[] lblNames = { "HP :", "Name :", "Weapon :", "Armor :" };

	private Knight player;
	private Enemy pc;
	private Enemy pc2;
	private static int statCount = 4;
	
	//interpreted from assignment writeup and extra credit 
	//When the attack is set up, this window requests how many
	//the knight sees. Then it begins combat with the enemies
	//seen and for the extra credit it doesnt ALWAYS 
	//have to be minimum 2 but can support at least 2
	//since the encounter is random 
	private static int enemyCount = 1;

	CombatWindow() {
		knightApp = new JFrame("KnightFight");
		inStats = new JLabel[statCount * 2]; // label + entry
		aiStats = new JLabel[statCount * 2];
		pnlStats = new JPanel();
		initStatWindow();
		player = new Knight(printGetString("What is your Knight's Name?"),
				selectWeapon(), selectArmor());
	}

	private void updateStats() {
		aiStats[4].setText(Integer.toString(pc.getHealth()));
		aiStats[5].setText(pc.toString());
		if (enemyCount > 1) {
			aiStats[2].setVisible(true);
			aiStats[3].setVisible(true);
			aiStats[6].setVisible(true);
			aiStats[7].setVisible(true);
			aiStats[6].setText(Integer.toString(pc2.getHealth()));
			aiStats[7].setText(pc2.toString());
		} else {
			aiStats[2].setVisible(false);
			aiStats[3].setVisible(false);
			aiStats[6].setVisible(false);
			aiStats[7].setVisible(false);
		}
		inStats[4].setText(Integer.toString(player.getHealth()));
		inStats[5].setText(player.getName());
		inStats[6].setText(player.getWeaponName());
		inStats[7].setText(player.getArmorName());
	}

	private int selectWeapon() {
		String[] wpnNames = { "Stick", "BattleAxe", "Magic Staff", "Fists" };
		String prompt = "Choose a weapon!\n" + "Stick: No special attributes\n"
				+ "BattleAxe: Sharp Damage\n" + "Magic Staff: Magic Damage\n"
				+ "Fists: Melee Damage";
		return printGetMsg(prompt, "Weapon Select", wpnNames);
	}

	private int selectArmor() {
		String[] armNames = { "Cloth", "Leather", "Mail", "Plate" };
		return printGetMsg("Choose armor!", "Armor Select", armNames);
	}

	private void initStatWindow() {

		knightApp.add(pnlStats);
		knightApp.setResizable(false);
		knightApp.setLocation(400, 400);
		knightApp.setSize(400, 400);

		pnlStats.setSize(knightApp.getSize());
		pnlStats.setLayout(null);
		pnlStats.setBackground(Color.white);

		for (int i = 0; i < statCount; i++) {
			// set player panel info
			inStats[i] = new JLabel(lblNames[i], SwingConstants.RIGHT);
			inStats[i].setSize(75, 20);
			inStats[i].setFont(Font.getFont("Arial"));
			inStats[i].setBackground(Color.lightGray);
			inStats[i].setLocation(140, 270 + (25 * i));
			inStats[i].setOpaque(true);
			inStats[i + 4] = new JLabel("", SwingConstants.CENTER);
			inStats[i + 4].setSize(150, 20);
			inStats[i + 4].setFont(Font.getFont("Arial"));
			inStats[i + 4].setBackground(Color.lightGray);
			inStats[i + 4].setOpaque(true);
			inStats[i + 4].setLocation(215, 270 + 25 * i);
			pnlStats.add(inStats[i]);
			pnlStats.add(inStats[i + 4]);

			// ai portion
			aiStats[i] = new JLabel(lblNames[i % 2], SwingConstants.RIGHT);
			aiStats[i].setSize(75, 20);
			aiStats[i].setFont(Font.getFont("Arial"));
			aiStats[i].setBackground(Color.lightGray);
			aiStats[i].setLocation(10, 10 + (25 * i));
			aiStats[i].setOpaque(true);

			aiStats[i + 4] = new JLabel("", SwingConstants.CENTER);
			aiStats[i + 4].setSize(150, 20);
			aiStats[i + 4].setFont(Font.getFont("Arial"));
			aiStats[i + 4].setBackground(Color.lightGray);
			aiStats[i + 4].setOpaque(true);
			aiStats[i + 4].setLocation(85, 10 + 25 * i);
			if (i > 1) {
				aiStats[i].setVisible(false);
				aiStats[i + 4].setVisible(false);
			}
			pnlStats.add(aiStats[i]);
			pnlStats.add(aiStats[i + 4]);
		}
		knightApp.setVisible(true);
		printMessage("You've entered the JavaBean Forest!");
	}

	public void beginCombat() {
		String msgString = "";
		pc = Enemy.getRandomEnemy();
		Random r = new Random();
		if (r.nextBoolean()) {
			enemyCount++;
			pc2 = Enemy.getRandomEnemy();
		}

		String a = "You've encountered:\n" + pc.toString();
		if (enemyCount > 1) {
			a += " and " + pc2.toString();
		}
		a += "\nAre you ready to FIGHT!?";
		if (!(printGetMsg(a, "Combat Phase") == 0)) {
			return;
		}
		updateStats();
		String[] option = { "Weapon", "Magic", "Flee" };
		// Would you like to fight with these stats
		System.out.println(pc);

		printMessage("The battle begins!");
		boolean isTurn = r.nextBoolean();
		if (isTurn) {
			printMessage("You get the initiative!");
		} else {
			printMessage(pc.toString() + " gets the initiative!");
		}
		while (player.getHealth() > 0) {
			if (isTurn) {
				// check if continue or quit
				int cmbtSelect = printGetMsg(
						"It is your turn! What will you do?", "Your turn",
						option);
				if (!(cmbtSelect == 0 || cmbtSelect == 1)) {
					return;
				} else {
					// attack
					int enmySelect = 0;
					CombatType type = CombatType.MAGIC;
					if (cmbtSelect == 0) {
						type = player.getWeaponType();
					}
					if (enemyCount > 1) {
						msgString = "Who will you attack?";
						String[] choice = { pc.toString(), pc2.toString() };
						enmySelect = printGetMsg(msgString, "Enemy Select",
								choice);
					}
					int newDmg = 0, dmg = player.fight();
					try
					{
					if (enmySelect == 0) {
						msgString = pc.toString();
						newDmg = pc.takeDamage(dmg, type);
					} else {
						msgString = pc2.toString();
						newDmg = pc2.takeDamage(dmg, type);
					}
					}
					catch (InvalidDamageException e)
					{
						//no behavior defined by writeup
					}
					
					if (dmg > newDmg) {
						msgString += " is strong against "
								+ player.getWeaponName(cmbtSelect);
						printMessage(msgString);
					} else if (dmg < newDmg) {
						msgString += " is weak against "
								+ player.getWeaponName(cmbtSelect);
						printMessage(msgString);
					}
					msgString = "You did " + newDmg + " damage with your "
							+ player.getWeaponName(cmbtSelect);
					printMessage(msgString);
					// update panel for user
					updateStats();
					isTurn = false;
				}
			}
			if (!isTurn) {
				// check win condition
				if (enemyCount > 1) {
					if (pc.getHealth() <= 0) {
						printMessage("You have slain " + pc.toString());
						pc = pc2;
						--enemyCount;
	
					} else if (pc2.getHealth() <= 0) {
						printMessage("You have slain " + pc2.toString());
						--enemyCount;
					}
				} else if (pc.getHealth() <= 0) {
					printMessage("You won the battle!");
					return;
				}
				updateStats();
				// begin enemy turn
				printMessage(pc.toString() + " attacks!");
				// attack
				int dmg = pc.fight();
				msgString = pc.toString() + " did " + dmg + " with "
						+ pc.getAbility(r.nextInt(3));
				printMessage(msgString);
				player.takeDamage(dmg);
				updateStats();
				if (enemyCount > 1 && player.getHealth() >= 1) {

					printMessage(pc2.toString() + " attacks!");
					// attack
					dmg = pc2.fight();
					msgString = pc2.toString() + " did " + dmg + " with "
							+ pc2.getAbility(r.nextInt(3));
					printMessage(msgString);
					player.takeDamage(dmg);
				}
				// update panel for user
				updateStats();
				isTurn = true;
			}
		}
		printMessage("You died!");
		return;
	}

	public void printMessage(String x) {
		JOptionPane.showMessageDialog(knightApp, x);
	}

	public int printGetMsg(String x, String y) {
		String[] optionYN = { "Yes", "No" };
		return printGetMsg(x, y, optionYN);
	}

	public int printGetMsg(String x, String y, String[] z) {
		return JOptionPane.showOptionDialog(knightApp, x, y,
				JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,
				null, z, null);
	}

	public String printGetString(String x) {
		return JOptionPane.showInputDialog(knightApp, x);
	}

	public boolean restartGame() {
		knightApp.setVisible(false);
		if (printGetMsg("Would you like to restart?", "The End") == 0) {
			return true;
		}
		return false;

	}

}
