//
// Author: Jue Wang
//

#include "liblab8part2.h"
#include "lab8part2.h"

#include "stdio.h"

// Functions - prototype:

void initializeBoard(char board[][26], int n); // done

void printBoard(char board[][26], int n); // done

int makeMove(const char board[][26], int n, char turn, int *row, int *col); /* Included */ // done

  bool isInDeadArea(const char board[][26], int n, int rowNum, int colNum); /* Included */ // done

  bool isInEdges(int n, int rowNum, int colNum); /* Included */ // done

  bool isInCorner(int n, int rowNum, int colNum); /* Included */ // done

  bool isInSecondEdges(int n, int rowNum, int colNum); /* Included */ // done

  int futureMaxLoss(const char board[][26], int n, int rowNum, int colNum, char turn); /* Included */

      /*int countScore*/

void computerMove(char board[][26], int n, char computerColour); // done

    int countScore(char board[][26], int n, int row, int col, char colour); /* Included */ // done

        /*bool checkLegalInDirection*/

        int countScoreInDirection(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol); /* Included */ // done

    /*void flipTiles*/

void flipTiles(char board[][26], int n, int row, int col, char userColour); // done

    void flipTilesInDirection(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol); // done

    /*bool checkLegalInDirection*/ 

bool gameOver(char board[][26], int n, char userColour, char computerColour); // done

    bool canMove(char board[][26], int n, char colour); // done

    bool full(char board[][26], int n);  // done

bool checkSingleLegal(char board[][26], int n, int row, int col, char colour); // done /* Included */ // consted

    bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol); /* Included */ // done // consted

        bool positionInBounds(int n, int row, int col); /* Included */ // done

        bool positionOccupied(char board[][26], int row, int col); /* Included */ // done // consted

int countFinalNumber(char board[][26], int n, char colour); // done

void findAndPrintAvailableMoves(char board[][26], int n, char color); // done

/* Main function - - - - - - - - - - - - - - S T A R T - - - - - - - - - - - - - - Main function */

