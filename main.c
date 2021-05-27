// @author::: Kush Raj Rimal
// @FileName: Minesweeper.c
// Date:::::: 02/23/2020
#include<stdio.h>
#include<stdlib.h>
//global variables.
int rowsize, colsize;
int maxboardsize=15;
int minboardsize=6;
char yourInput;	   /* variable initialization for user's input.	*/
int step=0;
int blasted=0;
typedef struct
{
    int bombPresence;
    int revealed;
    int flagged;
    int neighbouringBombs;
    int traversed;
} Cell;
Cell **gameBoard;

int checkGameStatus();
void resetTraversalStatus();
void revealMyNeighbours(int rownum, int colnum);
void initialization();
void gridSizeSetup();
void teardown();
char userValidation();
void acceptInput(char yourInput);
void boardUpdate(int rownum, int colnum, char action);
void display();
void xyCoordinate();
int number();
int getNumericInput(int min, int max);
void initializeGameBoard();
void setBombs();
void countNeighbouringBombs();
void gridSizeSetup(){
    char response;
    while(response != 'y' && response != 'Y' &&  response != 'n' && response != 'N')
    {
        printf("Do you want to customize board size? A defult of %d x %d will be used.(Y/N)\n",minboardsize,minboardsize);
        scanf("%c",&response);
    }
    if(response == 'Y' || response == 'y'){
        printf("Enter the row size( %d < and < %d)",minboardsize,maxboardsize);
        rowsize = getNumericInput(minboardsize, maxboardsize);
        printf("Enter the column size( %d < and < %d)",minboardsize,maxboardsize);
        colsize = getNumericInput(minboardsize, maxboardsize);
    }
    else{
        colsize=minboardsize;
        rowsize=minboardsize;
    }
    initializeGameBoard(colsize, rowsize);
}

int getNumericInput(int min, int max)
{
    int number;
    scanf(" %d", &number);
    while ( (number > max || number < min) )
    {
        printf("enter number within valid range \n");
        scanf(" %d", &number);
    }
    return number;
}

void initializeGameBoard(width,height){
    gameBoard =malloc(sizeof(Cell*) * rowsize);
    for (int i=0 ; i < rowsize; i++){
        gameBoard[i]= malloc(sizeof(Cell) * colsize);
    }
    for(int i=0; i < rowsize; i++){
        for(int j=0; j < colsize; j++){
            gameBoard[i][j].revealed=0;
            gameBoard[i][j].flagged=0;
            gameBoard[i][j].bombPresence=0;
            gameBoard[i][j].traversed=0;
        }
    }
    setBombs();
}

void setBombs(){
    int noOfBombs= (colsize * rowsize) / 4 ;
    int bombArray[noOfBombs];
    for (int i = 0; i < noOfBombs; i++) {
        int num = (rand() %  ((colsize * rowsize - 1) - 0 + 1)) + 0;
        bombArray[i]=num;
    }
    for(int i=0; i < rowsize; i++){
        for(int j=0; j < colsize; j++){
            for(int k = 0; k < noOfBombs; k++)
            {
                if(bombArray[k] == (rowsize * j) + i ) {
                    gameBoard[i][j].bombPresence = 1;
                    break;
                }
            }
        }
    }
}

void countNeighbouringBombs(){
    int count;
    for(int i=0; i < rowsize; i++){
        for(int j=0; j < colsize; j++){
            count=0;
            if(j>0 && i < (rowsize - 1)) {
                if (gameBoard[i + 1][j - 1].bombPresence == 1) {
                    count = count + 1;
                }
            }
            if(i< (rowsize - 1)) {
                if (gameBoard[i + 1][j].bombPresence == 1) {
                    count = count + 1;
                }
                if(j< (colsize - 1)) {
                    if (gameBoard[i + 1][j + 1].bombPresence == 1) {
                        count = count + 1;
                    }
                }
            }
            if(j > 0) {
                if (gameBoard[i][j - 1].bombPresence == 1) {
                    count = count + 1;
                }
            }
            if(j< (colsize - 1)) {
                if (gameBoard[i][j + 1].bombPresence == 1) {
                    count = count + 1;
                }
            }
            if(i>0) {
                if(j>0) {
                    if (gameBoard[i - 1][j - 1].bombPresence == 1) {
                        count = count + 1;
                    }
                }
                if(j< (colsize - 1)) {
                    if (gameBoard[i - 1][j + 1].bombPresence == 1) {
                        count = count + 1;
                    }
                }
                if (gameBoard[i - 1][j].bombPresence == 1) {
                    count = count + 1;
                }
            }
            gameBoard[i][j].neighbouringBombs=count;
        }
    }
}

void initialization() /*starting the game*/
{
    printf("Setting up the game\n");
}

void teardown() /*ending the game*/
{
    printf("Destroying the game\n");
    free(gameBoard);
    exit(1);     /*terminates the calling process immediately.*/
}

char userValidation() /*checks if user inputs the instructed variables F, R, A and Q and if the input is correct returns the input to acceptInput function*/
{
    char input;
    printf("please enter your input\n");
    scanf(" %c", &input);
    while(input != 'F' && input != 'f' &&  input != 'R' && input != 'r' && input != 'A' && input != 'a' && input != 'Q' && input != 'q' )
    {
        printf("Please enter valid input\n");
        scanf(" %c", &input);
    }
    return input;
}

void acceptInput(char input)        /* accepting input in both uppercase and lowercase for letters */
{
    if ((input == 'F') || (input == 'f') || (input == 'R') || (input == 'r') || (input == 'A') || (input == 'a')){
        xyCoordinate(input);  	       /* passes the control to xyCoordinate function */
    }
    else if ((input == 'Q') || (input == 'q')){
        teardown();	/* passes the control to teardown function */
    }
}

