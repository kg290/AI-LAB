#include <bits/stdc++.h>
using namespace std;

char board[3][3];

// Print board
void printBoard() {
    cout << "\n";
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Check moves left
bool isMovesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]=='-')
                return true;
    return false;
}

// Evaluate board
int evaluate() {
    // Rows
    for(int i=0;i<3;i++) {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2]) {
            if(board[i][0]=='O') return 10;
            if(board[i][0]=='X') return -10;
        }
    }

    // Columns
    for(int j=0;j<3;j++) {
        if(board[0][j]==board[1][j] && board[1][j]==board[2][j]) {
            if(board[0][j]=='O') return 10;
            if(board[0][j]=='X') return -10;
        }
    }

    // Diagonals
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) {
        if(board[0][0]=='O') return 10;
        if(board[0][0]=='X') return -10;
    }

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]) {
        if(board[0][2]=='O') return 10;
        if(board[0][2]=='X') return -10;
    }

    return 0;
}

// Minimax
int minimax(bool isMax) {
    int score = evaluate();

    if(score == 10 || score == -10)
        return score;

    if(!isMovesLeft())
        return 0;

    if(isMax) {
        int best = -1000;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]=='-') {
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]=='-') {
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = '-';
                }
            }
        }
        return best;
    }
}

// Find best move
pair<int,int> findBestMove() {
    int bestVal = -1000;
    pair<int,int> bestMove = {-1,-1};

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j]=='-') {
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = '-';

                if(moveVal > bestVal) {
                    bestMove = {i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    memset(board, '-', sizeof(board));

    cout << "Tic-Tac-Toe (You = X, AI = O)\n";

    while(true) {
        printBoard();

        int r,c;
        cout << "Enter your move (row col 0-2): ";
        cin >> r >> c;

        if(r<0 || r>2 || c<0 || c>2 || board[r][c] != '-') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[r][c] = 'X';

        if(evaluate() == -10) {
            printBoard();
            cout << "You win\n";
            break;
        }

        if(!isMovesLeft()) {
            printBoard();
            cout << "Draw\n";
            break;
        }

        cout << "AI is thinking...\n";

        pair<int,int> ai = findBestMove();
        board[ai.first][ai.second] = 'O';

        if(evaluate() == 10) {
            printBoard();
            cout << "AI wins\n";
            break;
        }

        if(!isMovesLeft()) {
            printBoard();
            cout << "Draw\n";
            break;
        }
    }

    return 0;
}