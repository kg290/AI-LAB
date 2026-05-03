#include <bits/stdc++.h>
using namespace std;

int n=4, m=4;
vector<vector<int>> maze = {
    {0,1,0,0},
    {0,0,0,1},
    {1,0,1,0},
    {0,0,0,0}
};

bool vis[10][10];
map<pair<int,int>, pair<int,int>> parent;

int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};

bool dfs(int x, int y, int gx, int gy) {
    if(x==gx && y==gy) return true;

    vis[x][y]=true;

    for(int i=0;i<4;i++){
        int nx=x+dx[i], ny=y+dy[i];
        if(nx>=0 && ny>=0 && nx<n && ny<m &&
           maze[nx][ny]==0 && !vis[nx][ny]){
            parent[{nx,ny}] = {x,y};
            if(dfs(nx,ny,gx,gy)) return true;
        }
    }
    return false;
}

void print(pair<int,int> cur) {
    vector<pair<int,int>> path;
    while(parent.count(cur)){
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back({0,0});
    reverse(path.begin(), path.end());

    for(auto [x,y]:path)
        cout<<"("<<x<<","<<y<<")\n";
}

int main(){
    if(dfs(0,0,3,3)) print({3,3});
}