package np.com.kushrajrimal;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        int gameOption = 0;
        int gameStatus = 0;
        Scanner input = new Scanner(System.in);
        Board board = new Board();
        board.readRowNum();
        board.readColNum();
        board.initializeCells();

        board.displayBoard();
        while (gameOption != 4) {
            while ((gameOption > 4 || gameOption < 1) && gameStatus == 0) {
                System.out.println("1.Declare Bomb free\n2.Flag as Bomb\n3.Unflag\n4.Quit Game");
                gameOption = input.nextInt();
                if (gameOption < 4 && gameOption > 0) {
                    board.checkCell(gameOption);
                    board.checkGameStatus();
                    if (board.gameStatus == -1)
                        gameStatus = -1;
                    if (board.gameStatus == 1)
                        gameStatus = 1;
                    gameOption = 0;
                    board.displayBoard();
                }
            }
            if (gameStatus == -1) {
                System.out.println("Game Over. Try Again");
                gameOption = 4;
            }
            if (gameStatus == 1) {
                System.out.println("Game Over.Congratulations");
                gameOption = 4;
            }
        }
        board.teardown();

    }
}