int main(void) {
    char board[26][26];
    int n;
    char computerColour, userColour;

    // Initialize the game:

    printf("Enter the board dimension: ");
    scanf(" %d", &n);
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);

    if(computerColour == 'B'){
        userColour = 'W';
    }else if(computerColour == 'W'){
        userColour = 'B';
    }
  
    initializeBoard(board, n);
    printBoard(board, n);

    // PK:

    if(computerColour == 'B'){

        while(gameOver(board, n, userColour, computerColour) == false){

            if(canMove(board, n, computerColour)){ 

                printf("Available moves for %c:\n", computerColour);
                findAndPrintAvailableMoves(board, n, computerColour);

                int rowNumber, colNumber;
                int* row = &rowNumber;
                int* col = &colNumber;

                makeMove(board, n, computerColour, row, col);

                flipTiles(board, n, rowNumber, colNumber, computerColour);
                printBoard(board, n);
                
            }else{

                if(gameOver(board, n, userColour, computerColour) == false){
                    printf("%c player has no valid move.\n", computerColour);
                }
            }

            if(canMove(board, n, userColour)){        // tb changed

                printf("Available moves for %c:\n", userColour);
                findAndPrintAvailableMoves(board, n, userColour);

                int testingRowNumber, testingColNumber;
                int* pTestingRow = &testingRowNumber;
                int* pTestingCol = &testingColNumber;

                findSmarterMove(board, n, userColour, pTestingRow, pTestingCol);
                printf("Testing AI move (row, col): %c%c\n", testingRowNumber + 'a', testingColNumber + 'a');

                flipTiles(board, n, pTestingRow, pTestingCol, userColour);
                printBoard(board, n);

                if(checkSingleLegal(board, n, testingRowNumber, testingColNumber, userColour) == false){

                    printf("Invalid move.\n");
                    printf("B player wins.\n");

                    return 0; 
                }

                flipTiles(board, n, testingRowNumber, testingColNumber, userColour);
                printBoard(board, n);

            }else{

                if(gameOver(board, n, userColour, computerColour) == false){
                    printf("%c player has no valid move.\n", userColour);
                }
            }
        }

   }else{

        while(gameOver(board, n, userColour, computerColour) == false){        //tb changed

            if(canMove(board, n, userColour)){        // tb changed

                printf("Available moves for %c:\n", userColour);
                findAndPrintAvailableMoves(board, n, userColour);

                int testingRowNumber, testingColNumber;
                int* pTestingRow = &testingRowNumber;
                int* pTestingCol = &testingColNumber;

                findSmarterMove(board, n, userColour, pTestingRow, pTestingCol);
                printf("Testing AI move (row, col): %c%c\n", testingRowNumber + 'a', testingColNumber + 'a');

                flipTiles(board, n, pTestingRow, pTestingCol, userColour);
                printBoard(board, n);

                if(checkSingleLegal(board, n, testingRowNumber, testingColNumber, userColour) == false){

                    printf("Invalid move.\n");
                    printf("B player wins.\n");

                    return 0; 
                }

                flipTiles(board, n, testingRowNumber, testingColNumber, userColour);
                printBoard(board, n);

            }else{

                if(gameOver(board, n, userColour, computerColour) == false){
                    printf("%c player has no valid move.\n", userColour);
                }
            }

            if(canMove(board, n, computerColour)){ 

                printf("Available moves for %c:\n", computerColour);
                findAndPrintAvailableMoves(board, n, computerColour);

                int rowNumber, colNumber;
                int* row = &rowNumber;
                int* col = &colNumber;
                
                makeMove(board, n, computerColour, row, col);

                flipTiles(board, n, rowNumber, colNumber, computerColour);
                printBoard(board, n);
                
            }else{

                if(gameOver(board, n, userColour, computerColour) == false){
                    printf("%c player has no valid move.\n", computerColour);
                }
            }
        }
    }

    // Decide the winner:

    int computerFinalNumber = countFinalNumber(board, n, computerColour);
    int userFinalNumber = countFinalNumber(board, n, userColour);

    if(computerFinalNumber > userFinalNumber){
        printf("%c player wins.\n", computerColour);
    }else if(computerFinalNumber < userFinalNumber){
        printf("%c player wins.\n", userColour);
    }else{
        printf("Draw!\n");
    }

    return 0;
}

/* Main function - - - - - - - - - - - - - - E N D - - - - - - - - - - - - - - Main function */

// Functions: 

void initializeBoard(char board[][26], int n){
    for(int r = 0; r < n; r += 1){
    for(int c = 0; c < n; c += 1){

      if(((r == n / 2 - 1) && (c == n/2 - 1)) || ((r == n / 2) && (c == n/2))){
        board[r][c] = 'W';

      }else if(((r == n / 2 - 1) && (c == n / 2)) || ((r == n / 2) && (c == n/2 - 1))){
        board[r][c] = 'B';

      }else{
        board[r][c] = 'U';
      }
    }
  }
}

void printBoard(char board[][26], int n) {

  char alphabet1[26];
  for(int i = 0; i < 26; i += 1){
    alphabet1[i] = (char)('a' + i); 
  }

  printf("  ");
  for(int j = 0; j < n; j += 1){
    printf("%c", alphabet1[j]); 
  }
  printf("\n");

  for(int r = 0; r < n; r += 1){  
    printf("%c ", alphabet1[r]);

    for(int c = 0; c < n; c += 1){
      printf("%c", board[r][c]);
    }
    printf("\n");
  }
}

