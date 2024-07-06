#include <stdio.h>
#include <ctype.h>

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
    while (1) {
        printf("Player %c's turn. Enter row (1-3) and column (1-3): ", player_marker);
        int result = scanf("%d %d", &row, &col);

        if (result != 2) {
            printf("Invalid input. Please enter numeric values.\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }

        row--;
        col--;

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            printf("Invalid move. Please try again.\n");
        } else {
            board[row][col] = player_marker;
            break;
        }
    }
}

// Function to check for a win
int check_win(char board[3][3], char player_marker) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player_marker && board[i][1] == player_marker && board[i][2] == player_marker) {
            return 1;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player_marker && board[1][i] == player_marker && board[2][i] == player_marker) {
            return 1;
        }
    }
    if (board[0][0] == player_marker && board[1][1] == player_marker && board[2][2] == player_marker) {
        return 1;
    }
    if (board[0][2] == player_marker && board[1][1] == player_marker && board[2][0] == player_marker) {
        return 1;
    }
    return 0;
}

int main() {
    char play_again;
    int player_x_wins = 0;
    int player_o_wins = 0;

    do {
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
                if (current_player == 'X') {
                    player_x_wins++;
                } else {
                    player_o_wins++;
                }
            } else {
                current_player = (current_player == 'X') ? 'O' : 'X';
                moves++;
            }
        }

        if (!win) {
            printf("It's a tie!\n");
        }

        printf("\nScore:\nPlayer X: %d\nPlayer O: %d\n", player_x_wins, player_o_wins);

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &play_again);
        play_again = tolower(play_again);

    } while (play_again == 'y');

    printf("Final Score:\nPlayer X: %d\nPlayer O: %d\n", player_x_wins, player_o_wins);
    printf("Thank you for playing!\n");

    return 0;
}
