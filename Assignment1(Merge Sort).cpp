#include <bits/stdc++.h>
using namespace std;

struct Order {
    int order_id;
    long long timestamp;
};

void mergeRuns(vector<Order> &arr, vector<Order> &aux, int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (arr[i].timestamp <= arr[j].timestamp)
            aux[k++] = arr[i++];
        else
            aux[k++] = arr[j++];
    }
    while (i < mid) aux[k++] = arr[i++];
    while (j < right) aux[k++] = arr[j++];

    for (int x = left; x < right; x++)
        arr[x] = aux[x];
}

void mergeSort(vector<Order> &arr) {
    int n = arr.size();
    if (n <= 1) return;

    vector<Order> aux(n);

    for (int width = 1; width < n; width *= 2) {
        for (int left = 0; left < n; left += 2 * width) {
            int mid = min(left + width, n);
            int right = min(left + 2 * width, n);
            mergeRuns(arr, aux, left, mid, right);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number of orders: ";
    cin >> n;

    if (!cin || n <= 0) {
        cout << "Invalid number of orders. Exiting.\n";
        return 0;
    }

    vector<Order> orders(n);

    cout << "\nEnter each order as: order_id timestamp\n";
    cout << "(Example: 101 1700000123)\n\n";

    for (int i = 0; i < n; i++) {
        cout << "Order " << i + 1 << ": ";
        cin >> orders[i].order_id >> orders[i].timestamp;
        if (!cin) {
            cout << "Invalid input detected. Exiting.\n";
            return 0;
        }
    }
    mergeSort(orders);

    cout << "\n Sorted Orders by timestamp:\n";
    for (const auto &o : orders) {
        cout << "OrderID: " << o.order_id
             << ", Timestamp: " << o.timestamp << "\n";
    }

    return 0;
}