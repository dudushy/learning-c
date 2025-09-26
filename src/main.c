#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

char board[BOARD_SIZE][BOARD_SIZE];

void initBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void drawBoard() {
    printf("\n-------\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("|");
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c|", board[i][j]);
        }
        printf("\n-------\n");
    }
    printf("\n");
}

int isValidMove(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY);
}

char checkWinner() {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
            return board[i][0];
        }
    }
    
    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != EMPTY) {
            return board[0][j];
        }
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        return board[0][2];
    }
    
    return EMPTY;
}

int isBoardFull() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}

void computerMove() {
    int row, col;
    do {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
    } while (!isValidMove(row, col));
    
    board[row][col] = COMPUTER;
    printf("Computer plays at position (%d, %d)\n", row + 1, col + 1);
}

int playerMove() {
    int row, col;
    
    printf("Enter your move (row col, 1-3): ");
    if (scanf("%d %d", &row, &col) != 2) {
        printf("Invalid input! Please enter two numbers.\n");
        // Clear input buffer
        while (getchar() != '\n');
        return 0;
    }
    
    row--; col--; // Convert to 0-indexed
    
    if (!isValidMove(row, col)) {
        printf("Invalid move! Position (%d, %d) is not available.\n", row + 1, col + 1);
        return 0;
    }
    
    board[row][col] = PLAYER;
    return 1;
}

int main() {
    srand(time(NULL)); // Initialize random seed
    
    initBoard();
    printf("Welcome to Tic Tac Toe!\n");
    printf("You are X, computer is O\n");
    printf("Enter moves as 'row col' (1-3)\n");
    
    drawBoard();
    
    int moves = 0;
    char winner = EMPTY;
    
    while (winner == EMPTY && !isBoardFull()) {
        if (moves % 2 == 0) { // Player's turn
            printf("Your turn:\n");
            if (playerMove()) {
                moves++;
                drawBoard();
                
                // Check for winner after 3rd move
                if (moves >= 3) {
                    winner = checkWinner();
                }
            }
        } else { // Computer's turn
            printf("Computer's turn:\n");
            computerMove();
            moves++;
            drawBoard();
            
            // Check for winner after 3rd move
            if (moves >= 3) {
                winner = checkWinner();
            }
        }
    }
    
    // Game over
    if (winner == PLAYER) {
        printf("Congratulations! You win!\n");
    } else if (winner == COMPUTER) {
        printf("Computer wins! Better luck next time.\n");
    } else {
        printf("It's a tie!\n");
    }
    
    return 0;
}
