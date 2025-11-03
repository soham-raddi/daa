#include <bits/stdc++.h>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    bool isDivisible;
    double valuePerKg;
};

bool compareItems(const Item& a, const Item& b) {
    return a.valuePerKg > b.valuePerKg;
}

double fractionalKnapsack(double W, vector<Item>& items) {
    for (auto& item : items) {
        item.valuePerKg = item.value / item.weight;
    }

    sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    cout << "\n--- Boat Loading Plan ---" << endl;

    for (const auto& item : items) {
        double remainingWeight = W - currentWeight;

        if (remainingWeight == 0) {
            break;
        }

        if (item.weight <= remainingWeight) {
            currentWeight += item.weight;
            totalValue += item.value;
            cout << "Took 100% of " << item.name 
                 << " (Weight: " << item.weight << "kg, Value: " << item.value << ")" << endl;
        }
        else if (item.isDivisible) {
            double fraction = remainingWeight / item.weight;
            double valueTaken = item.value * fraction;
            
            currentWeight += remainingWeight;
            totalValue += valueTaken;
            
            cout << "Took " << fixed << setprecision(1) << (fraction * 100.0) 
                 << "% of " << item.name 
                 << " (Weight: " << remainingWeight << "kg, Value: " << valueTaken << ")" << endl;
        }
        else {
            cout << "SKIPPED " << item.name 
                 << " (Weight: " << item.weight << "kg) - Not divisible and too heavy." << endl;
        }
    }

    cout << "-------------------------" << endl;
    return totalValue;
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        cout << "--- Item " << i + 1 << " ---" << endl; 
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, items[i].name);
        
        cout << "Weight: ";
        cin >> items[i].weight;
        
        cout << "Value: ";
        cin >> items[i].value;
        
        char divisibleChar;
        cout << "Is it divisible? (y/n): ";
        cin >> divisibleChar;
        items[i].isDivisible = (divisibleChar == 'y' || divisibleChar == 'Y');
    }

    double W;
    cout << "\nEnter the boat's maximum weight capacity (W in kg): ";
    cin >> W;

    double maxValue = fractionalKnapsack(W, items);

    cout << "\nMaximum total utility value: " << fixed << setprecision(2) << maxValue << endl;

    return 0;
}