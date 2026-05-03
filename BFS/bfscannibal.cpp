#include <bits/stdc++.h>
using namespace std;

struct State {
    int m, c, boat; // missionaries, cannibals, boat side (1=left,0=right)
};

// Check if state is valid
bool isValid(int m, int c) {
    if(m < 0 || c < 0 || m > 3 || c > 3) return false;

    int m_right = 3 - m;
    int c_right = 3 - c;

    if((m > 0 && c > m) || (m_right > 0 && c_right > m_right))
        return false;

    return true;
}

void bfs() {
    queue<State> q;
    map<tuple<int,int,int>, tuple<int,int,int>> parent;
    set<tuple<int,int,int>> visited;

    State start = {3,3,1};
    State goal  = {0,0,0};

    q.push(start);
    visited.insert({3,3,1});
    parent[{3,3,1}] = {-1,-1,-1};

    // Possible moves: (m,c)
    vector<pair<int,int>> moves = {
        {1,0}, {2,0}, // missionaries
        {0,1}, {0,2}, // cannibals
        {1,1}         // both
    };

    while(!q.empty()) {
        State cur = q.front(); q.pop();

        if(cur.m == 0 && cur.c == 0 && cur.boat == 0) {
            cout << "Solution path:\n";

            vector<tuple<int,int,int>> path;
            auto t = make_tuple(cur.m, cur.c, cur.boat);

            while(get<0>(t) != -1) {
                path.push_back(t);
                t = parent[t];
            }

            reverse(path.begin(), path.end());

            for(auto &s : path) {
                cout << "(M=" << get<0>(s)
                     << ", C=" << get<1>(s)
                     << ", Boat=" << (get<2>(s)==1?"Left":"Right")
                     << ")\n";
            }
            return;
        }

        for(auto &mv : moves) {
            int m = cur.m;
            int c = cur.c;
            int b = cur.boat;

            State next;

            if(b == 1) { // boat on left → move to right
                next = {m - mv.first, c - mv.second, 0};
            } else {     // boat on right → move to left
                next = {m + mv.first, c + mv.second, 1};
            }

            if(isValid(next.m, next.c)) {
                auto key = make_tuple(next.m, next.c, next.boat);
                if(!visited.count(key)) {
                    visited.insert(key);
                    parent[key] = make_tuple(m, c, b);
                    q.push(next);
                }
            }
        }
    }

    cout << "No solution found\n";
}

int main() {
    bfs();
    return 0;
}