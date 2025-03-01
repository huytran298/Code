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
    ll r, c, n, p;
    cin >> r >> c >> n >> p;
    deque<pair<ll, ll>> lst;
    ll tbl[r + 1][c + 1];
    for(int i = 1; i <= r; i ++){
        for(int j = 1; j <= c; j ++){
            ll x;
            cin >> x;
            tbl[i][j] = x;
            if(x != 0 && x <= p)lst.pb({i, j});
        }
    }
    set<ll> meet;
    for(int i = 0; i < p; i ++){
        auto [u, v] = lst[i];
        ll arr[] = {-1, 1};
        for(int j = 0; j < 2; j ++){
            if(u + arr[j] <= 0 && u + arr[j] > r)continue;
            if(tbl[u + arr[j]][v] <= i || tbl[u + arr[j]][v] > n - i)continue;
            meet.insert(tbl[u + arr[j]][v] + i);
        }
        for(int j = 0; j < 2; j ++){
            if(v + arr[j] <= 0 && v + arr[j] > c)continue;
            if(tbl[u][v + arr[j]] <= i || tbl[u][v + arr[j]] > n - i)continue;
            meet.insert(tbl[u][v + arr[j]] + i);
        }
    }
    for(auto x : meet)cout << x << ' ';
    cout << meet.size() << '/' << n - 1;
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