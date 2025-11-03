#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

struct Node {
    vector<int> path;
    int cost;
    int lower_bound;
    int city;
    int level;

    bool operator>(const Node& other) const {
        return lower_bound > other.lower_bound;
    }
};

int get_min_edge(int i, int N, const vector<vector<int>>& cost_matrix) {
    int min_val = INF;
    for (int j = 0; j < N; ++j) {
        if (i != j && cost_matrix[i][j] < min_val) {
            min_val = cost_matrix[i][j];
        }
    }
    return min_val;
}

int calculate_lower_bound(const Node& node, int N,
                          const vector<vector<int>>& cost_matrix,
                          const vector<int>& min_edges) {
    
    int bound = node.cost;
    vector<bool> visited(N, false);
    for (int city_in_path : node.path) {
        visited[city_in_path] = true;
    }

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            bound += min_edges[i];
        }
    }

    int min_from_last = INF;
    for (int i = 0; i < N; ++i) {
        if (!visited[i] && cost_matrix[node.city][i] < min_from_last) {
            min_from_last = cost_matrix[node.city][i];
        }
    }

    if (min_from_last == INF) {
        min_from_last = cost_matrix[node.city][0];
    }
    bound += min_from_last;

    return bound;
}

void solveTSP(int N, const vector<vector<int>>& cost_matrix) {
    vector<int> min_edges(N);
    for (int i = 0; i < N; ++i) {
        min_edges[i] = get_min_edge(i, N, cost_matrix);
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    int global_min_cost = INF;
    vector<int> global_min_path;

    Node root;
    root.path = {0};
    root.city = 0;
    root.cost = 0;
    root.level = 1;
    root.lower_bound = 0;
    for (int val : min_edges) {
        root.lower_bound += val;
    }
    
    pq.push(root);

    while (!pq.empty()) {
        Node u = pq.top();
        pq.pop();

        if (u.lower_bound > global_min_cost) {
            continue;
        }

        if (u.level == N) {
            int cost_to_start = cost_matrix[u.city][0];
            if (cost_to_start == INF) {
                continue;
            }

            int total_cost = u.cost + cost_to_start;

            if (total_cost < global_min_cost) {
                global_min_cost = total_cost;
                global_min_path = u.path;
            }
            continue;
        }

        vector<bool> visited(N, false);
        for (int city_in_path : u.path) {
            visited[city_in_path] = true;
        }

        for (int v = 0; v < N; ++v) {
            if (!visited[v]) {
                int new_cost = u.cost + cost_matrix[u.city][v];
                if (new_cost == INF) continue;

                Node child;
                child.path = u.path;
                child.path.push_back(v);
                child.city = v;
                child.cost = new_cost;
                child.level = u.level + 1;

                child.lower_bound = calculate_lower_bound(child, N, cost_matrix, min_edges);

                if (child.lower_bound < global_min_cost) {
                    pq.push(child);
                }
            }
        }
    }

    if (global_min_cost == INF) {
        cout << "No valid solution found." << endl;
    } else {
        cout << "Optimal Cost: " << global_min_cost << endl;
        cout << "Optimal Route: ";
        for (int city : global_min_path) {
            cout << city << " -> ";
        }
        cout << "0" << endl;
    }
}

int main() {
    int N;
    cout << "Enter the number of cities: ";
    cin >> N;

    vector<vector<int>> cost_matrix(N, vector<int>(N));
    cout << "Enter the cost matrix (" << N << "x" << N << "):" << endl;
    cout << "(Use a large number like 999 for infinity/no path)" << endl;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> cost_matrix[i][j];
            if (i == j) cost_matrix[i][j] = INF;
        }
    }

    solveTSP(N, cost_matrix);

    return 0;
}