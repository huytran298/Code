// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
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
    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> pre(n + 1, vector<ll> (n + 1, 0));
    char map[n + 1][n + 1];
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            cin >> map[i][j];
            pre[i][j] = pre[i][j - 1] + (pre[i - 1][j] - pre[i - 1][j - 1]) + (map[i][j] == '*');
        }
    }
    
    while(q --){
        ll u, v, x, y;
        cin >> u >> v >> x >> y;
        ll tmp = pre[x][y] - pre[x][v - 1] - pre[u - 1][y] + pre[u - 1][v - 1] ;
        cout << tmp << endl;
    }
}

signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}