#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";
int maxDepth = 3;

set<string> visited;
vector<string> path;

// Directions: up, down, left, right
vector<vector<int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};

// Print board
void printBoard(string s) {
    for(int i=0;i<9;i++) {
        cout << s[i] << " ";
        if(i % 3 == 2) cout << "\n";
    }
    cout << "\n";
}

// Depth-Limited Search
bool dls(string state, int depth) {
    if(depth > maxDepth) return false;

    if(visited.count(state)) return false;

    visited.insert(state);
    path.push_back(state);

    // Goal check
    if(state == goal) return true;

    // Stop if depth limit reached
    if(depth == maxDepth) {
        path.pop_back();
        return false;
    }

    int pos = state.find('0');
    int x = pos / 3;
    int y = pos % 3;

    for(auto &d : dirs) {
        int nx = x + d[0];
        int ny = y + d[1];

        if(nx>=0 && nx<3 && ny>=0 && ny<3) {
            string next = state;
            swap(next[x*3 + y], next[nx*3 + ny]);

            if(dls(next, depth + 1))
                return true;
        }
    }

    // Backtrack
    path.pop_back();
    return false;
}

int main() {
    string start = "123405678"; // initial state

    if(dls(start, 0)) {
        cout << "Solution within depth 3:\n";
        for(auto &s : path) {
            printBoard(s);
        }
    } else {
        cout << "No solution found within depth 3\n";
    }

    return 0;
}