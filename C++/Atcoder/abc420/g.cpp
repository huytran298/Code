#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long X; 
    if (!(cin >> X)) return 0;

    long long N = 1 - 4 * X;          // odd
    long long M = llabs(N);

    vector<long long> ans;

    // i runs over odd positive divisors of |N|
    auto process = [&](long long i) {
        long long sum = i + N / i;            // a + b with a=i, b=N/i
        // (sum - 2) is always divisible by 4 for odd a,b when N ≡ 1 (mod 4)
        long long n1 = (sum - 2) / 4;
        long long n2 = -n1 - 1;               // symmetric counterpart
        ans.push_back(n1);
        ans.push_back(n2);
    };

    // i = 1 separately, then odd i >= 3
    if (M % 1 == 0) process(1);
    for (long long i = 3; i * i <= M; i += 2) {
        if (M % i == 0) {
            process(i);                       // covers pair (i, N/i)
            // no need to process M/i separately; it gives same sum
        }
    }
    // If M is a perfect square with odd root r, i=r was already processed.

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
