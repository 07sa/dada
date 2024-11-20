#include <stdio.h>

#define N 9

int is_valid(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return 0;
        }
    }
    int start_row = row - row % 3, start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[start_row + i][start_col + j] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int solve_sudoku(int board[N][N]) {
    int row = -1, col = -1, empty = 0;
    for (int i = 0; i < N && !empty; i++) {
        for (int j = 0; j < N && !empty; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                empty = 1;
            }
        }
    }
    if (!empty) {
        return 1;
    }
    for (int num = 1; num <= 9; num++) {
        if (is_valid(board, row, col, num)) {
            board[row][col] = num;
            if (solve_sudoku(board)) {
                return 1;
            }
            board[row][col] = 0; // Backtrack
        }
    }
    return 0;
}

void print_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int board[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    if (solve_sudoku(board)) {
        print_board(board);
    } else {
        printf("No solution exists\n");
    }
    return 0;
}
