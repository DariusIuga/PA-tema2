#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 100010;

vector<long long> dijkstra(int source, vector<vector<pair<int, int>>>& adj) {
    vector<long long> dist(adj.size(), LONG_LONG_MAX);
    dist[source] = 0;

    // The priority queue should prioritize nodes by their current shortest distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, source });

    while (pq.empty() == false) {
        int node_dist = pq.top().first;
        int node_nr = pq.top().second;
        pq.pop();

        // If this distance is not the current shortest, skip processing
        if (node_dist > dist[node_nr]) continue;

        for (auto& neigh : adj[node_nr]) {
            int neigh_node = neigh.first;
            int edge_weight = neigh.second;

            if (dist[neigh_node] > dist[node_nr] + edge_weight) {
                dist[neigh_node] = dist[node_nr] + edge_weight;
                pq.push({ dist[neigh_node], neigh_node });
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);

    // Read input
    ifstream in("drumuri.in");
    int nr_nodes, nr_edges;
    in >> nr_nodes >> nr_edges;
    vector<vector<pair<int, int>>> adj(nr_nodes + 1), transpose_adj(nr_nodes + 1);
    for (int i = 0; i < nr_edges; i++) {
        int source, dest, weight;
        in >> source >> dest >> weight;
        adj[source].push_back({ dest, weight });
        transpose_adj[dest].push_back({ source, weight });
    }

    // Read the nodes x, y and z
    int x, y, z;
    in >> x >> y >> z;

    vector<long long> dist_from_x = dijkstra(x, adj);
    vector<long long> dist_from_y = dijkstra(y, adj);
    vector<long long> dist_to_z = dijkstra(z, transpose_adj);

    // Find the minimum cost to go from x to z and y to z via any common node
    long long minimum_cost_path = LONG_LONG_MAX;
    for (int node = 1;node <= nr_nodes;node++)
    {
        if (dist_to_z[node] != LONG_LONG_MAX && dist_from_x[node] != LONG_LONG_MAX && dist_from_y[node] != LONG_LONG_MAX) {
            minimum_cost_path = min(minimum_cost_path, dist_from_x[node] + dist_from_y[node] + dist_to_z[node]);
        }
    }

    // Write result
    ofstream out("drumuri.out");
    if (minimum_cost_path == LONG_LONG_MAX) {
        // There is no path from x to z and from y to z
        out << -1 << endl;
    }
    else {
        out << minimum_cost_path << endl;
    }

    return 0;
}
