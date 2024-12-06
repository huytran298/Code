#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <bitset>
#include <stack>
#include <queue>
#include <map>
#include <time.h>
using namespace std;
#define MAX 1048580 // 2^20 + 4
int sumSubset[MAX] = { 0 };
vector<int> checkRes;
bool solve(int n, int k, int num, int value) {
    if (num == (1 << n) - 1 && checkRes.size() <= k)
        return true;
    if (value == 0)
        return false;
    for (int i = 0; i < (1 << n); i++) {
        if ((sumSubset[i] == value) && ((i & num) == 0)) {
            checkRes.push_back(i);
            if (solve(n, k, num + i, value))
                return true;
            else
                checkRes.pop_back();
        }
    }
    if (solve(n, k, num, value - 1))
        return true;
    return false;
}
void isSubsetMaxSum(vector<int>& arr, int  sum, vector<int>& res) {
    size_t n = arr.size();
	vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < arr[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    for (int j = 1; j <= sum; j++) {
        if (j < arr[n - 1]) {
            dp[n][j] = dp[n - 1][j];
        }
        else {
            dp[n][j] = dp[n - 1][j] || dp[n - 1][j - arr[n - 1]];
        }
        if (dp[n][j])
            res.push_back(j);
    }
}
void isSubsetSum(vector<int>& arr, int sum, vector<int>& res) {
    size_t n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < arr[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    int maxSum = 0;
    for (int j = 1; j <= sum; j++) {
        if (j < arr[n - 1]) {
            dp[n][j] = dp[n - 1][j];
        }
        else {
            dp[n][j] = dp[n - 1][j] || dp[n - 1][j - arr[n - 1]];
        }
        if (dp[n][j])
            maxSum = j;
    }
    for (int i = n; i >= 1; i--) {
        if (dp[i - 1][maxSum] == 0) {
            res.push_back(i - 1);
            maxSum -= arr[i - 1];
        }
        if (maxSum == 0)
            break;
    }
}
int main() {
    time_t t;
    srand((unsigned)time(&t));
    for (int tc = 0; tc < 100000; tc++) {
        cout << "Test case: " << tc + 1 << "\n";
        int k = rand() % 5 + 2;
        int n = 12;
        cout << k << " " << n << endl;
        vector<int> arr;
        int sum = 0;
        while (arr.size() < n) {
            int temp = 1 + rand() % 20;
            sum += temp;
            arr.push_back(temp);
        }
        //int k;
        //int n;
        //vector<int>arr;
        //int sum = 0;
        //cin >> k >> n;
        //int x;
        //for (int i = 0; i < n; i++) {
        //    cin >> x;
        //    arr.push_back(x);
        //    sum += arr[i];
        //}
        sort(arr.begin(), arr.end(), greater<int>());
        for (auto x : arr)
            cout << x << " ";
        cout << endl;
        vector<int> sumList;
        isSubsetMaxSum(arr, sum, sumList);
        sumList.push_back(1000000000);
        int l = 0, r = sumList.size() - 1, m;
        while (l < r) {
            m = (l + r) / 2;
            vector<int> temp = arr;
            int cnt = 0;
            while (!temp.empty()) {
                vector<int> tempRes;
                isSubsetSum(temp, sumList[m], tempRes);
                if (!tempRes.empty()) {
                    for (auto x : tempRes)
                        temp.erase(temp.begin() + x);
                    cnt++;
                }
                else {
                    cnt = k + 1;
                    break;
                }
            }
            if (cnt <= k)
                r = m;
            else
                l = m + 1;
        }
        int ans = sumList[l];
        cout << ans << endl;
        for (int i = 0; i < (1 << n); i++) {
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                    sumSubset[i] += arr[j];
        }
        while (!arr.empty()) {
            vector<int> res;
            isSubsetSum(arr, ans, res);
            if (!res.empty()) {
                for (auto x : res) {
                    cout << arr[x] << " ";
                    arr.erase(arr.begin() + x);
                }
                cout << endl;
            }
            else
                break;
        }

        if (solve(n, k, 0, ans - 1)){
            cout << "False\n";
            break;
        }
            
        else
            cout << "True\n";
    }
    
    return 0;
}