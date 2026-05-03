#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

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

// DFS function
bool dfs(string state) {
    if(visited.count(state)) return false;

    visited.insert(state);
    path.push_back(state);

    if(state == goal) return true;

    int pos = state.find('0');
    int x = pos / 3;
    int y = pos % 3;

    for(auto &d : dirs) {
        int nx = x + d[0];
        int ny = y + d[1];

        if(nx>=0 && nx<3 && ny>=0 && ny<3) {
            string next = state;
            swap(next[x*3 + y], next[nx*3 + ny]);

            if(dfs(next)) return true;
        }
    }

    path.pop_back(); // backtrack
    return false;
}

int main() {
    string start = "123405678"; // initial state

    if(dfs(start)) {
        cout << "Solution path:\n";
        for(auto &s : path) {
            printBoard(s);
        }
    } else {
        cout << "No solution found\n";
    }

    return 0;
}