bool checkSingleLegal(char board[][26], int n, int row, int col, char colour){

  bool singleLegal = false;
  
  if(checkLegalInDirection(board, n, row, col, colour, 0, 1)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, -1, 1)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, -1, 0)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, -1, -1)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, 0, -1)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, 1, -1)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, 1, 0)){
    singleLegal = true;
  }else if(checkLegalInDirection(board, n, row, col, colour, 1, 1)){
    singleLegal = true;
  }

  return singleLegal;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, 
                           char colour, int deltaRow, int deltaCol) {

  bool legalInDirection = false;
  char oppositeColour;

  if(colour == 'W'){
    oppositeColour = 'B';
  }else if(colour == 'B'){
    oppositeColour = 'W';
  }else{
    return legalInDirection;
  }

  if(positionInBounds(n, row + deltaRow, col + deltaCol) == false){
    
    return legalInDirection;
  } 
  if(positionOccupied(board, row, col) == true){
    
    return legalInDirection;
  }

  char firstContinuedLetter = board[row + deltaRow][col + deltaCol];

  if(firstContinuedLetter != oppositeColour){
    
    return legalInDirection;
  }

  int count = 2; 

  while(positionInBounds(n, row + (deltaRow * count), col + (deltaCol * count)) == true){

    char countedLetter = board[row + deltaRow * count][col + deltaCol * count];

    if (countedLetter == colour){

      legalInDirection = true;
      return legalInDirection;
    
    }else if(countedLetter == oppositeColour){
      count += 1;

    }else{
      return legalInDirection;
    }
  }
  return legalInDirection;

}

bool positionInBounds(int n, int row, int col) {
  bool inBounds = false;
  if((row >= 0 && row < n) && (col >= 0 && col < n)){
    inBounds = true;
  }

  return inBounds;
}

bool positionOccupied(char board[][26], int row, int col){
  bool occupied = true;

  if(board[row][col] == 'U'){
    occupied = false; 
  }

  return occupied;
}

bool canMove(char board[][26], int n, char colour){

    bool itCan = false;

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){

            if(checkSingleLegal(board, n, r, c, colour)){
                itCan = true; 
                return itCan;
            }
        }
    }
    return itCan;
}

bool full(char board[][26], int n){

    bool isFull = true;

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){

            if(board[r][c] == 'U'){
                isFull = false;
                return isFull;
            }
        }
    }
    return isFull;
}

bool gameOver(char board[][26], int n, char userColour, char computerColour){

    bool isOver = false;

    if(full(board, n) == true){
        isOver = true;
        return isOver;
    }

    if((canMove(board, n, userColour) == false) && (canMove(board, n, computerColour) == false)){
        isOver = true;
        return isOver;
    }

    return isOver;
}

int countFinalNumber(char board[][26], int n, char colour){

    int finalNumber = 0; 

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){

            if(board[r][c] == colour){
                finalNumber++; 
            }
        }
    }   
    
    return finalNumber;
}

void flipTilesInDirection(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol){

    for(int i = 1; board[row + (deltaRow * i)][col + (deltaCol * i)] != colour; i += 1){

    board[row + (deltaRow * i)][col + (deltaCol * i)] = colour;
  }
}

void flipTiles(char board[][26], int n, int row, int col, char colour){

  if(checkLegalInDirection(board, n, row, col, colour, 0, 1)){
    flipTilesInDirection(board, row, col, colour, 0, 1);
    
  }
  if(checkLegalInDirection(board, n, row, col, colour, -1, 1)){
    flipTilesInDirection(board, row, col, colour, -1, 1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, -1, 0)){
    flipTilesInDirection(board, row, col, colour, -1, 0);

  }
  if(checkLegalInDirection(board, n, row, col, colour, -1, -1)){
    flipTilesInDirection(board, row, col, colour, -1, -1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 0, -1)){
    flipTilesInDirection(board, row, col, colour, 0, -1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 1, -1)){
    flipTilesInDirection(board, row, col, colour, 1, -1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 1, 0)){
    flipTilesInDirection(board, row, col, colour, 1, 0);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 1, 1)){
    flipTilesInDirection(board, row, col, colour, 1, 1);
  }

  board[row][col] = colour;
}

int countScoreInDirection(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol){

    int scoreInDirection = 0;

    for(int i = 1; board[row + (deltaRow * i)][col + (deltaCol * i)] != colour; i += 1){
        scoreInDirection++; 
    }

    return scoreInDirection;
}

