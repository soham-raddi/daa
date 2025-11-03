#include <bits/stdc++.h>

using namespace std;

const long long INF = LLONG_MAX;

void dijkstra(int src, int V, const vector<vector<pair<int, int>>>& adj,
              vector<long long>& dist, vector<int>& parent) {
    
    dist.assign(V, INF);
    parent.assign(V, -1);

    dist[src] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        long long d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(int dest, const vector<int>& parent) {
    if (dest == -1) {
        cout << "Path not found." << endl;
        return;
    }

    vector<int> path;
    for (int at = dest; at != -1; at = parent[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    cout << "Optimal Route: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main() {
    int N, E;
    cout << "Enter the total number of hubs/cities (nodes): ";
    cin >> N;
    
    vector<vector<pair<int, int>>> adj(N);

    cout << "Enter the total number of routes (edges): ";
    cin >> E;

    cout << "Enter " << E << " routes (from to cost):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
    }

    int sourceNode, destNode;
    
    cout << "\nEnter Source Hub (0-" << N - 1 << "): ";
    cin >> sourceNode;

    cout << "Enter Destination Hub (0-" << N - 1 << "): ";
    cin >> destNode;

    vector<long long> dist;
    vector<int> parent;

    dijkstra(sourceNode, N, adj, dist, parent);

    if (dist[destNode] == INF) {
        cout << "\nERROR: Hub " << destNode 
             << " is unreachable from " << sourceNode << "." << endl;
    } else {
        cout << "\nOptimal Delivery Cost: " << dist[destNode] << endl;
        printPath(destNode, parent);
    }

    return 0;
}