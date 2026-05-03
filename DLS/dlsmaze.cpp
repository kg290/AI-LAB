#include <iostream>
using namespace std;

int n = 2;
int m = 2;

int maze[2][2] = {
    {0, 0},
    {0, 0}
};

bool visited[2][2];

int path[100][2];
int path_len = 0;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int max_depth = 3;

// Check valid cell
bool is_valid(int x, int y)
{
    return (x >= 0 && x < n &&
            y >= 0 && y < m &&
            maze[x][y] == 0 &&
            !visited[x][y]);
}

// Depth-Limited Search
bool dls(int x, int y, int depth)
{
    // Stop at depth limit
    if (depth > max_depth)
        return false;

    visited[x][y] = true;

    path[path_len][0] = x;
    path[path_len][1] = y;
    path_len++;

    // Goal reached
    if (x == n - 1 && y == m - 1)
        return true;

    // Explore neighbors
    for (int i = 0; i < 4; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if (is_valid(new_x, new_y))
        {
            if (dls(new_x, new_y, depth + 1))
                return true;
        }
    }

    // Backtrack (IMPORTANT FIX)
    visited[x][y] = false;
    path_len--;

    return false;
}

int main()
{
    // Initialize visited
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            visited[i][j] = false;

    if (dls(0, 0, 0))
    {
        cout << "Path exists within depth limit:\n";
        for (int i = 0; i < path_len; i++)
        {
            cout << "(" << path[i][0] << "," << path[i][1] << ") ";
        }
        cout << "\n";
    }
    else
    {
        cout << "No path found within depth limit.\n";
    }

    return 0;
}