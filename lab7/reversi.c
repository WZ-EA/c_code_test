//
// Author: Jue Wang
//

#include "reversi.h"
#include "stdio.h"

// Given functions - prototype:

void printBoard(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);    // To change. -> Changed.

// Created function - prototype: 

bool positionOccupied(char board[][26], int row, int col);

void findAndPrintAvailableMoves(char board[][26], int n, char color);

bool checkSingleLegal(char board[][26], int n, int row, int col, char colour);

void flipTilesInDirection(char board[][26], int row, int col,
                           char colour, int deltaRow, int deltaCol);

void flipTiles(char board[][26], int n, int row, int col, char colour);   // To change. 

/* Main function - - - - - - - - - - - - - - S T A R T - - - - - - - - - - - - - - Main function */

int main(void) {
  char board[26][26];
  int n;

  // Generate and Print the original board input:

  printf("Enter the board dimension: ");
  scanf("%d", &n);

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
  printBoard(board, n);

  // Enter the board configuration:

  bool configuartionEnd = false;
  
  printf("Enter board configuration:\n");

  while(configuartionEnd == false){

    char configColour, configRowLetter, configColLetter;
    int configRowNumber, configColNumber;

    scanf(" %c%c%c", &configColour, &configRowLetter, &configColLetter);

    if(configColour == '!'){
      configuartionEnd = true;
      break;
    }

    configRowNumber = configRowLetter - 'a';
    configColNumber = configColLetter - 'a';

    board[configRowNumber][configColNumber] = configColour;    
  }

  // Print the board:

  printBoard(board, n);

  // Print the available moves:

  char white = 'W';
  char black = 'B';

  printf("Available moves for W:\n");
  findAndPrintAvailableMoves(board, n, white);

  printf("Available moves for B:\n");
  findAndPrintAvailableMoves(board, n, black);

/* Case 1:

8

Wed
Bfe
Wdc
Wcc
Wcd
Wce
Bcf
!!!

Bcb

*/


  // Enter a move & make changes:

  char colourToMove;
  char rowToMove;
  char colToMove; 

  printf("Enter a move:\n");
  scanf(" %c%c%c", &colourToMove, &rowToMove, &colToMove);

  int rowToMoveNumber = rowToMove - 'a';
  int colToMoveNumber = colToMove - 'a';

  if(checkSingleLegal(board, n, rowToMoveNumber, colToMoveNumber, colourToMove) == true){
    printf("Valid move.\n");

    flipTiles(board, n, rowToMoveNumber, colToMoveNumber, colourToMove);
    board[rowToMoveNumber][colToMoveNumber] = colourToMove;

  }else{
    printf("Invalid move.\n");
  }
  
  // Print the fanal board:

  printBoard(board, n);
  
  return 0;
}
/* Main function - - - - - - - - - - - - - - E N D - - - - - - - - - - - - - - Main function */

// Given functions: 

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

bool positionInBounds(int n, int row, int col) {
  bool inBounds = false;
  if((row >= 0 && row < n) && (col >= 0 && col < n)){
    inBounds = true;
  }

  return inBounds;
}

/* Case 2:

6

Bbd
Bad
Wde
Wcb
!!!

Bbe
or
Bdf
*/

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

//Created function: 

bool positionOccupied(char board[][26], int row, int col){
  bool occupied = true;

  if(board[row][col] == 'U'){
    occupied = false; 
  }

  return occupied;
}

void findAndPrintAvailableMoves(char board[][26], int n, char colour){
  char legalRowLetter, legalColLetter; 
  bool isAvailable = false;

  for(int r = 0; r < n; r += 1){
    for(int c = 0; c < n; c += 1){

      legalRowLetter = (char)('a' + r);
      legalColLetter = (char)('a' + c);

      isAvailable = false;
      isAvailable = checkSingleLegal(board, n, r, c, colour);

      if(isAvailable == true){
        printf("%c%c\n", legalRowLetter, legalColLetter);
      }
    }
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

void flipTilesInDirection(char board[][26], int row, int col,
                           char colour, int deltaRow, int deltaCol){

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
}
