#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to calculate the maximum possible earnings
long long maxEarnings(int n, int k, vector<int>& a, vector<int>& b) {
    vector<pair<int, int>> customers;
    long long totalEarnings = 0;

    // Collect customers into pairs of {a[i], b[i]}
    for (int i = 0; i < n; ++i) {
        customers.push_back({a[i], b[i]});
    }

    // Sort customers by their "minimum price" a[i]
    sort(customers.begin(), customers.end());

    vector<int> penalties; // Penalties for negative reviews
    for (const auto& customer : customers) {
        int ai = customer.first;
        int bi = customer.second;

        if (bi <= ai) {
            // Always buy with a positive review
            totalEarnings += bi;
        } else {
            // Add minimum price to the total
            totalEarnings += ai;
            // Save penalty for considering a negative review
            penalties.push_back(bi - ai);
        }
    }

    // Sort penalties in descending order to maximize profit
    sort(penalties.rbegin(), penalties.rend());

    // Add penalties for up to `k` negative reviews
    for (int i = 0; i < k && i < penalties.size(); ++i) {
        totalEarnings += penalties[i];
    }

    return totalEarnings;
}

int main() {
    int t;
    cin >> t; // Number of test cases

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i]; // Read `a` array
        for (int i = 0; i < n; ++i) cin >> b[i]; // Read `b` array

        cout << maxEarnings(n, k, a, b) << endl;
    }
}
   
