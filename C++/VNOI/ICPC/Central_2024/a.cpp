// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define int long long
#define maxN (ll) 1e6 + 5
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
void solve(){
    ll n, W, H;
    cin >> n >> W >> H;
    vector<ll> c(n + 1), w(n + 1);
    ll sumCost = 0;
    for(int i = 1; i <= n; i ++){
        cin >> c[i] >> w[i];
        sumCost += c[i];
    }
    vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>> (sumCost + 1, array<int, 2>{infi, infi}));
    
    for(int i = 0; i <= sumCost; i ++){
        dp[0][i][0] = dp[0][i][1] = 0;
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= sumCost; j ++){
            //if(j <= c[i])continue;
            if(j > c[i])dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j - c[i]][0] + w[i]);
            //else dp[i][j][0] = dp[i - 1][j][0];
            dp[i][j][1] = min(dp[i - 1][j][1], dp[i - 1][j][0]); 
        }
    }
    ll ans = 0;
    for(int i = 1; i <= sumCost; i ++){
        if(dp[n][i][1] <= W)ans = i;
    }
    //cout << ans;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= sumCost; j ++){
            cout << dp[i][j][0] << ' ';
        }
        cout << endl;
    }
}

signed main(){
    fast; 
    ll t = 1;
   // cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}