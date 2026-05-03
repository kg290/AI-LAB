#include <bits/stdc++.h>
using namespace std;

int V = 4;          // number of vertices
int m = 3;          // number of colors

// Graph adjacency matrix
int graph[4][4] = {
    {0,1,1,1},
    {1,0,1,0},
    {1,1,0,1},
    {1,0,1,0}
};

int color[4]; // color assignment

// Check if safe to assign color c to vertex v
bool isSafe(int v, int c) {
    for(int i = 0; i < V; i++) {
        if(graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}

// Backtracking solver
bool solve(int v) {
    if(v == V) return true;

    for(int c = 1; c <= m; c++) {
        if(isSafe(v, c)) {
            color[v] = c;

            if(solve(v + 1))
                return true;

            color[v] = 0; // backtrack
        }
    }
    return false;
}

int main() {
    memset(color, 0, sizeof(color));

    if(solve(0)) {
        cout << "Coloring Solution:\n";
        for(int i = 0; i < V; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << "\n";
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}