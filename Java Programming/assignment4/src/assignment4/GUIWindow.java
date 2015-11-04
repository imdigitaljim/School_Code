package assignment4;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

public class GUIWindow {
	private JFrame knightApp;
	private JLabel[] inStats;
	private JLabel[] aiStats;
	private JPanel pnlStats;
	private String[] lblNames = { "HP :", "Name :", "Weapon :", "Armor :" };

	private Knight player;
	private Knight computer;
	private static int statCount = 4;
	private boolean hasSelected = false;
	
	GUIWindow() {
		knightApp = new JFrame("KnightFight");
		inStats = new JLabel[statCount * 2]; //label + entry
		aiStats = new JLabel[statCount * 2];
		pnlStats = new JPanel();
		initStatWindow();
	}

	public Knight getUserKnight() {
		player = new Knight(printGetString("What is your Knight's Name?"), 
				selectWeapon(), selectArmor());
		updateStats();
		return player;
	}

	public Knight getAIKnight() {
		hasSelected = true;
		int c = printGetMsg("Would you like to randomize your enemy?", "Enemy Generation");
		if (c == 1) {
			computer = new Knight(printGetString("What is the Knight's Name?"), 
					selectWeapon(), selectArmor());
			updateStats();
			return computer;
		} else if (c == 0) {
			computer = new Knight();
			updateStats();
			return computer;
		}
		System.exit(0);
		return computer;
	}

	private void updateStats() {
		if (hasSelected) {
			aiStats[4].setText(Integer.toString(computer.getHealth()));
			aiStats[5].setText(computer.getName());
			aiStats[6].setText(computer.getWeaponName());
			aiStats[7].setText(computer.getArmorName());
		}
		inStats[4].setText(Integer.toString(player.getHealth()));
		inStats[5].setText(player.getName());
		inStats[6].setText(player.getWeaponName());
		inStats[7].setText(player.getArmorName());
	}

	private int selectWeapon() {
		String[] wpnNames = { "LongSword", "BattleAxe", "Spear", "Warhammer" };
		String prompt = "Choose a weapon!\n"
				+ "LongSword: Strong against Cloth\n"
				+ "BattleAxe: Strong against Leather\n"
				+ "Spear: Strong against Mail\n"
				+ "Warhammer: Strong against Plate";
		return printGetMsg(prompt, "Weapon Select",wpnNames);
	}

	private int selectArmor() {
		String[] armNames = { "Cloth", "Leather", "Mail", "Plate" };
		return printGetMsg("Choose armor!","Armor Select", armNames);
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
			
			//ai portion
			aiStats[i] = new JLabel(lblNames[i], SwingConstants.RIGHT);
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
			pnlStats.add(aiStats[i]);
			pnlStats.add(aiStats[i + 4]);
		}
		knightApp.setVisible(true);
		printMessage("Welcome to Knight Fight!");
	}

	public void beginCombat(Knight user, Knight pc) {
		String[] option = { "Attack", "Flee" };
		//Would you like to fight with these stats
		String a = "Would you like to fight " + pc.getName() + "?";
		if (!(printGetMsg(a,	"Combat Phase") == 0)) {
			return;
		}
		printMessage("The battle begins!");
		Random r = new Random();
		boolean isTurn = r.nextBoolean();
		if (isTurn) {
			printMessage("You get the initiative!");
		} else {
			printMessage(pc.getName() + " gets the initiative!");
		}
		while (user.getHealth() > 0) {
			if (isTurn) {
				// check if continue or quit
				int c = printGetMsg("It is your turn! What will you do?",
						"Your turn",option);
				if (!(c == 0)) {
					return;
				} else {
					// attack
					String s =	"You did " + getCombatDamage(user, pc)
							+ " damage with your " + user.getWeaponName();
					printMessage(s);
					// update panel for user
					updateStats();
					isTurn = false;
				}
			}
			if (!isTurn) {
				// check win condition
				if (pc.getHealth() <= 0) {
					printMessage("You have defeated " + pc.getName() + "!");
					return;
				}
				// begin enemy turn
				printMessage(pc.getName()+ " attacks!");
				// attack
				String s = String.format("%s did %d damage with %s",
						pc.getName(), getCombatDamage(pc, user), pc.getWeaponName());
				printMessage(s);
				// update panel for user
				updateStats();
				isTurn = true;
			}
		}
		printMessage("You died!");
		return;
	}

	private int getCombatDamage(Knight x, Knight y) {
		Random r = new Random();
		int d =  5 + r.nextInt(x.fight()); // base + random
		if (x.getWeaponName() == y.getWeakness()) {
			String s = String.format("%s is weak against %s!", 
					y.getName(), x.getWeaponName());
			printMessage(s);
			d *= 1.5;
		}
		if (r.nextInt(20) == 19) // DND roll 20
		{
			printMessage("Critical Hit!");
			d *= 1.5; // 50% more damage
		}
		y.setHealth(y.getHealth() - d);
		return d;
	}
	public void printMessage(String x)
	{
		JOptionPane.showMessageDialog(knightApp, x);
	}
	
	public int printGetMsg(String x, String y)
	{	
		String[] optionYN = { "Yes", "No" };
		return printGetMsg(x, y, optionYN);
	}
	public int printGetMsg(String x, String y, String[] z)
	{
		return JOptionPane.showOptionDialog(knightApp, x, y,
				JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,
				null, z, null);
	}
	public String printGetString(String x)
	{
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
