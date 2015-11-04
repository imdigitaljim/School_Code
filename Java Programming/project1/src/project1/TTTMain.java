package project1;
/*
Bach, James
COP-3252
Project 1
2/8/2015

Reference: 
http://docs.oracle.com/
--Team Pictures (before modifications)
http://en.wikipedia.org/wiki/Florida_State_Seminoles#mediaviewer/File:FSU_Seminoles.svg
http://en.wikipedia.org/wiki/Florida_Gators#mediaviewer/File:Florida_Gators_logo.svg
https://www.fsu.edu/.element/img/4.0/fsuLogo8.png
*/

import java.util.Random;
import javax.swing.ImageIcon;

public class TTTMain {
	private int[] matrixMoves = new int[9];
	// 0 1 2
	// 3 4 5  <-- these are the index references for the board
	// 6 7 8
	private int[] windex = { 12, 345, 678, 36, 147, 258, 48, 246 };
	//these are the possible winning scenarios 
	// 0 1 2  <-- 012 windex[0]
	// 3 4 5  <-- 345 windex[1]
	// 6 7 8  <-- 678 windex[2]
	// ^ ^ ^ 048 windex[6] and 0246 windex[7] other diagonal
	// ^ ^ 258 windex[5]
	// ^ 147 windex[4]
	// 036 windex[3] 
	private GUIWindow gui;
	private int[] winCondMtxTotal = new int[8];

	private XOObject x, o, turn, opp;
	public int movesRemain;
	public static boolean newGame, aiEnabled;
	public static int p1WinCount, p2WinCount, p2LossCount, p1LossCount;

	TTTMain() {
		gui = new GUIWindow(this);
		aiEnabled = true;
	}

	//getters and setters
	public int getWinCondMtxTotal(int i) {
		return winCondMtxTotal[i];
	}
	public boolean getAIEnabled() {
		return aiEnabled;
	}

	public boolean getNewGame() {
		return newGame;
	}

	public void setNewGame(boolean b) {
		newGame = b;
	}

	public XOObject getTurn() {
		return turn;
	}

	public XOObject getOpp() {
		return opp;
	}

	public void setXOWinnable(int index, boolean val) {
		x.isWinnable[index] = val;
		o.isWinnable[index] = val;
	}
	
	//used by GUI
	public int getHighVal() {
		return opp.getHighestMatchVal();
	}
	
	public void resetStats() {
		p1WinCount = 0;
		p1LossCount = 0;
		p2WinCount = 0;
		p2LossCount = 0;
	}
	
	//setup up a new game
	public void newGame() {
		x = new XOObject('x', this);
		o = new XOObject('o', this);
		gui.setScores();
		x.setImage(gui.getXSkin());
		o.setImage(gui.getOSkin());
		x.setXO(gui.getTeamSet()[0]);
		o.setXO(gui.getTeamSet()[1]);
		if (aiEnabled) {
			if (gui.playerIsX()) {
				o.setAIEnabled(true);
			} else {
				x.setAIEnabled(true);
			}
		}
		for (int i = 0; i < 9; i++) {
			gui.setOption(i, null);
			if (i < 8) {
				setXOWinnable(i, true);
			}
		}
		matrixMoves = new int[9];
		movesRemain = 9;
		newGame = false;
		turn = x;
		opp = o;
		if (turn.isAIEnabled()) {
			computerMove();
		}
	}

	//checks if NewGame has been initiated
	public void checkNew() {
		if (newGame) {
			newGame();
		} else if (turn.isAIEnabled()) {

			computerMove();
			if (newGame) {
				newGame();
			}
		}
	}

	//attempts to set new move
	public void setMove(int m) {
		if (matrixMoves[m] == 0) {
			matrixMoves[m] = turn.getMatrixVal();
			gui.setOption(m, new ImageIcon(turn.getImage()));
			--movesRemain;
			switchTurn(turn);
			if (isWinCondition() || movesRemain == 0) {
				if (x.getHighestMatchVal() == 3 || o.getHighestMatchVal() == 3) {
					updateScores();
				}
				gui.restart();
			}
		}
	}

