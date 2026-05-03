#include <bits/stdc++.h>
using namespace std;

int n = 5, m = 5;

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

// DFS function
bool dfs(int x, int y, int gx, int gy) {
    // Check bounds and validity
    if(x < 0 || y < 0 || x >= n || y >= m ||
       maze[x][y] == 1 || visited[x][y])
        return false;

    // Mark visited and add to path
    visited[x][y] = true;
    path.push_back({x, y});

    // Goal reached
    if(x == gx && y == gy)
        return true;

    // Explore all directions
    for(int i=0;i<4;i++) {
        if(dfs(x + dx[i], y + dy[i], gx, gy))
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

    if(dfs(start.first, start.second, goal.first, goal.second)) {
        cout << "Path found:\n";
        for(auto &p : path)
            cout << "(" << p.first << ", " << p.second << ")\n";
    } else {
        cout << "No path found\n";
    }

    return 0;
}