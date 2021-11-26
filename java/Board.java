package np.com.kushrajrimal;

import java.util.Scanner;


public class Board {
    public int rows;
    public int columns;
    public int noOfSteps;
    public int gameStatus;
    public Cell[][] grid;
    public Scanner input = new Scanner(System.in);

    public int getNoOfSteps() {
        return noOfSteps;
    }

    public void setNoOfSteps(int noOfSteps) {
        this.noOfSteps = noOfSteps;
    }

    public int getGameStatus() {
        return gameStatus;
    }

    public void setGameStatus(int gameStatus) {
        this.gameStatus = gameStatus;
    }

    public Cell[][] getGrid() {
        return grid;
    }

    public void setGrid(Cell[][] grid) {
        this.grid = grid;
    }

    public Board() {
        this.rows = 0;
        this.columns = 0;
        this.gameStatus = 0;
        this.noOfSteps = 0;
    }

    public int getRows() {
        return rows;
    }

    public void setRows(int rows) {
        this.rows = rows;
    }

    public int getColumns() {
        return columns;
    }

    public void setColumns(int columns) {
        this.columns = columns;
    }


    public void teardown() {
        System.out.println("Destroying the game");
    }

    public void readRowNum() {
        while (this.rows < 8 || this.rows > 20) {
            System.out.println("Enter the number of rows (8 <= rows >= 20)");
            int rows = input.nextInt();
            setRows(rows);
        }
    }

    public void readColNum() {
        while (this.columns < 8 || this.columns > 20) {
            System.out.println("Enter the number of columns (8 <= columns >= 20)");
            int columns = input.nextInt();
            setColumns(columns);
        }
    }

    public void setBombCount() {

    }

    public void checkCell(int option) {
        int rowNum = -1, colNum = -1;
        while (colNum < 0 || colNum >= this.columns) {
            System.out.println("Enter the column number");
            colNum = input.nextInt();
        }
        while (rowNum < 0 || rowNum >= this.rows) {
            System.out.println("Enter the row number");
            rowNum = input.nextInt();
        }
        if (this.noOfSteps == 0) {
            //1st choice cannot be a bomb, hence
            if (this.grid[rowNum][colNum].bombPresence) {
                this.grid[rowNum][colNum].setBombPresence(false);
                this.countNeighbouringBombs();
            }
        }
        boardUpdate(rowNum, colNum, option);
        this.noOfSteps++;
    }


    private void boardUpdate(int x, int y, int action) //Function Defination, updates the board.
    {
        if (action == 2) {
            if (this.grid[x][y].flagged) {
                System.out.println("\nIt already marked as bomb\n");
            } else {
                this.grid[x][y].flagged = true;
                System.out.println("\nMarked as bomb\n");
            }
        }
        if (action == 3) {
            if (!this.grid[x][y].flagged) {
                System.out.println("\nIt already unmarked as bomb\n");
            } else {
                this.grid[x][y].flagged = false;
                System.out.println("\nUnmarked as bomb\n");
            }
        }
        if (action == 1) {
            if (this.grid[x][y].flagged) {
                System.out.println("\nPLease unflag bomb before assertion\n");
            } else {
                if (this.grid[x][y].bombPresence) {
                    this.setGameStatus(-1);
                    System.out.println("\nBoom. Game Over\n");
                } else {
                    System.out.println("\nOk\n");
                    this.grid[x][y].revealed = true;
                    if (this.grid[x][y].neighbouringBombs == 0) {
                        revealMyNeighbours(x, y);
                        resetTraversalStatus();
                    }
                }
            }
        }
    }

