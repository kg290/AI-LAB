#include <bits/stdc++.h>
using namespace std;

// Check if placing queen is safe
bool isSafe(vector<int> &state, int row, int col) {
    for(int i = 0; i < row; i++) {
        int prevCol = state[i];

        // Same column or diagonal
        if(prevCol == col || abs(prevCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// BFS function
void bfs() {
    queue<vector<int>> q;

    // Start with empty state
    q.push({});

    while(!q.empty()) {
        vector<int> state = q.front();
        q.pop();

        int row = state.size();

        // If all 8 queens placed
        if(row == 4) {
            cout << "Solution:\n";
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    if(state[i] == j) cout << "Q ";
                    else cout << ". ";
                }
                cout << "\n";
            }
            return;
        }

        // Try placing queen in each column
        for(int col = 0; col < 4; col++) {
            if(isSafe(state, row, col)) {
                vector<int> next = state;
                next.push_back(col);
                q.push(next);
            }
        }
    }

    cout << "No solution found\n";
}

int main() {
    bfs();
    return 0;
}