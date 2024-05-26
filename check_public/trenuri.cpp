#include <bits/stdc++.h>
using namespace std;

void topo_sort(const string& node, unordered_map<string, vector<string>>& neigh_cities, unordered_map<string, bool>& visited, stack<string>& node_stack) {
    visited[node] = true;

    for (const string& adj : neigh_cities[node]) {
        if (!visited[adj]) {
            topo_sort(adj, neigh_cities, visited, node_stack);
        }
    }
    node_stack.push(node);
}

int get_longest_path_length(unordered_map<string, vector<string>>& neigh_cities, const string& source, const string& destination) {
    unordered_map<string, bool> visited;
    stack<string> node_stack;

    // Initialize visited map
    for (const auto& city : neigh_cities) {
        visited[city.first] = false;
    }

    // Initialize distances to all nodes as negative infinity
    unordered_map<string, int> dist;
    for (const auto& city : neigh_cities) {
        dist[city.first] = INT_MIN;
    }
    // The distance to the source is 1 (include the source itself)
    dist[source] = 1;

    // Perform topological sort
    for (const auto& city : neigh_cities) {
        if (!visited[city.first]) {
            topo_sort(city.first, neigh_cities, visited, node_stack);
        }
    }

    // Process nodes in topological order (as they were put in the stack)
    while (!node_stack.empty()) {
        string node = node_stack.top();
        node_stack.pop();

        if (dist[node] != INT_MIN) {
            for (const string& adj : neigh_cities[node]) {
                // Update the distance if it is greater
                if (dist[adj] < dist[node] + 1) {
                    dist[adj] = dist[node] + 1;
                }
            }
        }
    }

    return dist[destination];
}

int main() {
    ios::sync_with_stdio(false);
    // Adjacency list for a city
    unordered_map<string, vector<string>> neigh_cities;
    string source, destination;
    int nr_edges;

    // Get input
    ifstream in("trenuri.in");
    in >> source >> destination >> nr_edges;
    for (int i = 0; i < nr_edges; i++) {
        string map_source, map_dest;
        in >> map_source >> map_dest;
        neigh_cities[map_source].push_back(map_dest);
    }

    // Get the length of the longest path
    int result = get_longest_path_length(neigh_cities, source, destination);

    // Write result
    ofstream out("trenuri.out");
    out << result;

    return 0;
}
