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
    printf("  1   2   3 \n");
    printf("1 %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf(" ---|---|---\n");
    printf("2 %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf(" ---|---|---\n");
    printf("3 %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int is_board_full(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int is_valid_move(char board[3][3], int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

void player_move(char board[3][3], char player_marker) {
    int row, col;
    while (1) {
        printf("Player %c's turn. Enter row (1-3) and column (1-3): ", player_marker);
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            while (getchar() != '\n');
            continue;
        }
        row--;
        col--;
        if (!is_valid_move(board, row, col)) {
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

void save_game(char board[3][3], char current_player, int moves, int player_x_wins, int player_o_wins) {
    FILE *file = fopen("tic_tac_toe_save.txt", "w");
    if (file == NULL) {
        printf("Failed to save game.\n");
        return;
    }
    fprintf(file, "%c\n%d\n%d\n%d\n", current_player, moves, player_x_wins, player_o_wins);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fprintf(file, "%c ", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Game saved successfully.\n");
}

int load_game(char board[3][3], char *current_player, int *moves, int *player_x_wins, int *player_o_wins) {
    FILE *file = fopen("tic_tac_toe_save.txt", "r");
    if (file == NULL) {
        printf("No saved game found.\n");
        return 0;
    }
    fscanf(file, " %c\n%d\n%d\n%d\n", current_player, moves, player_x_wins, player_o_wins);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fscanf(file, " %c", &board[i][j]);
        }
    }
    fclose(file);
    printf("Game loaded successfully.\n");
    return 1;
}

void display_statistics(int player_x_wins, int player_o_wins) {
    printf("Game Statistics:\n");
    printf("Player X wins: %d\n", player_x_wins);
    printf("Player O wins: %d\n", player_o_wins);
}

int main() {
    char play_again;
    int player_x_wins = 0;
    int player_o_wins = 0;
    int play_with_ai;
    int difficulty_level;
    char reset_scores;
    char load_saved_game;
    char save_game_choice;

    printf("Do you want to load the saved game? (y/n): ");
    scanf(" %c", &load_saved_game);
    load_saved_game = tolower(load_saved_game);

    char board[3][3];
    char current_player = 'X';
    int moves = 0;
    if (load_saved_game == 'y') {
        if (!load_game(board, &current_player, &moves, &player_x_wins, &player_o_wins)) {
            initialize_board(board);
        }
    } else {
        initialize_board(board);
    }

    do {
        printf("Do you want to play against AI? (1 for Yes, 0 for No): ");
        scanf("%d", &play_with_ai);
        if (play_with_ai) {
            printf("Select difficulty level (1 for Easy, 2 for Hard): ");
            scanf("%d", &difficulty_level);
        }

        display_board(board);

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

            printf("Do you want to save the game? (y/n): ");
            scanf(" %c", &save_game_choice);
            save_game_choice = tolower(save_game_choice);
            if (save_game_choice == 'y') {
                save_game(board, current_player, moves, player_x_wins, player_o_wins);
            }
        }

        if (!win) {
            printf("It's a tie!\n");
        }

        display_statistics(player_x_wins, player_o_wins);

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
        } else {
            initialize_board(board);
            current_player = 'X';
            moves = 0;
        }

    } while (play_again == 'y');

    printf("Final Score:\nPlayer X: %d\nPlayer O: %d\n", player_x_wins, player_o_wins);
    printf("Thank you for playing!\n");

    return 0;
}
