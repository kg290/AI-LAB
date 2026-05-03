#include <bits/stdc++.h>
using namespace std;

map<char, vector<pair<char,int>>> g;
map<char,int> h = {
    {'A',10},{'B',8},{'C',5},{'D',7},{'E',3},{'F',6},{'G',0}
};

struct Node{
    char v; int h;
    bool operator<(const Node &o)const{
        return h>o.h;
    }
};

int main(){
    g['A']={{'B',1},{'C',1}};
    g['B']={{'D',1},{'E',1}};
    g['C']={{'F',1}};
    g['E']={{'G',1}};
    g['F']={{'G',1}};

    priority_queue<Node> pq;
    set<char> vis;

    pq.push({'A',h['A']});

    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();
        if(vis.count(cur.v)) continue;
        vis.insert(cur.v);

        cout<<cur.v<<" ";

        if(cur.v=='G'){
            cout<<"\nGoal reached\n";
            return 0;
        }

        for(auto &n:g[cur.v])
            if(!vis.count(n.first))
                pq.push({n.first,h[n.first]});
    }
}