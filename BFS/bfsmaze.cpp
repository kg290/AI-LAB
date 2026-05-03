#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

#define ROW 5
#define COL 5

struct Node {
    int x, y, dist;
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y, int maze[ROW][COL], bool visited[ROW][COL]) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL &&
            maze[x][y] == 1 && !visited[x][y]);
}

void bfs(int maze[ROW][COL], int sx, int sy, int dx1, int dy1) {

    bool visited[ROW][COL] = {false};
    pair<int,int> parent[ROW][COL];

    queue<Node> q;

    q.push({sx, sy, 0});
    visited[sx][sy] = true;
    parent[sx][sy] = {-1, -1};

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        if (curr.x == dx1 && curr.y == dy1) {

            cout << "Shortest Path Length: " << curr.dist << "\n";

            // Reconstruct path
            vector<pair<int,int>> path;
            int x = dx1, y = dy1;

            while (x != -1) {
                path.push_back({x, y});
                auto p = parent[x][y];
                x = p.first;
                y = p.second;
            }

            reverse(path.begin(), path.end());

            cout << "Path:\n";
            for (auto &p : path) {
                cout << "(" << p.first << "," << p.second << ") ";
            }

            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (isValid(nx, ny, maze, visited)) {
                visited[nx][ny] = true;
                parent[nx][ny] = {curr.x, curr.y};
                q.push({nx, ny, curr.dist + 1});
            }
        }
    }

    cout << "No path exists";
}

int main() {

    int maze[ROW][COL] = {
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1}
    };

    int startX = 0, startY = 0;
    int endX = 4, endY = 4;

    bfs(maze, startX, startY, endX, endY);

    return 0;
}