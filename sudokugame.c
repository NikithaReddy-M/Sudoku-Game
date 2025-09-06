#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

// Function to print the Sudoku board
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Check if it's valid to place 'num' at board[row][col]
bool isValidMove(int board[SIZE][SIZE], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Check if the board is completely filled
bool isBoardFull(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Solve Sudoku using backtracking
bool solveSudoku(int board[SIZE][SIZE]) {
    int row, col;

    if (isBoardFull(board)) {
        return true;
    }

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isValidMove(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board)) {
                            return true;
                        }

                        // Backtrack
                        board[row][col] = 0;
                    }
                }

                // If no valid number found, backtrack
                return false;
            }
        }
    }

    return false; // Should not reach here
}

// Main function
int main() {
    int sudokuBoard[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    printf("Sudoku Puzzle:\n");
    printBoard(sudokuBoard);

    if (solveSudoku(sudokuBoard)) {
        printf("\nSudoku Solved:\n");
        printBoard(sudokuBoard);
    } else {
        printf("\nNo solution exists.\n");
    }

    return 0;
}
