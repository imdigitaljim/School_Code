package project1;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.WindowConstants;

public class GUIWindow implements ActionListener, MouseListener {
	private JFrame window;
	private JPanel mainPanel, menuPanel;
	private JPanel[] matrix;
	private JLabel[] option;
	private JLabel logoLBL, nameLBL, p1Stats, p2Stats;
	private JMenuBar menuBar;
	private JMenu mFile, mOptions, mDiff, mAbout;
	private JMenuItem nextGame, reset, exit, info;
	private JRadioButtonMenuItem p1, p2, hx, ho, easy, hard, impossible, plain, fsu;
	private ButtonGroup pCount, xoSelect, diffSel, xoSkin;
	private Color garnet = new Color(120, 47, 64);
	private Color gold = new Color(206, 184, 136);
	private TTTMain game;
	private BufferedImage fsux, fsuo, plainx, plaino, fsuicon, fsutitle, nametitle;

	public int processMove(Object click) {
		for (int i = 0; i < 9; i++) {
			if (click == matrix[i]) {
				game.setMove(i);
			}
		}
		return 0;
	}

	public void setOption(int i, ImageIcon img) {
		option[i].setIcon(img);
	}

	public JPanel getMatrix(int i) {
		return matrix[i];
	}

	GUIWindow(TTTMain g) {
		game = g;
		window = new JFrame("Tic Tac Toe");
		mainPanel = new JPanel();
		matrix = new JPanel[9];
		option = new JLabel[9];
		try {
			fsuicon = ImageIO.read(getClass().getResource("images/fsuicon.png"));
			fsux = ImageIO.read(getClass().getResource("images/fsu.png"));
			fsuo = ImageIO.read(getClass().getResource("images/ufo.png"));
			plainx = ImageIO.read(getClass().getResource("images/plainx.png"));
			plaino = ImageIO.read(getClass().getResource("images/plaino.png"));
			fsutitle = ImageIO.read(getClass().getResource("images/fsutitle2.png"));
			nametitle = ImageIO.read(getClass().getResource("images/nametitle.png"));

		} catch (IOException ex) {
			printMessage("Pictures Failed to Load");
		}
		initWindow();
		window.setVisible(true);
	}

	private void setJLabel(JLabel jl, int sizex, int sizey, int locx, int locy) {
		mainPanel.add(jl);
		jl.setVisible(true);
		jl.setLocation(locx, locy);
		jl.setSize(sizex, sizey);
	}

	private void initWindow() {
		window.setIconImage(fsuicon);
		window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		window.setResizable(false);
		window.setLocation(400, 400);
		window.setSize(400, 600);
		window.setLayout(null);
		window.add(mainPanel);
		mainPanel.setSize(395, 570);
		mainPanel.setLayout(null);
		mainPanel.setBackground(garnet);
		mainPanel.setBorder(BorderFactory.createLineBorder(gold, 10));

		logoLBL = new JLabel(new ImageIcon(fsutitle));
		setJLabel(logoLBL, 372, 35, 10, 30);

		nameLBL = new JLabel(new ImageIcon(nametitle));
		nameLBL.setBorder(BorderFactory.createLineBorder(gold, 5));
		setJLabel(nameLBL, 400, 55, 0, 510);

		p1Stats = new JLabel();
		setJLabel(p1Stats, 150, 50, 20, 470);

		p2Stats = new JLabel();
		setJLabel(p2Stats, 150, 50, 225, 470);

		buildGridPanel();
		buildMenuPanel();
	}

	public void buildGridPanel() {
		int locY = 100, locX = 22;
		for (int i = 0; i < matrix.length; i++) {
			if (i > 0 && i % 3 == 0) {
				locX = 22;
				locY += 125;
			}
			matrix[i] = new JPanel();
			option[i] = new JLabel();
			matrix[i].add(option[i]);
			mainPanel.add(matrix[i]);
			matrix[i].setBackground(gold);
			matrix[i].setVisible(true);
			matrix[i].setSize(100, 100);
			matrix[i].addMouseListener(this);
			matrix[i].setLocation(locX, locY);
			locX += 125;
		}
	}

