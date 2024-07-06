#include <stdio.h>

void initialize_board(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void display_board(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

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

int main() {
    char board[3][3];
    initialize_board(board);
    display_board(board);

    player_move(board, 'X');
    display_board(board);

    player_move(board, 'O');
    display_board(board);

    return 0;
}
