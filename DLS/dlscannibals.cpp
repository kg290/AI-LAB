#include <bits/stdc++.h>
using namespace std;

int maxDepth = 3;

struct State {
    int m, c, boat; // missionaries, cannibals, boat side (1=left, 0=right)
};

set<tuple<int,int,int>> visited;
vector<State> path;

// Check validity of state
bool isValid(int m, int c) {
    if(m < 0 || c < 0 || m > 3 || c > 3) return false;

    int m_right = 3 - m;
    int c_right = 3 - c;

    if((m > 0 && c > m) || (m_right > 0 && c_right > m_right))
        return false;

    return true;
}

// Depth-Limited Search
bool dls(State cur, int depth) {
    if(depth > maxDepth) return false;

    auto key = make_tuple(cur.m, cur.c, cur.boat);
    if(visited.count(key)) return false;

    visited.insert(key);
    path.push_back(cur);

    // Goal check
    if(cur.m == 0 && cur.c == 0 && cur.boat == 0)
        return true;

    // Stop at depth limit
    if(depth == maxDepth) {
        path.pop_back();
        return false;
    }

    // Possible moves
    vector<pair<int,int>> moves = {
        {1,0}, {2,0},
        {0,1}, {0,2},
        {1,1}
    };

    for(auto &mv : moves) {
        State next;

        if(cur.boat == 1) // left → right
            next = {cur.m - mv.first, cur.c - mv.second, 0};
        else              // right → left
            next = {cur.m + mv.first, cur.c + mv.second, 1};

        if(isValid(next.m, next.c)) {
            if(dls(next, depth + 1))
                return true;
        }
    }

    // Backtrack
    path.pop_back();
    return false;
}

int main() {
    State start = {3,3,1};

    if(dls(start, 0)) {
        cout << "Solution within depth 3:\n";
        for(auto &s : path) {
            cout << "(M=" << s.m
                 << ", C=" << s.c
                 << ", Boat=" << (s.boat ? "Left" : "Right")
                 << ")\n";
        }
    } else {
        cout << "No solution found within depth 3\n";
    }

    return 0;
}