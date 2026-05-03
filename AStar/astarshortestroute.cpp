#include <bits/stdc++.h>
using namespace std;

map<char, vector<pair<char,int>>> g;
map<char,int> h = {
    {'A',10},{'B',8},{'C',5},{'D',7},{'E',3},{'F',6},{'G',0}
};

struct Node{
    char v; int g,f;
    bool operator<(const Node &o)const{
        return f>o.f;
    }
};

int main(){
    g['A']={{'B',1},{'C',4}};
    g['B']={{'D',2},{'E',5}};
    g['C']={{'F',1}};
    g['D']={{'G',7}};
    g['E']={{'G',2}};
    g['F']={{'G',3}};

    priority_queue<Node> pq;
    map<char,int> dist;
    map<char,char> parent;   // <-- store path

    pq.push({'A',0,h['A']});
    dist['A']=0;
    parent['A'] = '-'; // start marker

    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();

        if(cur.v=='G'){
            cout<<"Cost: "<<cur.g<<"\n";

            // reconstruct path
            vector<char> path;
            char node = 'G';
            while(node != '-'){
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());

            cout<<"Path: ";
            for(char c : path) cout<<c<<" ";
            cout<<"\n";

            return 0;
        }

        for(auto &n:g[cur.v]){
            int ng=cur.g+n.second;
            if(!dist.count(n.first)||ng<dist[n.first]){
                dist[n.first]=ng;
                parent[n.first]=cur.v;   // <-- track parent
                pq.push({n.first,ng,ng+h[n.first]});
            }
        }
    }
}