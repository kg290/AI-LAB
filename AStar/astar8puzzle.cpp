#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

// Manhattan distance heuristic
int heuristic(string s) {
    int dist = 0;
    for(int i = 0; i < 9; i++) {
        if(s[i] == '0') continue;
        int val = s[i] - '1';
        int gx = val / 3;
        int gy = val % 3;

        int x = i / 3;
        int y = i % 3;

        dist += abs(x - gx) + abs(y - gy);
    }
    return dist;
}

// Node structure
struct Node {
    string state;
    int g, h;

    bool operator<(const Node &other) const {
        return (g + h) > (other.g + other.h); // min-heap
    }
};

// Print board
void printBoard(string s) {
    for(int i=0;i<9;i++) {
        cout << s[i] << " ";
        if(i % 3 == 2) cout << "\n";
    }
    cout << "\n";
}

void aStar(string start) {
    priority_queue<Node> pq;
    set<string> visited;
    map<string,string> parent;
    map<string,int> gCost;

    pq.push({start, 0, heuristic(start)});
    gCost[start] = 0;
    parent[start] = "";

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if(cur.state == goal) {
            cout << "Optimal solution path:\n";
            vector<string> path;

            string temp = cur.state;
            while(temp != "") {
                path.push_back(temp);
                temp = parent[temp];
            }

            reverse(path.begin(), path.end());

            for(auto &s : path)
                printBoard(s);

            return;
        }

        if(visited.count(cur.state)) continue;
        visited.insert(cur.state);

        int pos = cur.state.find('0');
        int x = pos / 3, y = pos % 3;

        vector<vector<int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};

        for(auto &d : dirs) {
            int nx = x + d[0];
            int ny = y + d[1];

            if(nx>=0 && nx<3 && ny>=0 && ny<3) {
                string next = cur.state;
                swap(next[x*3+y], next[nx*3+ny]);

                int newG = cur.g + 1;

                if(!gCost.count(next) || newG < gCost[next]) {
                    gCost[next] = newG;
                    parent[next] = cur.state;
                    pq.push({next, newG, heuristic(next)});
                }
            }
        }
    }

    cout << "No solution found\n";
}

int main() {
    string start = "123405678";
    aStar(start);
    return 0;
}