/* tictactoe.c
   Tic-Tac-Toe with Minimax AI (unbeatable)
   Compile: gcc -O2 -std=c11 tictactoe.c -o tictactoe
   Run: ./tictactoe
*/

#include <stdio.h>
#include <stdlib.h>

#define HUMAN 'X'
#define AI    'O'
#define EMPTY ' '

/* Board is 3x3 */
char board[3][3];

/* Function prototypes */
void init_board();
void print_board();
int is_moves_left();
int evaluate();
int minimax(int depth, int isMax);
void best_move(int *best_r, int *best_c);
void human_move();
int check_winner();
void play_game();

int main() {
    printf("Tic-Tac-Toe: You (X) vs AI (O)\n");
    printf("Enter moves as row and column numbers (1-3) separated by space.\n\n");
    play_game();
    return 0;
}

/* Initialize board to empty */
void init_board() {
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            board[i][j] = EMPTY;
}

/* Print the board nicely */
void print_board() {
    printf("\n  1   2   3\n");
    for (int i=0;i<3;i++) {
        printf("%d ", i+1);
        for (int j=0;j<3;j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  ---+---+---\n");
    }
    printf("\n");
}

/* Return 1 if there are moves left */
int is_moves_left() {
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (board[i][j] == EMPTY)
                return 1;
    return 0;
}

/* Evaluate board:
   +10 if AI wins
   -10 if HUMAN wins
   0 otherwise
*/
int evaluate() {
    // Rows
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == HUMAN) return -10;
        }
    }
    // Columns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == HUMAN) return -10;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == HUMAN) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == HUMAN) return -10;
    }
    return 0;
}

/* Minimax algorithm */
int minimax(int depth, int isMax) {
    int score = evaluate();

    // If AI has won the game, return evaluated score
    if (score == 10) return score - depth; // prefer fast wins
    if (score == -10) return score + depth; // prefer slow losses

    // If no moves left, it's a tie
    if (!is_moves_left()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int val = minimax(depth+1, 0);
                    board[i][j] = EMPTY;
                    if (val > best) best = val;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    int val = minimax(depth+1, 1);
                    board[i][j] = EMPTY;
                    if (val < best) best = val;
                }
            }
        }
        return best;
    }
}

/* Compute best move for AI */
void best_move(int *best_r, int *best_c) {
    int bestVal = -1000;
    *best_r = -1;
    *best_c = -1;

    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(0, 0);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    *best_r = i;
                    *best_c = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

/* Ask human for move and validate */
void human_move() {
    int r, c;
    while (1) {
        printf("Your move (row col): ");
        if (scanf("%d %d", &r, &c) != 2) {
            // clear invalid input
            while (getchar() != '\n');
            printf("Invalid input. Please enter two numbers 1-3.\n");
            continue;
        }
        if (r < 1 || r > 3 || c < 1 || c > 3) {
            printf("Coordinates out of range. Use 1 to 3.\n");
            continue;
        }
        r--; c--;
        if (board[r][c] != EMPTY) {
            printf("Cell already occupied. Pick another.\n");
            continue;
        }
        board[r][c] = HUMAN;
        break;
    }
}

/* Check winner:
   returns 1 if HUMAN won, 2 if AI won, 0 otherwise (no winner yet)
*/
int check_winner() {
    int val = evaluate();
    if (val == -10) return 1;
    if (val == 10) return 2;
    return 0;
}

/* Main game loop */
void play_game() {
    init_board();
    print_board();

    int choice;
    printf("Do you want to play first or second? (1 = first, 2 = second): ");
    while (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        while (getchar() != '\n');
        printf("Enter 1 (first) or 2 (second): ");
    }

    int humanTurn = (choice == 1) ? 1 : 0;
    int winner = 0;

    while (1) {
        if (humanTurn) {
            human_move();
        } else {
            int r, c;
            best_move(&r, &c);
            if (r == -1 || c == -1) {
                // fallback: pick first empty (shouldn't happen with minimax)
                for (int i=0;i<3 && r==-1;i++)
                    for (int j=0;j<3 && r==-1;j++)
                        if (board[i][j] == EMPTY) { r=i; c=j; }
            }
            board[r][c] = AI;
            printf("AI plays: %d %d\n", r+1, c+1);
        }

        print_board();
        winner = check_winner();
        if (winner == 1) {
            printf("You win! Congratulations 🎉\n");
            break;
        } else if (winner == 2) {
            printf("AI wins. Better luck next time!\n");
            break;
        } else if (!is_moves_left()) {
            printf("It's a draw.\n");
            break;
        }

        humanTurn = !humanTurn;
    }
}
