#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 100'010;
constexpr int MOD = 1'000'000'007;

// Define a hash function for std::pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // or use another combination method
    }
};

// Function to find the intersection of two unordered sets of pairs
std::unordered_set<std::pair<int, int>, pair_hash> intersection(
    const std::unordered_set<std::pair<int, int>, pair_hash>& set1,
    const std::unordered_set<std::pair<int, int>, pair_hash>& set2) {

    std::unordered_set<std::pair<int, int>, pair_hash> result;
    for (const auto& elem : set1) {
        if (set2.find(elem) != set2.end()) {
            result.insert(elem);
        }
    }
    return result;
}

class Graph {
public:
    int nr_nodes;
    int nr_edges;
    vector<int> adj[MAX_NR_NODES];

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // vector<vector<int>> allPathsSourceTarget() {
    //     vector<vector<vector<int>>> dp(nr_nodes + 1);
    //     dp[1].push_back({ 1 });

    //     for (int u = 1; u <= nr_nodes; u++) {
    //         for (int v : adj[u]) {
    //             for (auto path : dp[u]) {
    //                 path.push_back(v);
    //                 dp[v].push_back(path);
    //             }
    //         }
    //         // Erase all the paths to the current node to free up memory
    //         dp[u].clear();
    //         dp[u].shrink_to_fit();
    //     }

    //     return dp[nr_nodes];
    // }

    uint64_t get_nr_total_paths() {
        // The number of path in the graph to node i is dp[i]
        vector<uint64_t> dp(nr_nodes + 1, 0);
        // There is only 1 path to the first node
        dp[1] = 1;

        // The graph is already sorted topologically (u < v, for any edge (u,v))
        for (int node = 1;node <= nr_nodes;node++) {
            for (int edge : adj[node]) {
                dp[edge] += dp[node] % MOD;
            }
        }

        // Returns the number of paths from the first node to the last one
        return dp[nr_nodes] % MOD;
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

    unordered_set<pair<int, int>, pair_hash> edges1;
    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        edges1.insert({ x, y });
    }

    unordered_set<pair<int, int>, pair_hash> edges2;
    for (int i = 0; i < nr_edges; i++) {
        int x, y;
        in >> x >> y;
        edges2.insert({ x, y });
    }

    // Create a graph that only contains edges that are in both graphs
    Graph common_graph;
    common_graph.nr_nodes = nr_nodes;
    common_graph.nr_edges = nr_edges;

    // Get the intersection of edges frpm both graphs
    auto common_edges = intersection(edges1, edges2);

    // Add edges to the graph's adjacency list
    for (const auto& edge : common_edges) {
        common_graph.addEdge(edge.first, edge.second);
        // std::cout << "{" << edge.first << ", " << edge.second << "} ";
    }
    // std::cout << std::endl;

    uint64_t result = common_graph.get_nr_total_paths();

    // Write result
    ofstream out("numarare.out");
    out << result << endl;

    return 0;
}