void xyCoordinate(action) /*Function Defination:: to check if user have submitted correct coordinate*/
{
    int rownum, colnum;
    printf("Enter the row number(1- %d)\n", rowsize);
    rownum =getNumericInput(1, rowsize);
    printf("Enter the column number(1 - %d)\n", colsize);
    colnum = getNumericInput(1, colsize);
    boardUpdate(rownum, colnum,action); // passes the coordinate to boardUpdate function
}

void boardUpdate(int rownum, int colnum, char action) //Function Defination, updates the board.
{
    if(action == 'f' || action == 'F'){
        if(gameBoard[rownum - 1][colnum - 1].flagged == 1){
            printf("\nIt already marked as bomb\n");
        }
        else {
            gameBoard[rownum - 1][colnum - 1].flagged = 1;
            printf("\nMarked as bomb\n");
        }
    }
    if(action == 'r' || action == 'R'){
        if(gameBoard[rownum - 1][colnum - 1].flagged == 0){
            printf("\nIt already unmarked as bomb\n");
        }
        else {
            gameBoard[rownum - 1][colnum - 1].flagged = 0;
            printf("\nUnmarked as bomb\n");
        }
    }
    if(action=='A' || action =='a'){
        if(gameBoard[rownum - 1][colnum - 1].flagged == 1){
            printf("\nPlease unflag bomb before assertion\n");
        }
        else {
            if (gameBoard[rownum - 1][colnum - 1].bombPresence == 1 && step > 1) {
                blasted = 1;
                printf("\nBoom. Game Over\n");
            } else {
                if(step == 1){
                    gameBoard[rownum - 1][colnum - 1].bombPresence = 0;
                    countNeighbouringBombs();
                }
                printf("\nOk\n");
                gameBoard[rownum - 1][colnum - 1].revealed = 1;
                if (gameBoard[rownum - 1][colnum - 1].neighbouringBombs == 0) {
                    revealMyNeighbours(rownum - 1, colnum - 1);
                    resetTraversalStatus();
                }
            }
        }
    }
}
void resetTraversalStatus(){
    for(int i=0; i < rowsize; i++){
        for(int j=0; j < colsize; j++){
            gameBoard[i][j].traversed=0;
        }
    }
}

void revealMyNeighbours(int rownum, int colnum){
    if(gameBoard[rownum][colnum].traversed == 1  ) return;
    gameBoard[rownum][colnum].revealed = 1;
    gameBoard[rownum][colnum].traversed = 1;
    if (gameBoard[rownum][colnum].bombPresence == 0 && gameBoard[rownum][colnum].flagged == 0 && gameBoard[rownum][colnum].neighbouringBombs == 0) {
        if (rownum > 0) {
            revealMyNeighbours(rownum - 1, colnum);
            if (colnum > 0) {
                revealMyNeighbours(rownum - 1, colnum - 1);
            }
            if (colnum < colsize - 1) {
                revealMyNeighbours(rownum - 1, colnum + 1);
            }
        }
        if (rownum < rowsize - 1) {
            revealMyNeighbours(rownum + 1, colnum);
            if (colnum < colsize - 1) {
                revealMyNeighbours(rownum + 1, colnum + 1);
            }
            if (colnum > 0) {
                revealMyNeighbours(rownum + 1, colnum - 1);
            }
        }
        if (colnum > 0) {
            revealMyNeighbours(rownum, colnum - 1);
        }
        if (colnum < colsize - 1) {
            revealMyNeighbours(rownum, colnum + 1);
        }
    }
}

void  display() //Function Defination
{
    printf("Step %d display, \n",step);
    int gameWon=0;
    if(blasted == 0) {
        gameWon = checkGameStatus();
    }
    for(int i=0; i < rowsize; i++){
        for(int j=0; j < colsize; j++){
            if(gameBoard[i][j].bombPresence == 1 && blasted==1){
                printf(" *  ");
            }
            else {
                if (gameBoard[i][j].flagged == 1) {
                    printf(" F  ");
                } else {
                    if (gameBoard[i][j].revealed == 0) {
                        printf(" [] ");
                    } else {
                        printf("%2d  ", gameBoard[i][j].neighbouringBombs);
                    }
                }
            }
        }
        printf("\n");
    }
    if(blasted == 1 || gameWon == 1){
        teardown();
    }
}
int checkGameStatus(){
    int bombCount=0;
    int flaggedBombs=0;
    int revealedCount=0;
    for(int i=0; i < rowsize; i++){
        for(int j=0; j < colsize; j++) {
            if(gameBoard[i][j].bombPresence == 1){
                bombCount++;
                if(gameBoard[i][j].flagged == 1){
                    flaggedBombs++;
                }
            }
            else{
                if(gameBoard[i][j].revealed == 1){
                    revealedCount++;
                }
            }
        }
    }
    int nonBombCount= (colsize * rowsize) - bombCount;
    if(nonBombCount == revealedCount || bombCount == flaggedBombs){
        printf("Congratuations, You won. Game Over \n");
        return 1;
    }
    return 0;
}
// main function where all the necessary function are called
int main ()
{
    initialization(); // Function Call
    gridSizeSetup();
    step=0;
    do{
        step++;
        printf("(F) flag a spot as a mine, (R) remove a flag, (A) assert that a spot is mine free, (Q)uit\n");// giving Users option
        yourInput =userValidation(); // input from user is passed to userValidation function to check whether the user used correct letters or not.
        acceptInput(yourInput);   // passes the control to xyCoordinate function if input is F,A or R and if input is 'Q', passes to Teardown function.
        display();	  //displays the board
    }
    while((yourInput != 'Q' || yourInput != 'q'));
    teardown();   //Function Call
    return 0;
}
