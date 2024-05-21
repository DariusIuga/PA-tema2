#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <climits>
#define NINF INT_MIN
using namespace std;

class AdjListNode {
    int v;
public:
    AdjListNode(int _v) { v = _v; }
    int getV() { return v; }
};

class Graph {
    int V;
    list<AdjListNode>* adj;
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);
public:
    Graph(int V);
    ~Graph();
    void addEdge(int u, int v);
    int longestPath(int s, int t);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<AdjListNode>[V];
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int u, int v) {
    AdjListNode node(v);
    adj[u].push_back(node);
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack) {
    visited[v] = true;
    for (AdjListNode node : adj[v]) {
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }
    Stack.push(v);
}

int Graph::longestPath(int s, int t) {
    stack<int> Stack;
    int* dist = new int[V];
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, Stack);

    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    while (!Stack.empty()) {
        int u = Stack.top();
        Stack.pop();
        if (dist[u] != NINF) {
            for (AdjListNode node : adj[u]) {
                if (dist[node.getV()] < dist[u] + 1)
                    dist[node.getV()] = dist[u] + 1;
            }
        }
    }

    int result = dist[t] + 1; // +1 to include the start city itself
    delete[] visited;
    delete[] dist;
    return result;
}

int main() {
    ifstream infile("trenuri.in");
    ofstream outfile("trenuri.out");

    string start_city, destination_city;
    int M;
    infile >> start_city >> destination_city >> M;

    unordered_map<string, int> city_index;
    vector<string> cities;
    vector<pair<string, string>> edges;

    for (int i = 0; i < M; i++) {
        string u, v;
        infile >> u >> v;
        edges.push_back({ u, v });
        if (city_index.find(u) == city_index.end()) {
            city_index[u] = cities.size();
            cities.push_back(u);
        }
        if (city_index.find(v) == city_index.end()) {
            city_index[v] = cities.size();
            cities.push_back(v);
        }
    }

    int V = cities.size();
    Graph g(V);
    for (const auto& edge : edges) {
        g.addEdge(city_index[edge.first], city_index[edge.second]);
    }

    int start = city_index[start_city];
    int destination = city_index[destination_city];
    int result = g.longestPath(start, destination);

    outfile << result << endl;

    infile.close();
    outfile.close();
    return 0;
}
