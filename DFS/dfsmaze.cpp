#include <iostream>
using namespace std;

int n = 3;
int m = 3;

int maze[3][3] = {
    {0, 0, 1},
    {0, 0, 0},
    {1, 0, 0}
};

bool visited[3][3];

int path[100][2];
int path_len = 0;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool is_valid(int x, int y)
{
    if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y])
    {
        return true;
    }
    return false;
}

bool dfs(int x, int y)
{
    visited[x][y] = true;

    path[path_len][0] = x;
    path[path_len][1] = y;
    path_len++;

    if (x == n - 1 && y == m - 1)
    {
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if (is_valid(new_x, new_y))
        {
            if (dfs(new_x, new_y))
            {
                return true;
            }
        }
    }

    path_len--;
    return false;
}
/*Time = O(n × m)
Space = O(n × m)
Time = O(b^d)
Space = O(b × d)*/
int main()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = false;
        }
    }

    if (dfs(0, 0))
    {
        cout << "Path exists:\n";
        for (int i = 0; i < path_len; i++)
        {
            cout << "(" << path[i][0] << "," << path[i][1] << ") ";
        }
        cout << "\n";
    }
    else
    {
        cout << "No path found.\n";
    }

    return 0;
}