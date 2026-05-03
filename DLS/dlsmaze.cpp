#include <bits/stdc++.h>
using namespace std;

int n = 5, m = 5;
int maxDepth = 3;

// Maze: 0 = free, 1 = blocked
vector<vector<int>> maze = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0}
};

bool visited[5][5];
vector<pair<int,int>> path;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Depth-Limited Search
bool dls(int x, int y, int gx, int gy, int depth) {
    if(depth > maxDepth) return false;

    if(x < 0 || y < 0 || x >= n || y >= m ||
       maze[x][y] == 1 || visited[x][y])
        return false;

    visited[x][y] = true;
    path.push_back({x, y});

    // Goal check
    if(x == gx && y == gy)
        return true;

    // Stop if depth limit reached
    if(depth == maxDepth) {
        path.pop_back();
        return false;
    }

    for(int i=0;i<4;i++) {
        if(dls(x + dx[i], y + dy[i], gx, gy, depth + 1))
            return true;
    }

    // Backtrack
    path.pop_back();
    return false;
}

int main() {
    memset(visited, false, sizeof(visited));

    pair<int,int> start = {0, 0};
    pair<int,int> goal  = {4, 4};

    if(dls(start.first, start.second, goal.first, goal.second, 0)) {
        cout << "Path found within depth 3:\n";
        for(auto &p : path)
            cout << "(" << p.first << ", " << p.second << ")\n";
    } else {
        cout << "No path found within depth 3\n";
    }

    return 0;
}