	public void buildMenuPanel() {
		// Menu
		menuBar = new JMenuBar();

		menuPanel = new JPanel();
		menuPanel.setLayout(new BorderLayout());
		menuPanel.add(menuBar, BorderLayout.NORTH);
		menuPanel.setVisible(true);
		menuPanel.setSize(400, 20);
		mainPanel.add(menuPanel);

		// File
		mFile = new JMenu("File");
		mFile.setMnemonic(KeyEvent.VK_F);
		menuBar.add(mFile);

		nextGame = new JMenuItem("New Game");
		nextGame.addActionListener(this);
		mFile.add(nextGame);

		reset = new JMenuItem("Reset Score");
		reset.addActionListener(this);
		mFile.add(reset);

		exit = new JMenuItem("Exit");
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		mFile.add(exit);

		// Options
		mOptions = new JMenu("Game Options");
		mOptions.setMnemonic(KeyEvent.VK_O);
		menuBar.add(mOptions);

		// 1P 2P Selection RADIO--------------------
		pCount = new ButtonGroup();

		p1 = new JRadioButtonMenuItem("1 Player - Play against the computer");
		p1.addActionListener(this);
		p1.setSelected(true);
		pCount.add(p1);
		mOptions.add(p1);

		p2 = new JRadioButtonMenuItem("2 Player - Play with a friend");
		p2.addActionListener(this);
		pCount.add(p2);
		mOptions.add(p2);

		mOptions.addSeparator();
		// Player X O Selection RADIO--------------------
		xoSelect = new ButtonGroup();

		hx = new JRadioButtonMenuItem("Player 1 : X   - -   Player 2 : O");
		hx.addActionListener(this);
		hx.setSelected(true);
		xoSelect.add(hx);
		mOptions.add(hx);

		ho = new JRadioButtonMenuItem("Player 1 : O   - -   Player 2 : X");
		ho.addActionListener(this);

		xoSelect.add(ho);
		mOptions.add(ho);

		mOptions.addSeparator();

		// Player Skin Selection RADIO--------------------
		xoSkin = new ButtonGroup();

		plain = new JRadioButtonMenuItem("Traditional");
		plain.addActionListener(this);
		plain.setSelected(true);
		xoSkin.add(plain);
		mOptions.add(plain);

		fsu = new JRadioButtonMenuItem("FSU vs UF");
		fsu.addActionListener(this);
		xoSkin.add(fsu);
		mOptions.add(fsu);

		// Difficulty Selection
		mDiff = new JMenu("Difficulty");
		mDiff.setMnemonic(KeyEvent.VK_D);
		menuBar.add(mDiff);

		// Difficulty Selection Items
		diffSel = new ButtonGroup();

		easy = new JRadioButtonMenuItem("Easy");
		easy.setSelected(true);
		easy.addActionListener(this);
		diffSel.add(easy);
		mDiff.add(easy);

		hard = new JRadioButtonMenuItem("Hard");
		hard.addActionListener(this);
		diffSel.add(hard);
		mDiff.add(hard);

		impossible = new JRadioButtonMenuItem("Impossible");
		impossible.addActionListener(this);
		diffSel.add(impossible);
		mDiff.add(impossible);

		// About
		mAbout = new JMenu("About");
		mAbout.setMnemonic(KeyEvent.VK_A);
		menuBar.add(mAbout);

		info = new JMenuItem("About Me");
		info.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				printMessage("Tic Tac Toe\nCOP3252 Project 1\nJames Bach");
			}
		});
		mAbout.add(info);
	}

	public String[] getTeamSet() {
		String[] team = new String[2];
		if (plain.isSelected()) {
			team[0] = "X WINS!";
			team[1] = "O WINS!";
		} else {
			team[0] = "SEMINOLES WIN!";
			team[1] = "GATORS WIN!";
		}
		return team;
	}

	public BufferedImage getXSkin() {
		if (plain.isSelected()) {
			return plainx;
		}
		return fsux;
	}

	public BufferedImage getOSkin() {
		if (plain.isSelected()) {
			return plaino;
		}
		return fsuo;
	}
	
	public int getDifficulty() {
		if (easy.isSelected()) {
			return 0;
		} else if (hard.isSelected()) {
			return 1;
		} else {
			return 2;
		}
	}
	public void setScores() {
		p1Stats.setForeground(Color.white);
		p2Stats.setForeground(Color.white);
		p1Stats.setText("Player 1| Wins: " + TTTMain.p1WinCount + "  Loss: " + TTTMain.p1LossCount);
		p2Stats.setText("Player 2| Wins: " + TTTMain.p2WinCount + "  Loss: " + TTTMain.p2LossCount);

		if (p1.isSelected()) {
			TTTMain.aiEnabled = true;
			p2Stats.setVisible(false);
		} else if (p2.isSelected()) {
			TTTMain.aiEnabled = false;
			p2Stats.setVisible(true);
		}
	}

	public boolean playerIsX() {
		return hx.isSelected();
	}

	//interfaces for mouselistener and actionlistener
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == reset || e.getSource() == p1 || e.getSource() == p2) {
			game.resetStats();
		}
		game.newGame();
	}
	
	public void mouseClicked(MouseEvent e) {
	}

	public void mouseEntered(MouseEvent e) {
	}

	public void mouseExited(MouseEvent e) {
	}

	public void mouseReleased(MouseEvent e) {
	}

	public void mousePressed(MouseEvent e) {
		if (game.movesRemain > 0) {
			processMove(e.getSource());
			game.checkNew();
		}
	}

	public void printMessage(String x) {
		JOptionPane.showMessageDialog(window, x);
	}

	public int printGetMsg(String x, String y) {
		String[] optionYN = { "Yes", "No" };
		return printGetMsg(x, y, optionYN);
	}

	public int printGetMsg(String x, String y, String[] z) {
		return JOptionPane.showOptionDialog(window, x, y, JOptionPane.YES_NO_CANCEL_OPTION,
				JOptionPane.QUESTION_MESSAGE, null, z, null);
	}

	public String getWinner() {
		if (game.getHighVal() == 3) {
			return game.getOpp().getXO();
		} else {
			return "Cat Game!";
		}
	}

	public void restart() {

		if (printGetMsg(getWinner() + "\nWould you like to restart?", "The End") == 0) {
			game.setNewGame(true);
			return;
		}
		System.exit(0);

	}
}