int countScore(char board[][26], int n, int row, int col, char colour){

  int score = 0;
  
  if(checkLegalInDirection(board, n, row, col, colour, 0, 1)){
    score += countScoreInDirection(board, row, col, colour, 0, 1);
    
  }
  if(checkLegalInDirection(board, n, row, col, colour, -1, 1)){
    score += countScoreInDirection(board, row, col, colour, -1, 1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, -1, 0)){
    score += countScoreInDirection(board, row, col, colour, -1, 0);

  }
  if(checkLegalInDirection(board, n, row, col, colour, -1, -1)){
    score += countScoreInDirection(board, row, col, colour, -1, -1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 0, -1)){
    score += countScoreInDirection(board, row, col, colour, 0, -1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 1, -1)){
    score += countScoreInDirection(board, row, col, colour, 1, -1);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 1, 0)){
    score += countScoreInDirection(board, row, col, colour, 1, 0);

  }
  if(checkLegalInDirection(board, n, row, col, colour, 1, 1)){
    score += countScoreInDirection(board, row, col, colour, 1, 1);
  }

  score *= 10;

  return score;
}

void computerMove(char board[][26], int n, char computerColour){

    int bestRow, bestCol;
    int bestScore = 0;

    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){

          if(checkSingleLegal(board, n, row, col, computerColour)){

            int currentScore = countScore(board, n, row, col, computerColour);

            if(currentScore > bestScore){
                
                bestScore = currentScore;
                bestRow = row;
                bestCol = col;
            }
          }
        }
    }

    char bestRowLetter = (char)('a' + bestRow);
    char bestColLetter = (char)('a' + bestCol);

    printf("Computer places %c at %c%c.\n", computerColour, bestRowLetter, bestColLetter);
    flipTiles(board, n, bestRow, bestCol, computerColour);    
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col){

  int bestRowNum, bestColNum;
  int bestScore = 0;
  int iterationCount = 0;

  for(int rowNum = 0; rowNum < n; rowNum++){
    for(int colNum = 0; colNum < n; colNum++){
      if(checkSingleLegal(board, n, rowNum, colNum, turn)){

        int currentScore = 0;

        int currentKill = countScore(board, n, rowNum, colNum, turn);
        int willBeMaxKilled = futureMaxLoss(board, n, rowNum, colNum, turn);

        int netKill = currentKill - willBeMaxKilled;
        currentScore += netKill;

        if(isInDeadArea(board, n, rowNum, colNum)){
          currentScore -= 1000;

        }else if(isInCorner(n, rowNum, colNum)){
          currentScore += 1000;

        }

        if(currentScore == bestScore){

          if(isInEdges(n, rowNum, colNum)){
           currentScore += 1;

          }else if(isInSecondEdges(n, rowNum, colNum)){
           currentScore -= 1;
          }          
        }

        iterationCount += 1;

        if(currentScore > bestScore){     
          bestScore = currentScore;
          bestRowNum = rowNum;
          bestColNum = colNum;

        }else if(iterationCount == 1){
          bestScore = currentScore;
          bestRowNum = rowNum;
          bestColNum = colNum;
        }       
      }
    }
  }
  
  *row = bestRowNum;
  *col = bestColNum;

  char bestRowLetter = (char)('a' + *row);
  char bestColLetter = (char)('a' + *col);

  printf("The best choice is (%c,%c). Score: %d\n", bestRowLetter, bestColLetter, bestScore); // To be DELETED !!!!!!!!!!!!!!!!!!!!!!!!!!!

  return 0; 
}

  /*if(checkSingleLegal(board, n, 0, 0, turn)){
    *row = 0;
    *col = 0;
    return 0;
  }
  if(checkSingleLegal(board, n, 0, n, turn)){
    *row = 0;
    *col = n;
    return 0;
  }
  if(checkSingleLegal(board, n, n, n, turn)){
    *row = n;
    *col = n;
    return 0;
  }
  if(checkSingleLegal(board, n, n, 0, turn)){
    *row = n;
    *col = 0;
    return 0;
  }

  if()*/

