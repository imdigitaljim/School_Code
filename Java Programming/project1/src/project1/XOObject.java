package project1;

import java.awt.image.BufferedImage;

public class XOObject {
	private BufferedImage image;
	private boolean allowFindMatch;
	private TTTMain game;
	private boolean isAI;
	private String xo;
	private int bestMove, highestMatchVal, matrixVal;
	public boolean[] isWinnable;

	XOObject(char c, TTTMain g) {
		game = g;
		isAI = false;
		bestMove = 0;
		highestMatchVal = 0;
		isWinnable = new boolean[8];
		allowFindMatch = true;

		//used to differentiate mathematically
		if (c == 'x') {
			matrixVal = 1;
		} else {
			matrixVal = -1;
		}
	}
	//getters and setters
	public BufferedImage getImage() {
		return image;
	}

	public int getBestMove() {
		return bestMove;
	}

	public int getHighestMatchVal() {
		return highestMatchVal;
	}

	public int getMatrixVal() {
		return matrixVal;
	}

	public void setXO(String s) {
		xo = s;
	}

	public String getXO() {
		return xo;
	}

	public void setImage(BufferedImage img) {
		image = img;
	}

	public void setAIEnabled(boolean b) {
		isAI = b;
	}

	public boolean isAIEnabled() {
		return isAI;
	}
	
	public void updateBestMatch(int i) {
		if (Math.abs(game.getWinCondMtxTotal(i)) > highestMatchVal && isWinnable[i]) {
			highestMatchVal = Math.abs(game.getWinCondMtxTotal(i));
			bestMove = i;
			allowFindMatch = true;
		}
	}
	public boolean isMoveUpdateNeeded() {
		if (!isWinnable[bestMove] && game.movesRemain < 8) {
			if (allowFindMatch) {
				highestMatchVal = 0;
				bestMove = 0;
				allowFindMatch = false;
				return true;
			}
		}
		return false;
	}
}
