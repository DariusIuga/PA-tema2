#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 100010;

int dijkstra(int source, int dest, vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(adj.size(), INT_MAX);
    dist[source] = 0;

    // The priority queue should prioritize nodes by their current shortest distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, source });

    while (!pq.empty()) {
        int node_dist = pq.top().first;
        int node_nr = pq.top().second;
        pq.pop();

        // If this distance is not the current shortest, skip processing
        // if (node_dist > dist[node_nr]) continue;

        for (auto& neigh : adj[node_nr]) {
            int neigh_node = neigh.first;
            int edge_weight = neigh.second;

            if (dist[neigh_node] > dist[node_nr] + edge_weight) {
                dist[neigh_node] = dist[node_nr] + edge_weight;
                pq.push({ dist[neigh_node], neigh_node });
            }
        }
    }

    return dist[dest];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    ifstream in("drumuri.in");
    int nr_nodes, nr_edges;
    in >> nr_nodes >> nr_edges;
    vector<vector<pair<int, int>>> adj(nr_nodes + 1);
    for (int i = 0; i < nr_edges; i++) {
        int source, dest, weight;
        in >> source >> dest >> weight;
        adj[source].emplace_back(dest, weight);
    }

    // Read the nodes x, y and z
    int x, y, z;
    in >> x >> y >> z;

    int dist_x_z = dijkstra(x, z, adj);
    int dist_y_z = dijkstra(y, z, adj);

    // Write result
    ofstream out("drumuri.out");
    if (dist_x_z == INT_MAX || dist_y_z == INT_MAX) {
        out << -1;
    }
    else {
        out << dist_x_z + dist_y_z;
    }

    return 0;
}
