#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
const ll INF = numeric_limits<ll>::max();

void dijkstra(int start, const vector<vector<pii>>& adj, vector<ll>& dist) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (cost > dist[node]) continue;

        for (const auto &edge : adj[node]) {
            int nextNode = edge.first;
            int nextCost = edge.second;
            if (dist[node] + nextCost < dist[nextNode]) {
                dist[nextNode] = dist[node] + nextCost;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }
}

int main() {
    ifstream infile("drumuri.in");
    ofstream outfile("drumuri.out");

    int N, M;
    infile >> N >> M;

    vector<vector<pii>> adj(N + 1), reverseAdj(N + 1);

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        infile >> a >> b >> c;
        adj[a].push_back({b, c});
        reverseAdj[b].push_back({a, c});
    }

    int x, y, z;
    infile >> x >> y >> z;

    // Distance arrays
    vector<ll> distFromX(N + 1, INF);
    vector<ll> distFromY(N + 1, INF);
    vector<ll> distToZ(N + 1, INF);

    // Run Dijkstra's from x, y and z (in reversed graph)
    dijkstra(x, adj, distFromX);
    dijkstra(y, adj, distFromY);
    dijkstra(z, reverseAdj, distToZ);

    // Find the minimum cost to go from x to z and y to z via any common node
    ll minCost = INF;
    for (int i = 1; i <= N; ++i) {
        if (distFromX[i] != INF && distFromY[i] != INF && distToZ[i] != INF) {
            minCost = min(minCost, distFromX[i] + distFromY[i] + distToZ[i]);
        }
    }

    if (minCost == INF) {
        outfile << -1 << endl;
    } else {
        outfile << minCost << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}
