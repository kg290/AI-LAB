#include <bits/stdc++.h>
using namespace std;

int cap1 = 4, cap2 = 3, target = 2;
int maxDepth = 3;

set<pair<int,int>> visited;
vector<pair<int,int>> path;

// Depth-Limited Search
bool dls(int x, int y, int depth) {
    if(depth > maxDepth) return false;

    if(visited.count({x,y})) return false;

    visited.insert({x,y});
    path.push_back({x,y});

    // Goal check
    if(x == target || y == target)
        return true;

    // If depth limit reached, stop expanding
    if(depth == maxDepth) {
        path.pop_back();
        return false;
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

    for(auto &s : next) {
        if(dls(s.first, s.second, depth + 1))
            return true;
    }

    // Backtrack
    path.pop_back();
    return false;
}

int main() {
    if(dls(0, 0, 0)) {
        cout << "Solution within depth 3:\n";
        for(auto &p : path)
            cout << "(" << p.first << ", " << p.second << ")\n";
    } else {
        cout << "No solution found within depth 3\n";
    }

    return 0;
}