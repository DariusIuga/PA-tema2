#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 100010;

class Graph {
    vector<int> adj[MAX_NR_NODES];

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    unordered_set<string> countPaths(int V, int source, int destination) {
        vector<unordered_set<string>> dp(V + 1);
        dp[source].insert(to_string(source));

        for (int u = 1; u <= V; ++u) {
            for (int v : adj[u]) {
                for (const string& path : dp[u]) {
                    dp[v].insert(path + "->" + to_string(v));
                }
            }
        }

        return dp[destination];
    }
};

unordered_set<string> getCommonPaths(const unordered_set<string>& paths1, const unordered_set<string>& paths2) {
    unordered_set<string> commonPaths;
    for (const auto& path : paths1) {
        if (paths2.find(path) != paths2.end()) {
            commonPaths.insert(path);
        }
    }
    return commonPaths;
}

int main() {
    ifstream in("numarare.in");
    int nr_nodes, nr_edges;
    in >> nr_nodes >> nr_edges;

    Graph graph1, graph2;

    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        graph1.addEdge(x, y);
    }

    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        graph2.addEdge(x, y);
    }

    unordered_set<string> pathsGraph1 = graph1.countPaths(nr_nodes, 1, nr_nodes);
    unordered_set<string> pathsGraph2 = graph2.countPaths(nr_nodes, 1, nr_nodes);

    unordered_set<string> commonPaths = getCommonPaths(pathsGraph1, pathsGraph2);

    ofstream out("numarare.out");
    out << commonPaths.size() << endl;
    return 0;
}
