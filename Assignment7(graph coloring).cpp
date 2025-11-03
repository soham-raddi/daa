#include <bits/stdc++.h>

using namespace std;

int main() {
    int V, E;
    cout << "Enter the number of courses (vertices): ";
    cin >> V;
    cout << "Enter the number of conflicts (edges): ";
    cin >> E;

    vector<vector<int>> adj(V);
    cout << "Enter " << E << " conflicts (course1 course2, 0-indexed):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        if (u >= V || v >= V || u < 0 || v < 0) {
            cout << "Invalid input: Courses must be between 0 and " << (V - 1) << endl;
            i--;
            continue;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> result(V, -1);
    result[0] = 0;
    int maxColorUsed = 0;

    for (int u = 1; u < V; u++) {
        vector<bool> available(V, true);

        for (int v : adj[u]) {
            if (result[v] != -1) {
                available[result[v]] = false;
            }
        }

        int cr = 0;
        while (cr < V) {
            if (available[cr]) {
                break;
            }
            cr++;
        }

        result[u] = cr;
        if (cr > maxColorUsed) {
            maxColorUsed = cr;
        }
    }

    cout << "\n--- Exam Timetable ---" << endl;
    cout << "Total time slots needed: " << maxColorUsed + 1 << endl;
    for (int u = 0; u < V; ++u) {
        cout << "Course " << u << ": Time Slot " << result[u] << endl;
    }

    return 0;
}