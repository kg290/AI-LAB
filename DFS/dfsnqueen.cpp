#include <bits/stdc++.h>
using namespace std;

int N = 8;
vector<int> board(8, -1); // board[row] = column

// Check if safe to place queen
bool isSafe(int row, int col) {
    for(int i = 0; i < row; i++) {
        int prevCol = board[i];

        // Same column or diagonal attack
        if(prevCol == col || abs(prevCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// DFS (backtracking)
bool dfs(int row) {
    // All queens placed
    if(row == N) return true;

    for(int col = 0; col < N; col++) {
        if(isSafe(row, col)) {
            board[row] = col;

            if(dfs(row + 1))
                return true;

            // Backtrack
            board[row] = -1;
        }
    }
    return false;
}

int main() {
    if(dfs(0)) {
        cout << "Solution:\n";
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(board[i] == j) cout << "Q ";
                else cout << ". ";
            }
            cout << "\n";
        }
    } else {
        cout << "No solution found\n";
    }
    return 0;
}