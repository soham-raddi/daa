#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

void dijkstra(int src, int V, const vector<vector<pair<int, int>>>& adj,
              vector<int>& dist, vector<int>& parent) {
    
    dist.assign(V, INF);
    parent.assign(V, -1);

    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
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

    cout << "Optimal Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of intersections (nodes): ";
    cin >> V;
    
    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter the number of roads (edges): ";
    cin >> E;

    cout << "Enter road details (from to time) for " << E << " roads:" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Assuming roads are two-way
    }

    int ambulanceLocation, hospitalLocation;
    
    cout << "\nEnter Ambulance Location (Intersection 0-" << V - 1 << "): ";
    cin >> ambulanceLocation;

    cout << "Enter Hospital Location (Intersection 0-" << V - 1 << "): ";
    cin >> hospitalLocation;

    vector<int> dist;
    vector<int> parent;

    dijkstra(ambulanceLocation, V, adj, dist, parent);

    if (dist[hospitalLocation] == INF) {
        cout << "\nERROR: Hospital at intersection " << hospitalLocation 
             << " is unreachable." << endl;
    } else {
        cout << "\nShortest Time to Hospital " << hospitalLocation << " is: "
             << dist[hospitalLocation] << " minutes." << endl;
        
        printPath(hospitalLocation, parent);
    }

    return 0;
}