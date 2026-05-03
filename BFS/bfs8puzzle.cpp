#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

vector<string> getNext(string s) {
    vector<string> res;
    int idx = s.find('0');
    int x = idx / 3, y = idx % 3;

    vector<pair<int,int>> moves = {{1,0},{-1,0},{0,1},{0,-1}};

    for(auto [dx,dy] : moves) {
        int nx = x + dx, ny = y + dy;
        if(nx>=0 && nx<3 && ny>=0 && ny<3) {
            string t = s;
            swap(t[x*3+y], t[nx*3+ny]);
            res.push_back(t);
        }
    }
    return res;
}

void printPath(map<string,string> &parent, string cur) {
    vector<string> path;
    while(cur != "") {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    cout << "Solution path:\n";
    for(auto &state : path) {
        for(int i=0;i<9;i++) {
            cout << state[i] << " ";
            if(i%3==2) cout << "\n";
        }
        cout << "\n";
    }
}

void BFS(string start) {
    queue<string> q;
    unordered_set<string> visited;
    map<string,string> parent;

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    while(!q.empty()) {
        string cur = q.front();
        q.pop();

        if(cur == goal) {
            printPath(parent, cur);
            return;
        }

        for(auto &next : getNext(cur)) {
            if(!visited.count(next)) {
                visited.insert(next);
                parent[next] = cur;
                q.push(next);
            }
        }
    }

    cout << "No solution\n";
}

int main() {
    string start = "123405678"; // example input
    BFS(start);
}