#include <bits/stdc++.h>
using namespace std;

int n = 4;      // number of vertices
int m = 3;      // number of colors

vector<vector<int>> graph = {
    {0,1,1,1},
    {1,0,1,0},
    {1,1,0,1},
    {1,0,1,0}
};

vector<int> color(10, 0);

bool isSafe(int node, int c) {
    for(int i = 0; i < n; i++) {
        if(graph[node][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

bool solve(int node) {
    if(node == n) return true;

    for(int c = 1; c <= m; c++) {
        if(isSafe(node, c)) {
            color[node] = c;

            if(solve(node + 1)) return true;

            color[node] = 0; // backtrack
        }
    }
    return false;
}

int main() {
    if(solve(0)) {
        cout << "Color Assignment:\n";
        for(int i = 0; i < n; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << "\n";
    } else {
        cout << "No solution\n";
    }
}