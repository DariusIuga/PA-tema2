#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_NR_NODES = 200010;

void topologicalSortUtil(const string& node, unordered_map<string, vector<string>>& cities, unordered_map<string, bool>& visited, stack<string>& Stack) {
    visited[node] = true;
    for (const string& adj : cities[node]) {
        if (!visited[adj]) {
            topologicalSortUtil(adj, cities, visited, Stack);
        }
    }
    Stack.push(node);
}

int findLongestPath(unordered_map<string, vector<string>>& cities, const string& source, const string& destination) {
    unordered_map<string, bool> visited;
    stack<string> Stack;

    // Initialize visited map
    for (const auto& city : cities) {
        visited[city.first] = false;
    }

    // Perform topological sort
    for (const auto& city : cities) {
        if (!visited[city.first]) {
            topologicalSortUtil(city.first, cities, visited, Stack);
        }
    }

    // Initialize distances to all nodes as negative infinity
    unordered_map<string, int> dist;
    for (const auto& city : cities) {
        dist[city.first] = INT_MIN;
    }
    dist[source] = 0;

    // Process nodes in topological order
    while (!Stack.empty()) {
        string node = Stack.top();
        Stack.pop();

        if (dist[node] != INT_MIN) {
            for (const string& adj : cities[node]) {
                if (dist[adj] < dist[node] + 1) {
                    dist[adj] = dist[node] + 1;
                }
            }
        }
    }

    return dist[destination] + 1; // +1 to include the destination node itself
}

int main() {
    ios::sync_with_stdio(false);
    unordered_map<string, vector<string>> cities;
    string source, destination;
    int nr_edges;

    // Get input
    ifstream in("trenuri.in");
    in >> source >> destination >> nr_edges;
    for (int i = 0; i < nr_edges; i++) {
        string map_source, map_dest;
        in >> map_source >> map_dest;
        cities[map_source].push_back(map_dest);
    }

    int result = findLongestPath(cities, source, destination);

    // Write result
    ofstream out("trenuri.out");
    out << result;

    return 0;
}
