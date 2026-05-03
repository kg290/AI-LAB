#include <bits/stdc++.h>
using namespace std;

// Possible moves: up, down, left, right
vector<vector<int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};

// Print board
void printBoard(string s) {
    for(int i=0;i<9;i++) {
        cout << s[i] << " ";
        if(i%3==2) cout << "\n";
    }
    cout << "\n";
}

void bfs(string start, string goal) {
    queue<string> q;
    set<string> visited;
    map<string, string> parent;

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    while(!q.empty()) {
        string cur = q.front(); q.pop();

        if(cur == goal) {
            cout << "Solution path:\n";
            vector<string> path;

            while(cur != "") {
                path.push_back(cur);
                cur = parent[cur];
            }

            reverse(path.begin(), path.end());

            for(auto &state : path) {
                printBoard(state);
            }
            return;
        }

        int pos = cur.find('0'); // blank position
        int x = pos / 3;
        int y = pos % 3;

        for(auto &d : directions) {
            int nx = x + d[0];
            int ny = y + d[1];

            if(nx>=0 && nx<3 && ny>=0 && ny<3) {
                string next = cur;
                swap(next[x*3+y], next[nx*3+ny]);

                if(!visited.count(next)) {
                    visited.insert(next);
                    parent[next] = cur;
                    q.push(next);
                }
            }
        }
    }

    cout << "No solution found\n";
}

int main() {
    string start = "123405678"; // 0 = blank
    string goal  = "123456780";

    bfs(start, goal);

    return 0;
}