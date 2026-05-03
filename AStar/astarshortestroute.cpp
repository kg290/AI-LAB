#include <bits/stdc++.h>
using namespace std;

// Graph (Adjacency list: node -> {neighbor, cost})
map<string, vector<pair<string,int>>> graph = {
    {"A", {{"B", 1}, {"C", 4}}},
    {"B", {{"A", 1}, {"D", 2}, {"E", 5}}},
    {"C", {{"A", 4}, {"F", 3}}},
    {"D", {{"B", 2}}},
    {"E", {{"B", 5}, {"F", 1}}},
    {"F", {{"C", 3}, {"E", 1}}}
};

// Heuristic values (estimate to goal "F")
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
    int g, h;

    bool operator<(const Node &other) const {
        return (g + h) > (other.g + other.h); // min-heap
    }
};

void aStar(string start, string goal) {
    priority_queue<Node> pq;
    map<string,int> gCost;
    map<string,string> parent;
    set<string> visited;

    pq.push({start, 0, h[start]});
    gCost[start] = 0;
    parent[start] = "";

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if(cur.city == goal) {
            cout << "Optimal path:\n";
            vector<string> path;

            string temp = goal;
            while(temp != "") {
                path.push_back(temp);
                temp = parent[temp];
            }

            reverse(path.begin(), path.end());

            for(auto &c : path)
                cout << c << " ";

            cout << "\nTotal cost: " << gCost[goal] << "\n";
            return;
        }

        if(visited.count(cur.city)) continue;
        visited.insert(cur.city);

        for(auto &nbr : graph[cur.city]) {
            string next = nbr.first;
            int cost = nbr.second;

            int newG = gCost[cur.city] + cost;

            if(!gCost.count(next) || newG < gCost[next]) {
                gCost[next] = newG;
                parent[next] = cur.city;
                pq.push({next, newG, h[next]});
            }
        }
    }

    cout << "No path found\n";
}

int main() {
    aStar("A", "F");
    return 0;
}