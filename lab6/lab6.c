#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]); // done
char* readWord(int* wordSize);//done
void printWordPuzzle(const int Size, char puzzle[][Size]); // done
void printWord(char* word, const int wordSize); //done

void search(const int Size,
            char puzzle[][Size],
            const int wordSize,
            char* word); //done

bool inBounds(int row, int col, const int Size); //done

bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir); // changed *

int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);
  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");
  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }
  free(word);
  return 0;
}

void search(const int Size,
            char puzzle[][Size],
            const int wordSize,
            char* word) {

              bool check = false;
              int rowNum, colNum, dirNum;
              
              char* dirList[8] = {"south-east", "south", "south-west", "west", "north-west", "north", "north-east", "east"};  //later added.
              
              
              for(int row = 0; row < Size && check == false; row++){
                for(int col = 0; col < Size && check == false; col++){
                  if(puzzle[row][col] == word[0]){

                    rowNum = row + 1;
                    colNum = col + 1;                      

                    for(int dir = 0; dir < 8 && check == false; dir++){
                      dirNum = dir;
                      
                      if(check1D(Size, puzzle, wordSize, word, row, col, dir) == true){
                        check = true;
                      }
                     
                    }
                  }
                }
              }
                            
              if(check == false){
                for(int i = 0; i < wordSize; i++){
                  printf("%c", word[i]);
                }
                printf(" cannot be found!\n");
              }else{
                for(int i = 0; i < wordSize; i++){
                  printf("%c", word[i]);
                }
                printf(" can be found at row , col = (%d, %d) in the %s direction.\n", rowNum, colNum, dirList[dirNum]);
              }
            }


char* readWord(int* wordSize) {

  printf("How many characters are there in the word?\n");
  scanf("%d", wordSize);

  char* word = (char*) malloc ((*wordSize) * sizeof(char));

  printf("What is the word that you are looking for?\n");

  for (int index = 0; index < *wordSize; index++) {

    char temp;
    scanf("%c", &temp);
    
    if(temp != '\n' || temp != ' '){
      word[index] = temp;
    }else{
      index -= 1;
    }    
  }

  return word;
}

void readWordPuzzle(const int Size, char puzzle[][Size]) {

  printf("Please enter the word puzzle:\n");

  for(int i = 0; i < Size; i++) {
    for(int j = 0; j < Size; j++) {
        scanf(" %c", &puzzle[i][j]);
    }
  }
}

bool inBounds(int row, int col, const int Size) {

  bool in = false;

  if((row < Size && row >= 0) && (col < Size && col >= 0)){
    in = true;
  }

  return in;
}


void printWordPuzzle(const int Size, char puzzle[][Size]) {

  printf("The word puzzle entered is\n");

  for(int row = 0; row < Size; row++){

    for(int col = 0; col < Size; col++){

      printf("%c", puzzle[row][col]);

      if(col != Size - 1){
        printf(" ");
      }
    }
    printf("\n");
  }
}


void printWord(char* word, const int wordSize) {

  for(int i = 0; i < wordSize; i++){

    printf("%c", word[i]);

  }
}

bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir){ 
  bool checked = true;
  
  for(int i = 1; i < wordSize; i++){

    if(dir == 0){
      if(inBounds(rowLoc + i, colLoc + i, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc + i][colLoc + i] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 1){
      if(inBounds(rowLoc + i, colLoc, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc + i][colLoc] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 2){                                           
      if(inBounds(rowLoc + i, colLoc -i, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc + i][colLoc - i] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 3){
      if(inBounds(rowLoc, colLoc - i, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc][colLoc - i] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 4){                                           
      if(inBounds(rowLoc - i, colLoc - i, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc - i][colLoc - i] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 5){
      if(inBounds(rowLoc - i, colLoc, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc - i][colLoc] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 6){
      if(inBounds(rowLoc - i, colLoc + i, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc - i][colLoc + i] != word[i]){
          checked = false;
          return checked;
        }
      }
    }else if(dir == 7){
      if(inBounds(rowLoc, colLoc + i, Size) == false){
        checked = false;
        return checked;
      }else{
        if(puzzle[rowLoc][colLoc + i] != word[i]){
          checked = false;
          return checked;
        }
      }
    }
  }
  return checked;
}
