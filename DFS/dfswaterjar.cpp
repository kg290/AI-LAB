#include <bits/stdc++.h>
using namespace std;

set<pair<int,int>> vis;
map<pair<int,int>, pair<int,int>> parent;

int J1 = 4, J2 = 3, target = 2;

bool dfs(int x, int y) {
    if(vis.count({x,y})) return false;
    vis.insert({x,y});

    if(x == target || y == target) return true;

    vector<pair<int,int>> next;

    next.push_back({J1, y});
    next.push_back({x, J2});
    next.push_back({0, y});
    next.push_back({x, 0});

    int pour = min(x, J2 - y);
    next.push_back({x - pour, y + pour});

    pour = min(y, J1 - x);
    next.push_back({x + pour, y - pour});

    for(auto [nx,ny] : next) {
        if(!vis.count({nx,ny})) {
            parent[{nx,ny}] = {x,y};
            if(dfs(nx,ny)) return true;
        }
    }
    return false;
}

void print(pair<int,int> cur) {
    vector<pair<int,int>> path;
    while(parent.count(cur)) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back({0,0});
    reverse(path.begin(), path.end());

    for(auto [x,y] : path)
        cout << "(" << x << "," << y << ")\n";
}

int main() {
    parent.clear();
    if(dfs(0,0)) {
        for(auto &p: vis){
            if(p.first==target || p.second==target){
                print(p);
                break;
            }
        }
    }
}