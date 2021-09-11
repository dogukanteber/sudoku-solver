#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define ROW 9
#define COL 9
#define BOARD_SIZE (ROW * COL)

#define EMPTY 0


int* read_file(const char* file_name) {
    FILE* file;

    file = fopen(file_name, "r");
    if ( file == NULL ) {
        fprintf(stdout, "Could find the file.\n");
        exit(EXIT_FAILURE);
    }

    int* digits = malloc(BOARD_SIZE * sizeof(int));
    size_t pos = 0;
    int digit;

    // read the file character by character
    while ( (digit = fgetc(file)) != EOF ) {
        // if the current char is a digit
        if ( isdigit(digit) ) {
            // put its value as integer to digits array
            digits[pos++] = digit - '0';
        }
    }
    return digits;
}


void init_board(int board[][COL], const char* file_name) {
    int* digits = read_file(file_name);
    for ( size_t i=0; i<ROW; ++i ) {
        for ( size_t j=0; j<COL; ++j ) {
            board[i][j] = digits[(i * ROW) + j];
        }
    }
}

void print_board(const int board[][COL]) {
    for ( size_t i=0; i<ROW; ++i ) {
        if ( i % 3 == 0 ) {
            for ( size_t k=0; k<ROW + 4; ++k ) {
                printf("- ");
            }
            printf("\n");
        }
        for ( size_t j=0; j<COL; ++j ) {
            if ( j % 3 == 0 ) {
                printf("| ");
            }
            printf("%d ", board[i][j]);
        }
    printf("| \n");
    }
}

// checks if the given number is on the given row
bool check_row(const int board[][COL], int row, int number) {
    for ( size_t j=0; j<COL; ++j ) {
        if ( board[row][j] == number ) 
            return false;
    }
    return true;
}

// checks if the given number is on the given col
bool check_col(const int board[][COL], int col, int number) {
    for ( size_t i=0; i<ROW; ++i ) {
        if ( board[i][col] == number )
            return false;
    }
    return true;
}

// checks if the given number is on the given grid
bool check_square(const int board[][COL], int row, int col, int number) {
    size_t start_row = row - (row % 3);
    size_t start_col = col - (col % 3);

    for ( size_t i=start_row; i<start_row + 3; ++i ) {
        for ( size_t j=start_col; j<start_col + 3; ++j ) {
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
    for ( size_t i=0; i<ROW; ++i ) {
        for ( size_t j=0; j<COL; ++j ) {
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

    for ( size_t i=0; i<9; ++i ) { // go through every row
        for ( size_t j=0; j<9; ++j ) { // go through every col
            if ( is_empty(board, i, j) ) {
                for ( size_t move=1; move<=9; ++move ) { // go through each number
                    if ( is_available(board, i, j, move) ) { // if we can make the move
                        board[i][j] = move; // make the move
                        if ( solve_sudoku(board) ) // recursion step
                            return true;
                        board[i][j] = EMPTY; // take the above move back
                    }
                }
                return false; // the board is not solvable
            }
        }
    }
}

void print_usage(void) {
    printf("%s\n", "Usage: ./main <file_name>");
}

char* arguments(int argc, char** argv) {
    if ( argc == 1 ) {
        fprintf(stdout, "Please provide a file that contains sudoku board.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
    else if ( argc == 2 ) {
        return argv[1];
    }
    else {
        fprintf(stdout, "You have provided too many arguments.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
}

void sudoku(int board[][COL], const char* file_name) {
    init_board(board, file_name);
    printf("%s", "\nBoard, before solution:\n\n");
    print_board(board);


    solve_sudoku(board);
    printf("%s", "\nBoard, after solution:\n\n");
    print_board(board);
}

int main(int argc, char** argv) {
    int board[ROW][COL];
    const char* file_name;

    file_name = arguments(argc, argv);

    sudoku(board, file_name);

    
    return EXIT_SUCCESS;
}