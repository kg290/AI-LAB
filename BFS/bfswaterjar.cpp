#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y;
};

// BFS to find solution path
void bfs(int cap1, int cap2, int target) {
    set<pair<int,int>> visited;
    map<pair<int,int>, pair<int,int>> parent;

    queue<pair<int,int>> q;
    q.push({0, 0});
    visited.insert({0, 0});
    parent[{0,0}] = {-1,-1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Check goal
        if (x == target || y == target) {
            cout << "Solution path:\n";

            vector<pair<int,int>> path;
            pair<int,int> cur = {x, y};

            while (cur.first != -1) {
                path.push_back(cur);
                cur = parent[cur];
            }

            reverse(path.begin(), path.end());

            for (auto &p : path)
                cout << "(" << p.first << ", " << p.second << ")\n";

            return;
        }

        // All possible moves
        vector<pair<int,int>> next = {
            {cap1, y}, // fill jar1
            {x, cap2}, // fill jar2
            {0, y},    // empty jar1
            {x, 0},    // empty jar2
            {max(0, x - (cap2 - y)), min(cap2, y + x)}, // pour 1->2
            {min(cap1, x + y), max(0, y - (cap1 - x))}  // pour 2->1
        };

        for (auto &s : next) {
            if (!visited.count(s)) {
                visited.insert(s);
                parent[s] = {x, y};
                q.push(s);
            }
        }
    }

    cout << "No solution possible\n";
}

int main() {
    int cap1 = 4, cap2 = 3, target = 2;
    bfs(cap1, cap2, target);
    return 0;
}