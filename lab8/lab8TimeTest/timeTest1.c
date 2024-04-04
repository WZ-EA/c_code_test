//
// Author: Jue Wang
//

#include "timeTestHead.h"

#include "stdio.h"

#include <sys/time.h>
#include <sys/resource.h>

// Functions - prototype:

void initializeBoard(char board[][26], int n); // done

void printBoard(char board[][26], int n); // done

void computerMove(char board[][26], int n, char computerColour); // done

    int countScore(char board[][26], int n, int row, int col, char colour); // done

        /*bool checkLegalInDirection*/

        int countScoreInDirection(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol); // done

    /*void flipTiles*/

void flipTiles(char board[][26], int n, int row, int col, char userColour); // done

    void flipTilesInDirection(char board[][26], int row, int col, char colour, int deltaRow, int deltaCol); // done

    /*bool checkLegalInDirection*/ 

bool gameOver(char board[][26], int n, char userColour, char computerColour); // done

    bool canMove(char board[][26], int n, char colour); // done

    bool full(char board[][26], int n);  // done

bool checkSingleLegal(char board[][26], int n, int row, int col, char colour); // done

    bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol); // done

        bool positionInBounds(int n, int row, int col); // done

        bool positionOccupied(char board[][26], int row, int col); // done

int countFinalNumber(char board[][26], int n, char colour); // done

int main(void){

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

    struct rusage usage; // a structure to hold "resource usage" (including time)
    struct timeval start, end; // will hold the start and end times
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    double timeStart = start.tv_sec +
                   start.tv_usec / 1000000.0; // in seconds

    computerMove(board, n, computerColour);

    // PLACE THE CODE YOU WISH TO TIME HERE
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double timeEnd = end.tv_sec +
                 end.tv_usec / 1000000.0; // in seconds
    double totalTime = timeEnd - timeStart;

    printf("the time is: %f\n", totalTime);

    return 0;
}

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

