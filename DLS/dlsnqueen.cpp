#include <bits/stdc++.h>
using namespace std;

int N = 4;
int maxDepth = 3;

vector<int> board(8, -1); // board[row] = column
bool found = false;

// Check if safe
bool isSafe(int row, int col) {
    for(int i = 0; i < row; i++) {
        int prevCol = board[i];
        if(prevCol == col || abs(prevCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// Depth-Limited Search
void dls(int row) {
    if(row > maxDepth) return;

    // If reached depth limit, print partial state
    if(row == maxDepth) {
        cout << "Partial solution (depth 3):\n";
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < N; j++) {
                if(board[i] == j) cout << "Q ";
                else cout << ". ";
            }
            cout << "\n";
        }
        cout << "\n";
        return;
    }

    for(int col = 0; col < N; col++) {
        if(isSafe(row, col)) {
            board[row] = col;
            dls(row + 1);
            board[row] = -1; // backtrack
        }
    }
}

int main() {
    dls(0);
    return 0;
}