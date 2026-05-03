#include <bits/stdc++.h>
using namespace std;

int n = 5, m = 5;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Check valid cell
bool isValid(int x, int y, vector<vector<int>> &maze, vector<vector<bool>> &vis) {
    return (x >= 0 && x < n && y >= 0 && y < m &&
            maze[x][y] == 0 && !vis[x][y]);
}

// BFS function
void bfs(vector<vector<int>> &maze, pair<int,int> start, pair<int,int> goal) {
    queue<pair<int,int>> q;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    map<pair<int,int>, pair<int,int>> parent;

    q.push(start);
    vis[start.first][start.second] = true;
    parent[start] = {-1, -1};

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if(make_pair(x,y) == goal) {
            cout << "Path found:\n";

            vector<pair<int,int>> path;
            pair<int,int> cur = goal;

            while(cur.first != -1) {
                path.push_back(cur);
                cur = parent[cur];
            }

            reverse(path.begin(), path.end());

            for(auto &p : path)
                cout << "(" << p.first << ", " << p.second << ")\n";

            return;
        }

        for(int i=0;i<4;i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(isValid(nx, ny, maze, vis)) {
                vis[nx][ny] = true;
                parent[{nx, ny}] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    cout << "No path exists\n";
}

int main() {
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int,int> start = {0, 0};
    pair<int,int> goal  = {4, 4};

    bfs(maze, start, goal);

    return 0;
}