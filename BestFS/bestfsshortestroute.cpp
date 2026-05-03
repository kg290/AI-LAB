#include <bits/stdc++.h>
using namespace std;

// Graph (Adjacency List)
map<string, vector<pair<string,int>>> graph = {
    {"A", {{"B", 1}, {"C", 3}}},
    {"B", {{"A", 1}, {"D", 1}, {"E", 4}}},
    {"C", {{"A", 3}, {"F", 5}}},
    {"D", {{"B", 1}}},
    {"E", {{"B", 4}, {"F", 1}}},
    {"F", {{"C", 5}, {"E", 1}}}
};

// Heuristic (estimated distance to goal "F")
map<string,int> h = {
    {"A", 5},
    {"B", 3},
    {"C", 4},
    {"D", 6},
    {"E", 1},
    {"F", 0}
};

// Node for priority queue
struct Node {
    string city;
    int hval;

    bool operator<(const Node &other) const {
        return hval > other.hval; // min-heap
    }
};

void bestFirstSearch(string start, string goal) {
    priority_queue<Node> pq;
    set<string> visited;
    map<string,string> parent;

    pq.push({start, h[start]});
    visited.insert(start);
    parent[start] = "";

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if(cur.city == goal) {
            cout << "Path found:\n";
            vector<string> path;

            string temp = goal;
            while(temp != "") {
                path.push_back(temp);
                temp = parent[temp];
            }

            reverse(path.begin(), path.end());

            for(auto &c : path)
                cout << c << " ";

            cout << "\n";
            return;
        }

        for(auto &nbr : graph[cur.city]) {
            string next = nbr.first;

            if(!visited.count(next)) {
                visited.insert(next);
                parent[next] = cur.city;
                pq.push({next, h[next]});
            }
        }
    }

    cout << "No path found\n";
}

int main() {
    bestFirstSearch("A", "F");
    return 0;
}