#include <bits/stdc++.h>
using namespace std;

struct State {
    int ML, CL, B;
};

bool isValid(int ML, int CL) {
    int MR = 3 - ML;
    int CR = 3 - CL;

    if(ML < 0 || CL < 0 || ML > 3 || CL > 3) return false;

    if(ML > 0 && ML < CL) return false;
    if(MR > 0 && MR < CR) return false;

    return true;
}

void printPath(map<tuple<int,int,int>, tuple<int,int,int>> &parent,
               tuple<int,int,int> cur) {

    vector<tuple<int,int,int>> path;

    while(parent[cur] != make_tuple(-1,-1,-1)) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(make_tuple(3,3,0));

    reverse(path.begin(), path.end());

    cout << "Solution Path:\n";
    for(auto [ml,cl,b] : path) {
        cout << "ML=" << ml << " CL=" << cl
             << " | MR=" << 3-ml << " CR=" << 3-cl
             << " | Boat=" << (b==0?"Left":"Right") << "\n";
    }
}

void BFS() {
    queue<tuple<int,int,int>> q;
    set<tuple<int,int,int>> vis;
    map<tuple<int,int,int>, tuple<int,int,int>> parent;

    tuple<int,int,int> start = {3,3,0};
    tuple<int,int,int> goal  = {0,0,1};

    q.push(start);
    vis.insert(start);
    parent[start] = {-1,-1,-1};

    vector<pair<int,int>> moves = {
        {1,0},{2,0},{0,1},{0,2},{1,1}
    };

    while(!q.empty()) {
        auto [ML,CL,B] = q.front();
        q.pop();

        if(make_tuple(ML,CL,B) == goal) {
            printPath(parent, goal);
            return;
        }

        for(auto [m,c] : moves) {
            int nML = ML, nCL = CL, nB;

            if(B == 0) {
                nML = ML - m;
                nCL = CL - c;
                nB = 1;
            } else {
                nML = ML + m;
                nCL = CL + c;
                nB = 0;
            }

            if(isValid(nML, nCL)) {
                auto next = make_tuple(nML,nCL,nB);
                if(!vis.count(next)) {
                    vis.insert(next);
                    parent[next] = {ML,CL,B};
                    q.push(next);
                }
            }
        }
    }

    cout << "No solution\n";
}

int main() {
    BFS();
}