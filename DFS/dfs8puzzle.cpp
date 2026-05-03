#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";
set<string> vis;
map<string,string> parent;

vector<string> moves(string s) {
    vector<string> res;
    int i = s.find('0');
    int x = i/3, y = i%3;

    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};

    for(int k=0;k<4;k++){
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && nx<3 && ny>=0 && ny<3){
            string t=s;
            swap(t[x*3+y], t[nx*3+ny]);
            res.push_back(t);
        }
    }
    return res;
}

bool dfs(string cur) {
    if(vis.count(cur)) return false;
    vis.insert(cur);

    if(cur == goal) return true;

    for(auto nxt : moves(cur)) {
        if(!vis.count(nxt)) {
            parent[nxt] = cur;
            if(dfs(nxt)) return true;
        }
    }
    return false;
}

void print(string cur) {
    vector<string> path;
    while(parent.count(cur)) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(cur);
    reverse(path.begin(), path.end());

    for(auto s: path){
        for(int i=0;i<9;i++){
            cout<<s[i]<<" ";
            if(i%3==2) cout<<"\n";
        }
        cout<<"\n";
    }
}

int main() {
    string start = "123405678";
    if(dfs(start)) print(goal);
}