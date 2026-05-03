#include <bits/stdc++.h>
using namespace std;

char board[3][3];

void printBoard() {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool checkWin(char p) {
    for(int i=0;i<3;i++)
        if(board[i][0]==p && board[i][1]==p && board[i][2]==p)
            return true;

    for(int j=0;j<3;j++)
        if(board[0][j]==p && board[1][j]==p && board[2][j]==p)
            return true;

    if(board[0][0]==p && board[1][1]==p && board[2][2]==p)
        return true;

    if(board[0][2]==p && board[1][1]==p && board[2][0]==p)
        return true;

    return false;
}

int main() {
    memset(board, '-', sizeof(board));

    int r, c;

    cout << "Enter moves in order (P1 P2 P1 P2 ...):\n";

    for(int turn=0; turn<9; turn++) {

        cin >> r >> c;   // input taken continuously

        char player = (turn%2==0) ? 'X' : 'O';

        if(board[r][c] != '-') {
            cout << "Invalid move at turn " << turn+1 << "\n";
            return 0;
        }

        board[r][c] = player;

        if(checkWin(player)) {
            printBoard();
            cout << "Player " << (player=='X' ? "1" : "2") << " wins!\n";
            return 0;
        }
    }

    printBoard();
    cout << "Draw\n";
}