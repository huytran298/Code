#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include <string>
#include <climits>

using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Generate all possible next states by modifying one digit
vector<pair<int, int>> generateNextStates(int num) {
    vector<pair<int, int>> nextStates;
    string s = to_string(num);

    for (int i = 0; i < s.size(); i++) {
        char original = s[i];

        // Increment the digit if it's not 9
        if (s[i] < '9') {
            s[i]++;
            int newNum = stoi(s);
            if (!isPrime(newNum)) {
                nextStates.emplace_back(newNum, 1); // Cost is 1 for increment
            }
            s[i] = original; // Restore the digit
        }

        // Decrement the digit if it's not 0
        if (s[i] > '0') {
            s[i]--;
            int newNum = stoi(s);
            if (!isPrime(newNum)) {
                nextStates.emplace_back(newNum, 1); // Cost is 1 for decrement
            }
            s[i] = original; // Restore the digit
        }
    }

    return nextStates;
}

// Function to find the minimum cost to transform n to m
int minCostTransform(int n, int m) {
    if (isPrime(n)) return -1;

    queue<pair<int, int>> q; // {current number, cumulative cost}
    set<int> visited;       // Track visited numbers to avoid cycles
    q.push({n, 0});
    visited.insert(n);

    while (!q.empty()) {
        auto [current, cost] = q.front();
        q.pop();

        // If we reach the target number, return the cost
        if (current == m) return cost;

        // Generate next states and process them
        for (auto [next, stepCost] : generateNextStates(current)) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push({next, cost + stepCost});
            }
        }
    }

    return -1; // If no transformation is possible
}

int main() {
    int n = 10, m = 12;
    cout << minCostTransform(n, m) << endl; // Expected output: 85
    return 0;
}
