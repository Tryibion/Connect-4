// copyright by Chandler Cox in 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//connect 4 game implimentation
#define COLUMNS 7
#define ROWS 6
//const int COLUMNS = 7; // number of columns
//const int ROWS = 6; //number of rows

//player struct
struct player{
  char name[20];
  int numGamesWon;
};

//randomly decide who goes first, returns 0 for player1 and 1 for player2
int first_turn(){
  srand(time(NULL));
  int first_turn = rand() % 2;
  if(first_turn == 1){
    return 0;
  } else {
    return 1;
  }
}

// print gameBoard, no return value
void print_board(int board[ROWS][COLUMNS]){
  printf("\n");
  printf("-Game Board- \n");
  printf("1 2 3 4 5 6 7\n\n");
  for(int i = 0; i<ROWS; i++){
    for(int j = 0; j<COLUMNS; j++){
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}

//turn function, controls each players turn, no return value
void turn(int board[ROWS][COLUMNS], int player){
  //turn
  int column;
  while(1){
    printf("Enter column number between 1 and 7: ");
    scanf("%d", &column);
    if(column <=7 && column >=1){
      column -=1;
        if(board[0][column] != 0){ //bounds top
          printf("Invalid Input\n");
          continue;
        }
      break;
    } else{
      printf("Invalid Input\n"); //bounds columns
    }
  }
  //moves number to the most bottom row
  if(board[5][column] == 0){
    board[5][column] = player;
  }else if(board[4][column] == 0){
    board[4][column] = player;
  }else if(board[3][column] == 0){
    board[3][column] = player;
  }else if(board[2][column] == 0){
    board[2][column] = player;
  }else if(board[1][column] == 0){
    board[1][column] = player;
  }else if(board[0][column] == 0){
    board[0][column] = player;
  }
    
  print_board(board); //print board
}

//menu after game is finished, player input 1 to quit, 2 to play again, returns 1 to quit and 0 to play again
int menu(){
  int userInp;
  while(1){
    //user menu
    printf("\nOptions:\n1: quit\n2: play again\n");
    printf("Enter Option Number: ");
    scanf("%d", &userInp);
    if(userInp == 1){
      return 1;
    }else if(userInp == 2){
      return 0;
    } else{
      printf("Invalid Input\n");
    }
  }
}

//check the board for 4 in all directions row to win, return 1 if 4 in a row are found, 0 in none are found, and 2 if a draw
int check_board(int board[ROWS][COLUMNS]){
  int checker1 = 0; //checks for player1 win
  int checker2 = 0; // checks for player2 win
  //checks columns for 4
  for(int j = 0; j<COLUMNS; j++){
    checker1 = 0;
    checker2 = 0;
    for(int i = 0; i<ROWS; i++){
      if (board[i][j] == 1){
        checker1 += 1;
      }else{
        checker1 = 0;
      }

      if(board[i][j] == 2){
        checker2 += 1;
      }else{
        checker2 = 0;
      }
      if(checker1 == 4 || checker2 == 4){
        return 1;
      }
    }
  }

  // checks rows for 4
  for(int i = 0; i<ROWS; i++){
    checker1 = 0;
    checker2 = 0;
    for(int j = 0; j<COLUMNS; j++){
      if (board[i][j] == 1){
        checker1 += 1;
      }else{
        checker1 = 0;
      }

      if(board[i][j] == 2){
        checker2 += 1;
      }else{
        checker2 = 0;
      }
      if(checker1 == 4 || checker2 == 4){
        return 1;
      }
    }
  }

  // check diagonals
  checker1 = 0;
  checker2 = 0;
  for(int i = 0; i < ROWS; i++)
  {
    for(int j = 0; j < COLUMNS; j++)
    {    
      // check right diagonal
      if (board[i][j] == 1)
      {
        checker2 = 0;
        if (ROWS - i >= 4 || COLUMNS - j >= 4)
        {
          for (int k = 0; k < 4; k++)
          {
            if (board[i+k][j+k] == 1)
            {
              checker1 += 1;
            }
            else
            {
              checker1 = 0;
              break;
            }
          }
        }
        
        if (ROWS - i >= 4 || COLUMNS - j < 4)
        {
          if (checker1 != 4)
          {
            // check left diagonal
            for (int k = 0; k < 4; k++)
            {
              if (board[i+k][j-k] == 1)
              {
                checker1 += 1;
              }
              else
              {
                checker1 = 0;
                break;
              }
            }
          }
        }
        
        //printf("checker1 = %d\n", checker1);
      }
      else if (board[i][j] == 2)
      {
        checker1 = 0;

        if (ROWS - i >= 4 || COLUMNS - j >= 4)
        {
          // check right diagonal
          for (int k = 0; k < 4; k++)
          {
            if (board[i+k][j+k] == 2)
            {
              checker2 += 1;
            }
            else
            {
              checker2 = 0;
              break;
            }
          }
        }

        if (ROWS - i >= 4 || COLUMNS - j < 4)
        {
          if (checker2 != 4)
          {
            // check left diagonal
            for (int k = 0; k < 4; k++)
            {
              if (board[i+k][j-k] == 2)
              {
                checker2 += 1;
              }
              else
              {
                checker2 = 0;
                break;
              }
            }
          }
        }
        //printf("checker2 = %d\n", checker2);
      }
      else
      {
        checker1 = 0;
        checker2 = 0;
      }

      if (checker1 == 4 || checker2 == 4)
      {
        return 1;
      }
      
    }
  }

  //checks for draw
  int drawchecker = 0;
  for(int i = 0; i<ROWS; i++){
    for(int j = 0; j<COLUMNS; j++){
      if (board[i][j] != 0){
        drawchecker += 1;
      }
    }
  }
  if(drawchecker == COLUMNS*ROWS){
    return 2; //returns 2 if draw
  }
  return 0; //return 0 if no win
}

int main(void) {
  struct player player1; //creates player1
  struct player player2; //creates player2
  int playerTurn; //used for first turn and to switch turns
  int win; //used to declare a win

  player1.numGamesWon = 0;
  player2.numGamesWon = 0;

  printf("Welcome to Connect 4!\n\n-Instructions-\nThe first player to get 4 of their tiles in a row, column, or diagonally wins the game. \nPlayer 1's tile will be the number 1 and Player 2's tile will be the number 2.\n\n");
  printf("Enter Player 1's Name: "); //get player 1's name
  scanf("%s", player1.name);
  printf("Enter Player 2's Name: "); // get player 2's name
  scanf("%s", player2.name);

  playerTurn = first_turn(); //first turn
  int swapTurn = playerTurn; //used to swap turns after each game

  int done = 0;
  while(!done){
    int gameBoard[ROWS][COLUMNS] = {0}; //create and clear board
    print_board(gameBoard); //print blank board
    
    while(1){ //game play

      if(playerTurn == 0){ //player 1s turn
        printf("\n%s's turn!\n", player1.name);
        turn(gameBoard,1); //does turn and prints board
        win = check_board(gameBoard);

        //check to see if player 1 won
        if(win == 1){
          printf("%s Wins!\n", player1.name);
          player1.numGamesWon += 1;
          break; //breaks while loop if win
        }
        //draw check
        if(win == 2){
          printf("Draw!");
          break; //breaks while loop if draw
        }

        playerTurn = 1; //switch turn

      } else if(playerTurn == 1){ //player 2s turn
        printf("\n%s's turn!\n", player2.name);
        turn(gameBoard,2); //does turn and prints board
        win = check_board(gameBoard);

        //check to see if player 2 won
        if(win == 1){
          printf("%s Wins!\n", player2.name);
          player2.numGamesWon += 1;
          break; //breaks while loop if win
        }
        //draw check
        if(win == 2){
          printf("Draw!");
          break; //breaks while loop if draw
        }

        playerTurn = 0; //switch turn
        
      }
    
    }

    //display points for each player after game
    printf("\n%s's Number of Wins: %d\n", player1.name, player1.numGamesWon);
    printf("%s's Number of Wins: %d\n", player2.name, player2.numGamesWon);

    done = menu(); //options to play again or quit

    if(swapTurn ==1){ //alternate starting turn
      playerTurn = 0;
      swapTurn = 0;
    } else{
      playerTurn = 1;
      swapTurn = 1;
    }

  }
  printf("Thank you for playing!");
  return 0;
}
