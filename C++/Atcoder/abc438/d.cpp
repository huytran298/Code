#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (long long) 1e6 + 5
#define endl '\n'
#define fi first
#define se second
#define infi (int)(1e18)
#define bend(a) (a).begin(), (a).end()
#define rbend(a) (a).rbegin(), (a).rend()
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) ((a / gcd(a, b)) * b)
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define LIMIT (long long) 1e18
#define maxSelf(a, b) a = max(a, b)
#define minSelf(a, b) a = min(a, b)
#define elif else if
#define FORi(a, b, c) for(int i = a; i <= b; i += c)
#define FORj(a, b, c) for(int j = a; j <= b; j += c)
#define foreach(a) for(auto x : a)
#define pb push_back
#define mod 1000000007
int nxt(){ int n; cin >> n; return n;}
/*
 _  _             _____              
| || |_  _ _  _  |_   _| _ __ _ _ _  
| __ | || | || |   | || '_/ _` | ' \ 
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/                      
*/

signed main(){
    fast; 
    ll n;
    cin >> n;
    ll a[n + 1], b[n + 1], c[n + 1];
    for(int i = 1; i <= n; i ++)cin >> a[i];
    for(int i = 1; i <= n; i ++)cin >> b[i];
    for(int i = 1; i <= n; i ++)cin >> c[i];
    ll preA[n + 1], preB[n + 1];
    preA[0] = preB[0] = 0;
    preB[1] = b[1];
    
    for(int i = 1; i <= n; i ++)preA[i] = preA[i - 1] + a[i];
    for(int i = 2; i <= n; i ++)preB[i] = preB[i - 1] + b[i];
    ll RevPreC[n + 1];
    RevPreC[n] = c[n];
    for(int i = n - 1; i > 0; i --)RevPreC[i] = RevPreC[i + 1] + c[i];

    ll dp[n + 1];
    dp[0] = 0;
    dp[1] = a[1];
    for(int i = 2; i <= n; i ++){
        dp[i] = max(dp[i - 1] + b[i], preA[i - 1] + b[i]);
    }
    ll ans = 0;
    for(int i = 3; i <= n; i ++){
        ans = max(ans, dp[i - 1] + RevPreC[i]);
    }
    cout << ans;

}