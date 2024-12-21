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
    ll tbl[n + 1][n + 1];
    vector<vector<ll>> pre1(n + 1, vector<ll>(n + 1, 0)), a(n + 1, vector<ll>(n + 1, 0)), pre2(n + 1, vector<ll>(n + 1, 0));
    ll h = 1;
    for(int i = 1; i <= n; i ++){
        ll sum = 0;
        for(int j = 1; j <= n; j ++){
            ll x;
            cin >> x;
            sum +=  x * h;    
            a[i][j] = h;      
            pre2[i][j] = pre2[i][j - 1] + x;
            pre1[i][j] = pre1[i - 1][j] + sum;
            h ++;
        }
    }
    while(q -- ){
        ll x1, y1, x2, y2, ans = 0;
        cin >> x1 >> y1 >> x2 >> y2;
        ll delta = a[x1][y1] - 1;
        for(int i = x1; i <= x2; i ++){
            //ll tmp = pre1[x2][y2] - pre1[x1 - 1][y2] - pre1[x2][y1 - 1];
            ans += delta * (pre2[i][y2] - pre2[i][y1 - 1]);
            delta += n - (y2 - y1 + 1);
        }
        cout << pre1[x2][y2] - pre1[x1 - 1][y2] - pre1[x2][y1 - 1] + pre1[x1 - 1][y1 - 1] - ans << ' ';
    }
}

signed main(){
    fast; 
    ll t = 1;
    cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}