#include <bits/stdc++.h>
using namespace std;

int N = 8;
vector<int> board(8, -1); // board[row] = column

// Check constraints
bool isSafe(int row, int col) {
    for(int i = 0; i < row; i++) {
        int prevCol = board[i];

        // Same column or diagonal conflict
        if(prevCol == col || abs(prevCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// Backtracking (CSP solver)
bool solve(int row) {
    if(row == N) return true; // all variables assigned

    for(int col = 0; col < N; col++) {
        if(isSafe(row, col)) {
            board[row] = col;      // assign

            if(solve(row + 1))     // recurse
                return true;

            board[row] = -1;       // backtrack
        }
    }
    return false;
}

// Print solution
void printSolution() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << "\n";
    }
}

int main() {
    if(solve(0)) {
        cout << "Solution:\n";
        printSolution();
    } else {
        cout << "No solution found\n";
    }
    return 0;
}