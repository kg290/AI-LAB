#include <bits/stdc++.h>
using namespace std;

char board[3][3];

void printBoard() {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) cout << board[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]=='-') return true;
    return false;
}

int evaluate() {
    for(int i=0;i<3;i++) {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2]) {
            if(board[i][0]=='O') return 10;
            if(board[i][0]=='X') return -10;
        }
    }
    for(int j=0;j<3;j++) {
        if(board[0][j]==board[1][j] && board[1][j]==board[2][j]) {
            if(board[0][j]=='O') return 10;
            if(board[0][j]=='X') return -10;
        }
    }
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

// Minimax (simple, no tricks)
int minimax(bool isMax) {
    int score = evaluate();
    if(score == 10 || score == -10) return score;
    if(!isMovesLeft()) return 0;

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

    string line;
    getline(cin, line);   // ← FIX: stable input

    stringstream ss(line);
    vector<int> input;
    int x;

    while(ss >> x) input.push_back(x);

    if(input.size() % 2 != 0) {
        cout << "Invalid input\n";
        return 0;
    }

    int moves = input.size()/2;

    if(moves < 1) {
        cout << "Input insufficient\n";
        return 0;
    }

    for(int i=0;i<moves;i++) {

        int r = input[2*i];
        int c = input[2*i+1];

        if(r<0 || r>2 || c<0 || c>2 || board[r][c] != '-') {
            cout << "Invalid move\n";
            return 0;
        }

        // Player
        board[r][c] = 'X';
        cout << "Player move:\n";
        printBoard();

        if(evaluate() == -10) {
            cout << "Player wins\n";
            return 0;
        }

        if(!isMovesLeft()) break;

        // AI
        pair<int,int> ai = findBestMove();
        board[ai.first][ai.second] = 'O';

        cout << "AI move:\n";
        printBoard();

        if(evaluate() == 10) {
            cout << "AI wins\n";
            return 0;
        }

        if(!isMovesLeft()) break;
    }

    cout << "Draw\n";
    return 0;
}