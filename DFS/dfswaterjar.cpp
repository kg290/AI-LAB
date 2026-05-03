#include <bits/stdc++.h>
using namespace std;

int cap1 = 4, cap2 = 3, target = 2;

set<pair<int,int>> visited;
vector<pair<int,int>> path;

// DFS function
bool dfs(int x, int y) {
    // If already visited, skip
    if(visited.count({x,y})) return false;

    // Mark visited and add to path
    visited.insert({x,y});
    path.push_back({x,y});

    // Check goal
    if(x == target || y == target)
        return true;

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
        if(dfs(s.first, s.second))
            return true;
    }

    // Backtrack
    path.pop_back();
    return false;
}

int main() {
    if(dfs(0,0)) {
        cout << "Solution path:\n";
        for(auto &p : path)
            cout << "(" << p.first << ", " << p.second << ")\n";
    } else {
        cout << "No solution found\n";
    }
    return 0;
}