    private void resetTraversalStatus() {
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                this.grid[i][j].traversed = false;
            }
        }
    }

    private void revealMyNeighbours(int x, int y) {
        if (this.grid[x][y].traversed) return;
        this.grid[x][y].revealed = true;
        this.grid[x][y].traversed = true;
        if (!this.grid[x][y].bombPresence && !this.grid[x][y].flagged && this.grid[x][y].neighbouringBombs == 0) {
            if (x > 0) {
                revealMyNeighbours(x - 1, y);
                if (y > 0) {
                    revealMyNeighbours(x - 1, y - 1);
                }
                if (y < this.rows - 1) {
                    revealMyNeighbours(x - 1, y + 1);
                }
            }
            if (x < this.columns - 1) {
                revealMyNeighbours(x + 1, y);
                if (y < this.rows - 1) {
                    revealMyNeighbours(x + 1, y + 1);
                }
                if (y > 0) {
                    revealMyNeighbours(x + 1, y - 1);
                }
            }
            if (y > 0) {
                revealMyNeighbours(x, y - 1);
            }
            if (y < this.rows - 1) {
                revealMyNeighbours(x, y + 1);
            }

        }

    }


    public void initializeCells() {

        Cell[][] grid = new Cell[rows][columns];
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                grid[i][j] = new Cell(i, j);
            }
        }

        this.setGrid(grid);
        this.setBombs();
        this.countNeighbouringBombs();
    }

    public void displayBoard() {
        System.out.println("\n");
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                if (this.grid[i][j].bombPresence && this.gameStatus == -1) {
                    System.out.print("  *  ");
                } else {
                    if (this.grid[i][j].flagged) {
                        System.out.print("  F   ");
                    } else {
                        if (!this.grid[i][j].revealed) {
                            System.out.print(" [ ] ");
                        } else {
                            System.out.print("  " + this.grid[i][j].neighbouringBombs + "  ");
                        }
                    }
                }
            }
            System.out.println("\n");
        }
    }

    public void setBombs() {
        int noOfBombs = (this.rows * this.columns) / 4;
        int bombArray[] = new int[noOfBombs];
        for (int i = 0; i < noOfBombs; i++) {
            int num = (int) (Math.random() * (this.rows * this.columns - 0 + 1) + 0);
            bombArray[i] = num;
        }
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                for (int k = 0; k < noOfBombs; k++) {
                    if (bombArray[k] == (this.rows * j) + i) {
                        this.grid[i][j].bombPresence = true;
                        break;
                    }
                }
            }
        }
    }

    private void countNeighbouringBombs() {
        int count;
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                count = 0;
                if (j > 0 && i < (this.rows - 1)) {
                    if (this.grid[i + 1][j - 1].bombPresence) {
                        count = count + 1;
                    }
                }
                if (i < (this.rows - 1)) {
                    if (this.grid[i + 1][j].bombPresence) {
                        count = count + 1;
                    }
                    if (j < (this.columns - 1)) {
                        if (this.grid[i + 1][j + 1].bombPresence) {
                            count = count + 1;
                        }
                    }
                }
                if (j > 0) {
                    if (this.grid[i][j - 1].bombPresence) {
                        count = count + 1;
                    }
                }
                if (j < (this.columns - 1)) {
                    if (this.grid[i][j + 1].bombPresence) {
                        count = count + 1;
                    }
                }
                if (i > 0) {
                    if (j > 0) {
                        if (this.grid[i - 1][j - 1].bombPresence) {
                            count = count + 1;
                        }
                    }
                    if (j < (this.columns - 1)) {
                        if (this.grid[i - 1][j + 1].bombPresence) {
                            count = count + 1;
                        }
                    }
                    if (this.grid[i - 1][j].bombPresence) {
                        count = count + 1;
                    }
                }
                this.grid[i][j].neighbouringBombs = count;
            }
        }
    }

    public void checkGameStatus() {
        int bombCount = 0;
        int flaggedBombs = 0;
        int revealedCount = 0;
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                if (this.grid[i][j].bombPresence) {
                    bombCount++;
                    if (this.grid[i][j].flagged) {
                        flaggedBombs++;
                    }
                } else {
                    if (this.grid[i][j].revealed) {
                        revealedCount++;
                    }
                }

            }
        }
        int nonBombCount = (this.rows * this.columns) - bombCount;
        if (nonBombCount == revealedCount || bombCount == flaggedBombs) {
            this.setGameStatus(1);
        }
    }


}
