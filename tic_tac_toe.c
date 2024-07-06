#include <stdio.h>

// Function to initialize the board
void initialize_board(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Function to display the board
void display_board(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Function to take player input
void player_move(char board[3][3], char player_marker) {
    int row, col;

    printf("Player %c's turn. Enter row (1-3) and column (1-3): ", player_marker);
    scanf("%d %d", &row, &col);

    row--;
    col--;

    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        printf("Invalid move. Please try again.\n");
        player_move(board, player_marker);
    } else {
        board[row][col] = player_marker;
    }
}

// Function to check for a win
int check_win(char board[3][3], char player_marker) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player_marker && board[i][1] == player_marker && board[i][2] == player_marker) {
            return 1;
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player_marker && board[1][i] == player_marker && board[2][i] == player_marker) {
            return 1;
        }
    }
    // Check diagonals
    if (board[0][0] == player_marker && board[1][1] == player_marker && board[2][2] == player_marker) {
        return 1;
    }
    if (board[0][2] == player_marker && board[1][1] == player_marker && board[2][0] == player_marker) {
        return 1;
    }
    return 0;
}

// Main function to test the gameplay mechanics
int main() {
    char board[3][3];
    initialize_board(board);
    display_board(board);

    char current_player = 'X';
    int moves = 0;
    int win = 0;

    while (moves < 9 && !win) {
        player_move(board, current_player);
        display_board(board);
        win = check_win(board, current_player);

        if (win) {
            printf("Player %c wins!\n", current_player);
        } else {
            current_player = (current_player == 'X') ? 'O' : 'X';
            moves++;
        }
    }

    if (!win) {
        printf("It's a tie!\n");
    }

    return 0;
}
