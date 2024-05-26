#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 100'010;
constexpr int MOD = 1'000'000'007;

class Graph {
public:
    int nr_nodes;
    int nr_edges;
    vector<int> adj[MAX_NR_NODES];

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    uint64_t get_nr_total_paths() {
        // The number of path in the graph to node i is dp[i]
        vector<uint64_t> dp(nr_nodes + 1, 0);
        // There is only 1 path to the first node
        dp[1] = 1;

        // The graph is already sorted topologically (u < v, for any edge (u,v))
        for (int node = 1; node <= nr_nodes; node++) {
            for (int edge : adj[node]) {
                dp[edge] += dp[node] % MOD;
            }
        }

        // Returns the number of paths from the first node to the last one
        return dp[nr_nodes] % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);

    // Get input
    ifstream in("numarare.in");
    int nr_nodes, nr_edges;
    in >> nr_nodes >> nr_edges;

    // Create graphs with adjacency lists
    Graph graph1, graph2;
    graph1.nr_nodes = nr_nodes;
    graph1.nr_edges = nr_edges;
    graph2.nr_nodes = nr_nodes;
    graph2.nr_edges = nr_edges;

    // Add edges to graph1
    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        graph1.addEdge(x, y);
    }

    // Add edges to graph2
    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        graph2.addEdge(x, y);
    }

    // Create a graph that only has edges that are in both graphs
    Graph common_graph;
    common_graph.nr_nodes = nr_nodes;
    common_graph.nr_edges = 0;

    // Find the intersection by comparing adjacency lists
    for (int node = 1; node <= nr_nodes; node++) {
        for (int neighbor : graph1.adj[node]) {
            // Check if neighbor is also in graph2's adjacency list for node
            if (find(graph2.adj[node].begin(), graph2.adj[node].end(), neighbor) != graph2.adj[node].end()) {
                common_graph.addEdge(node, neighbor);
                common_graph.nr_edges++;
            }
        }
    }

    // Calculate total paths in the intersection graph
    uint64_t total_paths = common_graph.get_nr_total_paths();

    // Write result
    ofstream out("numarare.out");
    out << total_paths << endl;

    return 0;
}