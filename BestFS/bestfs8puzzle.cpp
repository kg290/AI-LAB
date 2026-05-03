#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

int h(string s) {
    int cnt = 0;
    for (int i = 0; i < 9; i++)
        if (s[i] != '0' && s[i] != goal[i])
            cnt++;
    return cnt;
}

vector<string> neighbors(string s) {
    vector<string> res;
    int i = s.find('0');
    int x = i / 3, y = i % 3;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            string t = s;
            swap(t[x * 3 + y], t[nx * 3 + ny]);
            res.push_back(t);
        }
    }
    return res;
}

struct Node {
    string state;
    int cost;
    bool operator<(const Node &other) const {
        return cost > other.cost; // min-heap
    }
};

void bestFirst(string start) {
    priority_queue<Node> pq;
    unordered_set<string> vis;
    map<string, string> parent;

    pq.push({start, h(start)});
    parent[start] = "";

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if (vis.count(cur.state)) continue;
        vis.insert(cur.state);

        if (cur.state == goal) {
            vector<string> path;
            string t = goal;
            while (t != "") {
                path.push_back(t);
                t = parent[t];
            }
            reverse(path.begin(), path.end());

            for (auto &s : path) {
                for (int i = 0; i < 9; i++) {
                    cout << s[i] << " ";
                    if (i % 3 == 2) cout << "\n";
                }
                cout << "\n";
            }
            return;
        }

        for (auto &nxt : neighbors(cur.state)) {
            if (!vis.count(nxt)) {
                parent[nxt] = cur.state;
                pq.push({nxt, h(nxt)});
            }
        }
    }

    cout << "No solution\n";
}

int main() {
    string start = "123405678";
    bestFirst(start);
}