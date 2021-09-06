#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 9
#define COL 9

#define EMPTY 0

void print_board(const int board[][COL]) {
    for ( int i=0; i<ROW; ++i ) {
        if ( i % 3 == 0 ) {
            for ( int k=0; k<ROW + 3; ++k ) {
                printf("- ");
            }
            printf("\n");
        }
        for ( int j=0; j<COL; ++j ) {
            if ( j % 3 == 0 ) {
                printf("| ");
            }
            printf("%d ", board[i][j]);
        }
    printf("\n");
    }
}

// checks if the given number is on the given row
bool check_row(const int board[][COL], int row, int number) {
    for ( int j=0; j<COL; ++j ) {
        if ( board[row][j] == number ) 
            return false;
    }
    return true;
}

// checks if the given number is on the given col
bool check_col(const int board[][COL], int col, int number) {
    for ( int i=0; i<ROW; ++i ) {
        if ( board[i][col] == number )
            return false;
    }
    return true;
}

// checks if the given number is on the given grid
bool check_square(const int board[][COL], int row, int col, int number) {
    int start_row = row - (row % 3);
    int start_col = col - (col % 3);

    for ( int i=start_row; i<start_row + 3; ++i ) {
        for ( int j=start_col; j<start_col + 3; ++j ) {
            if ( board[i][j] == number )
                return false;
        }
    }
    return true;
}

// checks if the given position is empty
bool is_empty(const int board[][COL], int row, int col) {
    return board[row][col] == EMPTY;
}

// checks if the given move is valid
bool is_available(const int board[][COL], int row, int col, int number) {
    return check_row(board, row, number) &&
            check_col(board, col, number) &&
            check_square(board, row, col, number);
}

bool is_board_filled(const int board[][COL]) {
    for ( int i=0; i<ROW; ++i ) {
        for ( int j=0; j<COL; ++j ) {
            if ( board[i][j] == EMPTY )
                return false;
        }
    }
    return true;
}

bool solve_sudoku(int board[][COL]) {
    // base case
    if ( is_board_filled(board) )
        return true;

    for ( int i=0; i<9; ++i ) { // go through every row
        for ( int j=0; j<9; ++j ) { // go through every col
            if ( is_empty(board, i, j) ) {
                for ( int move=1; move<=9; ++move ) { // go through each number
                    if ( is_available(board, i, j, move) ) { // if we can make the move
                        board[i][j] = move; // make the move
                        if ( solve_sudoku(board) ) // recurse
                            return true;
                        board[i][j] = EMPTY; // take the above move back
                    }
                }
                return false; // the board is not solvable
            }
        }
    }
}

int main(int argc, char** argv) {
    int board[ROW][COL] = {
        { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
        { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
        { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
        { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
        { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
        { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
        { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
        { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
        { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
    };

    solve_sudoku(board);
    print_board(board);
    
    return EXIT_SUCCESS;
}