	//update the scoreboard
	private void updateScores() {
		// single player
		if (turn.isAIEnabled()) {
			p1WinCount++;
		} else if (opp.isAIEnabled()) {
			p1LossCount++;
		}
		// multi-player
		else if (gui.playerIsX() && x == turn) {
			p1LossCount++;
			p2WinCount++;
		} else {
			p1WinCount++;
			p2LossCount++;
		}
	}

	//flip flop turns
	private void switchTurn(XOObject m) {
		turn = opp;
		opp = m;
	}

	
	public void computerMove() {
		Random r = new Random();
		XOObject myturn = turn;
		int select;
		// if impossible always make the best move (== 2)
		// hard has a 25% chance to make the best possible
		//  move otherwise random
		if (gui.getDifficulty() == 2
				|| (r.nextInt(2) * r.nextInt(2) * gui.getDifficulty()) % 2 != 0) {
			select = getBestMove();
		} else {
			select = r.nextInt(9);
		}
		while (myturn == turn) {
			//stay here until a valid turn has been found
			//doesnt get trapped because it is caught in 
			//the method below
			setMove(select);
			select = r.nextInt(9);
		}
	}

	public boolean isWinCondition() {
		if (checkConditions() == 3 || movesRemain == 0) {
			return true;
		}
		if (x.isMoveUpdateNeeded() || o.isMoveUpdateNeeded()) {
			checkConditions();
		}
		return false;
	}



	public int checkConditions() {
		int indexer, highestNum = 0;
		for (int i = 0; i < 8; i++) {
			//get the current line
			int temp = windex[i];
			winCondMtxTotal[i] = 0;
			for (int j = 0; j < 3; j++) {
				//get the 
				indexer = temp % 10;
				temp /= 10;
				//if both x/y are on same line winnable for that line set false
				if (Math.abs(winCondMtxTotal[i] + matrixMoves[indexer]) < Math
						.abs(winCondMtxTotal[i]) && (x.isWinnable[i] || o.isWinnable[i])) {
					setXOWinnable(i, false);
				}
				winCondMtxTotal[i] += matrixMoves[indexer];
			}
			//if 1 or -1 the opponent cannot win that line
			if (winCondMtxTotal[i] < 0) {
				x.isWinnable[i] = false;
			} else if (winCondMtxTotal[i] > 0) {
				o.isWinnable[i] = false;
			}
			if (highestNum < Math.abs(winCondMtxTotal[i])) {
				highestNum = Math.abs(winCondMtxTotal[i]);
			}
			x.updateBestMatch(i);
			o.updateBestMatch(i);
		}
		return highestNum;
	}

	public int getBestMove() {
		// if the middle is open take it
		if (matrixMoves[4] == 0) {
			return 4;
		}
		// if a block is necessary take it
		if (opp.getHighestMatchVal() == 2 && turn.getHighestMatchVal() < 2) {
			int temp = windex[opp.getBestMove()];
			for (int i = 0; i < 3; i++) {
				if (matrixMoves[temp % 10] == 0) {
					return temp % 10;
				}
				temp /= 10;
			}
		}
		// collect the possible "best moves"
		int temp = windex[turn.getBestMove()];
		int[] possible = { -1, -1, -1 };
		for (int i = 0; i < 3; i++) {
			if (matrixMoves[temp % 10] == 0) {
				possible[i] = temp % 10;
			}
			temp /= 10;
		}

		// possible corner best
		for (int i = 0; i < 3; i++) {
			if (possible[i] % 2 == 0) {
				return possible[i];
			}
		}
		// select the next best
		for (int i = 0; i < 3; i++) {
			if (possible[i] > 0) {
				return possible[i];
			}
		}
		// find whatever is left
		int remaining = 0;
		for (int i = 0; i < 8; i++) {
			if (matrixMoves[i] == 0) {
				remaining = i;
			}
		}
		return remaining;
	}

}
