package np.com.kushrajrimal;

public class Cell {
    public int rowNum;
    public int colNum;
    public boolean flagged;
    public boolean traversed;
    public boolean bombPresence;
    public boolean revealed;
    public int neighbouringBombs;

    public Cell(int rowNum, int colNum) {
        this.rowNum = rowNum;
        this.colNum = colNum;
        this.flagged = false;
        this.traversed = false;
        this.bombPresence = false;
        this.revealed = false;
        this.neighbouringBombs = 0;
    }

    public boolean isFlagged() {
        return flagged;
    }

    public void setFlagged(boolean flagged) {
        this.flagged = flagged;
    }

    public boolean isTraversed() {
        return traversed;
    }

    public void setTraversed(boolean traversed) {
        this.traversed = traversed;
    }

    public boolean isBombPresence() {
        return bombPresence;
    }

    public void setBombPresence(boolean bombPresence) {
        this.bombPresence = bombPresence;
    }

    public boolean isRevealed() {
        return revealed;
    }

    public void setRevealed(boolean revealed) {
        this.revealed = revealed;
    }

    public int getNeighbouringBombs() {
        return neighbouringBombs;
    }

    public void setNeighbouringBombs(int neighbouringBombs) {
        this.neighbouringBombs = neighbouringBombs;
    }

    public int getRowNum() {
        return rowNum;
    }

    public void setRowNum(int rowNum) {
        this.rowNum = rowNum;
    }

    public int getColNum() {
        return colNum;
    }

    public void setColNum(int colNum) {
        this.colNum = colNum;
    }
}
