#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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
    while (1) {
        printf("Player %c's turn. Enter row (1-3) and column (1-3): ", player_marker);
        int result = scanf("%d %d", &row, &col);

        if (result != 2) {
            printf("Invalid input. Please enter numeric values.\n");
            while (getchar() != '\n');
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

int check_two_in_a_row(char board[3][3], char player_marker, int *row, int *col) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player_marker && board[i][1] == player_marker && board[i][2] == ' ') {
            *row = i;
            *col = 2;
            return 1;
        }
        if (board[i][0] == player_marker && board[i][2] == player_marker && board[i][1] == ' ') {
            *row = i;
            *col = 1;
            return 1;
        }
        if (board[i][1] == player_marker && board[i][2] == player_marker && board[i][0] == ' ') {
            *row = i;
            *col = 0;
            return 1;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player_marker && board[1][i] == player_marker && board[2][i] == ' ') {
            *row = 2;
            *col = i;
            return 1;
        }
        if (board[0][i] == player_marker && board[2][i] == player_marker && board[1][i] == ' ') {
            *row = 1;
            *col = i;
            return 1;
        }
        if (board[1][i] == player_marker && board[2][i] == player_marker && board[0][i] == ' ') {
            *row = 0;
            *col = i;
            return 1;
        }
    }
    if (board[0][0] == player_marker && board[1][1] == player_marker && board[2][2] == ' ') {
        *row = 2;
        *col = 2;
        return 1;
    }
    if (board[0][0] == player_marker && board[2][2] == player_marker && board[1][1] == ' ') {
        *row = 1;
        *col = 1;
        return 1;
    }
    if (board[1][1] == player_marker && board[2][2] == player_marker && board[0][0] == ' ') {
        *row = 0;
        *col = 0;
        return 1;
    }
    if (board[0][2] == player_marker && board[1][1] == player_marker && board[2][0] == ' ') {
        *row = 2;
        *col = 0;
        return 1;
    }
    if (board[0][2] == player_marker && board[2][0] == player_marker && board[1][1] == ' ') {
        *row = 1;
        *col = 1;
        return 1;
    }
    if (board[1][1] == player_marker && board[2][0] == player_marker && board[0][2] == ' ') {
        *row = 0;
        *col = 2;
        return 1;
    }
    return 0;
}

void ai_move_easy(char board[3][3], char player_marker) {
    int row, col;
    srand(time(NULL));
    while (1) {
        row = rand() % 3;
        col = rand() % 3;
        if (board[row][col] == ' ') {
            board[row][col] = player_marker;
            printf("AI (Player %c) chose row %d and column %d.\n", player_marker, row + 1, col + 1);
            break;
        }
    }
}

void ai_move_hard(char board[3][3], char ai_marker, char player_marker) {
    int row, col;
    if (check_two_in_a_row(board, ai_marker, &row, &col)) {
        board[row][col] = ai_marker;
        printf("AI (Player %c) wins by moving to row %d and column %d.\n", ai_marker, row + 1, col + 1);
        return;
    }
    if (check_two_in_a_row(board, player_marker, &row, &col)) {
        board[row][col] = ai_marker;
        printf("AI (Player %c) blocks by moving to row %d and column %d.\n", ai_marker, row + 1, col + 1);
        return;
    }
    ai_move_easy(board, ai_marker);
}

void reset_score(int *player_x_wins, int *player_o_wins) {
    *player_x_wins = 0;
    *player_o_wins = 0;
    printf("Scores have been reset.\n");
}

int main() {
    char play_again;
    int player_x_wins = 0;
    int player_o_wins = 0;
    int play_with_ai;
    int difficulty_level;
    char reset_scores;

    do {
        printf("Do you want to play against AI? (1 for Yes, 0 for No): ");
        scanf("%d", &play_with_ai);

        if (play_with_ai) {
            printf("Select difficulty level (1 for Easy, 2 for Hard): ");
            scanf("%d", &difficulty_level);
        }

        char board[3][3];
        initialize_board(board);
        display_board(board);

        char current_player = 'X';
        int moves = 0;
        int win = 0;

        while (moves < 9 && !win) {
            if (play_with_ai && current_player == 'O') {
                if (difficulty_level == 1) {
                    ai_move_easy(board, current_player);
                } else {
                    ai_move_hard(board, current_player, 'X');
                }
            } else {
                player_move(board, current_player);
            }
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

        if (play_again == 'n') {
            printf("Do you want to reset the scores? (y/n): ");
            scanf(" %c", &reset_scores);
            reset_scores = tolower(reset_scores);

            if (reset_scores == 'y') {
                reset_score(&player_x_wins, &player_o_wins);
            }
        }

    } while (play_again == 'y');

    printf("Final Score:\nPlayer X: %d\nPlayer O: %d\n", player_x_wins, player_o_wins);
    printf("Thank you for playing!\n");

    return 0;
}
