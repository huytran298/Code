
#include<bits/stdc++.h>
using namespace std;

long long atMostK(vector<long long> &arr, long long k) {
    long long n = arr.size();
    long long res = 0;

    // polong longers to mark the left and right boundary
    long long left = 0, right = 0;

    // Frequency map
    unordered_map<long long, long long> freq;
    while (right < n) {
        freq[arr[right]] += 1;

        // If this is a new element in the window,
        // decrement k by 1
        if (freq[arr[right]] == 1)
            k -= 1;

        // Shrink the window until distinct element
        // count becomes <= k
        while (k < 0) {
            freq[arr[left]] -= 1;
            if (freq[arr[left]] == 0)
                k += 1;
            left += 1;
        }

        // add all possible subarrays to result
        res += (right - left + 1);
        right += 1;
    }
    return res;
}

long long exactlyK(vector<long long> &arr, long long k) {
    return atMostK(arr, k) - atMostK(arr, k - 1);
}


int main() {
    long long t;
    cin >> t;
    while(t --){
        long long n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for(auto &x : a){
            cin >> x;
        }
        cout << exactlyK(a, k) << endl;
    }
}