bool isInDeadArea(const char board[][26], int n, int rowNum, int colNum){
  bool inDeadArea = false;

  if((rowNum == 0 && colNum == 1) || (rowNum == 1 && colNum == 0) || (rowNum == 1 && colNum == 1)){
    if(positionOccupied(board, 0, 0) == false){
      inDeadArea = true;
    }
  }else if((rowNum == 0 && colNum == (n - 2)) || (rowNum == 1 && colNum == (n - 1)) || (rowNum == 1 && colNum == (n - 2))){
    if(positionOccupied(board, 0, (n - 1)) == false){
      inDeadArea = true;
    }
  }else if((rowNum == (n - 2) && colNum == 0) || (rowNum == (n - 1) && colNum == 1) || (rowNum == (n - 2) && colNum == 1)){
    if(positionOccupied(board, (n - 1), 0) == false){
      inDeadArea = true;
    }
  }else if((rowNum == (n - 1) && colNum == (n - 2)) || (rowNum == (n - 2) && colNum == (n - 1)) || (rowNum == (n - 2) && colNum == (n - 2))){
    if(positionOccupied(board, (n - 1), (n - 1)) == false){
      inDeadArea = true;
    }
  }
  return inDeadArea;
}

bool isInEdges(int n, int rowNum, int colNum){
  bool inEdge = false; 

  if((rowNum == 0) && (colNum >= 2 && colNum <= (n - 3))){
    inEdge = true;
  }else if((rowNum >= 2 && rowNum <= (n - 3)) && (colNum == 0)){
    inEdge = true;
  }else if((rowNum == (n - 1)) && (colNum >= 2 && colNum <= (n - 3))){
    inEdge = true;
  }else if((rowNum >= 2 && rowNum <= (n - 3)) && (colNum == (n - 1))){
    inEdge = true;
  }

  return inEdge;
}

bool isInCorner(int n, int rowNum, int colNum){
  bool inCorner = false;

  if(((rowNum == 0 && colNum == 0) || (rowNum == 0 && colNum == (n - 1))) || (rowNum == (n - 1) && colNum == 0) || (rowNum == (n - 1) && colNum == (n - 1))){
    inCorner = true;
  }
  return inCorner;
}

bool isInSecondEdges(int n, int rowNum, int colNum){
  bool inSecondEdge = false; 

  if((rowNum == 1) && (colNum >= 2 && colNum <= (n - 3))){
    inSecondEdge = true;
  }else if((rowNum >= 2 && rowNum <= (n - 3)) && (colNum == 1)){
    inSecondEdge = true;
  }else if((rowNum == (n - 2)) && (colNum >= 2 && colNum <= (n - 3))){
    inSecondEdge = true;
  }else if((rowNum >= 2 && rowNum <= (n - 3)) && (colNum == (n - 2))){
    inSecondEdge = true;
  }

  return inSecondEdge;
}

int futureMaxLoss(const char board[][26], int n, int rowNum, int colNum, char turn){

  int maxLoss = 0;

  char futureBoard[26][26];

  for(int r = 0; r < n; r++){
    for(int c = 0; c < n; c++){
      futureBoard[r][c] = board[r][c];
    }
  }

  flipTiles(futureBoard, n, rowNum, colNum, turn);

  char enemyTurn; 
  if(turn == 'B'){
    enemyTurn = 'W';
  }else if(turn == 'W'){
    enemyTurn = 'B';
  }

  for(int r = 0; r < n; r++){
    for(int c = 0; c < n; c++){
      if(checkSingleLegal(futureBoard, n, r, c, enemyTurn)){

        int currentLoss = countScore(futureBoard, n, r, c, enemyTurn);

        if(currentLoss > maxLoss){
          maxLoss = currentLoss;
        }
      }
    }
  }
  
  return maxLoss;
}

void findAndPrintAvailableMoves(char board[][26], int n, char colour){
  char legalRowLetter, legalColLetter; 
  bool isAvailable = false;
  int countMobility = 0;

  for(int r = 0; r < n; r += 1){
    for(int c = 0; c < n; c += 1){

      isAvailable = false;
      isAvailable = checkSingleLegal(board, n, r, c, colour);

      if(isAvailable == true){   

        legalRowLetter = (char)('a' + r);
        legalColLetter = (char)('a' + c);

        int killability = countScore(board, n, r, c, colour);
        int netKillability = countScore(board, n, r, c, colour) - futureMaxLoss(board, n, r, c, colour);

        printf("%c%c    %d    %d\n", legalRowLetter, legalColLetter, killability, netKillability);
        countMobility += 1;
      }
    }
  }
  printf("Mobility for %c is %d\n", colour, countMobility); 
}
