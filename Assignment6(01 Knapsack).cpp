#include <bits/stdc++.h>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

void solveKnapsack(int W, const vector<Item>& items) {
    int N = items.size();

    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        string name = items[i - 1].name;
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;

        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];

            if (wt <= w) {
                dp[i][w] = max(dp[i][w], val + dp[i - 1][w - wt]);
            }
        }
    }

    int maxUtility = dp[N][W];
    cout << "\n--- Optimal Manifest ---" << endl;
    cout << "Maximum Utility Value: " << maxUtility << endl;
    cout << "Total Weight: ";

    vector<Item> packedItems;
    int totalPackedWeight = 0;
    int w = W;

    for (int i = N; i > 0 && maxUtility > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            const Item& item = items[i - 1];
            packedItems.push_back(item);
            
            maxUtility -= item.value;
            w -= item.weight;
            totalPackedWeight += item.weight;
        }
    }

    cout << totalPackedWeight << " / " << W << " kg" << endl;
    cout << "\nItems to Pack:" << endl;
    for (const auto& item : packedItems) {
        cout << "  - " << item.name << " (Weight: " << item.weight 
             << ", Value: " << item.value << ")" << endl;
    }
}

int main() {
    int N;
    cout << "Enter the number of available item types: ";
    cin >> N;

    vector<Item> items(N);
    for (int i = 0; i < N; ++i) {
        cout << "\n--- Item " << i + 1 << " ---" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, items[i].name);
        cout << "Weight: ";
        cin >> items[i].weight;
        cout << "Utility Value: ";
        cin >> items[i].value;
    }

    int W;
    cout << "\nEnter the truck's maximum weight capacity (W): ";
    cin >> W;

    solveKnapsack(W, items);

    return 0;
}