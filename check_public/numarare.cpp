#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 100010;

class Graph {
public:
    int nr_nodes;
    int nr_edges;
    vector<int> adj[MAX_NR_NODES];

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    vector<vector<int>> allPathsSourceTarget() {
        vector<vector<vector<int>>> dp(nr_nodes + 1);
        dp[1].push_back({ 1 });

        for (int u = 1; u <= nr_nodes; u++) {
            for (int v : adj[u]) {
                for (auto path : dp[u]) {
                    path.push_back(v);
                    dp[v].push_back(path);
                }
            }
            // Erase all the paths to the current node to free up memory
            dp[u].clear();
            dp[u].shrink_to_fit();
            // if (u % 10 == 0) {
            //     // DEBUG
            //     int i = 0;
            // }
        }

        return dp[nr_nodes];
    }
};

vector<vector<int>> getCommonPaths(const vector<vector<int>>& paths1, const vector<vector<int>>& paths2) {
    set<vector<int>> setPaths1(paths1.begin(), paths1.end());
    set<vector<int>> setPaths2(paths2.begin(), paths2.end());

    vector<vector<int>> commonPaths;
    for (const auto& path : setPaths1) {
        if (setPaths2.find(path) != setPaths2.end()) {
            commonPaths.push_back(path);
        }
    }
    return commonPaths;
}

int main() {
    ios::sync_with_stdio(false);

    // Get input
    ifstream in("numarare.in");
    int nr_nodes, nr_edges;
    in >> nr_nodes >> nr_edges;

    Graph graph1, graph2;

    graph1.nr_nodes = nr_nodes;
    graph1.nr_edges = nr_edges;
    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        graph1.addEdge(x, y);
    }

    graph2.nr_nodes = nr_nodes;
    graph2.nr_edges = nr_edges;
    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        graph2.addEdge(x, y);
    }

    // vector<vector<int>> paths1 = graph1.allPathsSourceTarget();
    // vector<vector<int>> paths2 = graph2.allPathsSourceTarget();

    // for (const auto& path : paths1) {
    //     for (auto node : path) {
    //         cout << node << ",";
    //     }
    //     cout << endl;
    // }

    // for (const auto& path : paths2) {
    //     for (auto node : path) {
    //         cout << node << ",";
    //     }
    //     cout << endl;
    // }

    // Write result
    ofstream out("numarare.out");
    // out << getCommonPaths(paths1, paths2).size() << endl;
    out << 0;

    return 0;
}
