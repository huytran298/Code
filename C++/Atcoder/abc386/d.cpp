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
    ll n, m;
    cin >> n >> m;
    map<pair<ll, ll>, ll> q;
    vector<pair<ll, ll>> a;
    map<ll, pair<ll, ll>> r, c;
    bool check = false;
    for(int i = 1; i <= m; i ++){
        ll x, y, color;
        cin >> x >> y >> color;
        q[{x, y}] = color;
        a.pb({x, y});
    }
    for(int i = 1; i <= m; i ++){
        if(check) continue;
        auto [x, y] = a[i - 1];
        ll color = q[{x, y}];
        if(r[x].first == 0)r[x] = {y, color};
        else {
            if(r[x].first > y)r[x] = {y, color};
            else if(r[x].second != color) check = 1;
        }
        if(check) continue;
        if(c[y].first == 0)c[y] = {x, color};
        else {
            if(c[y].first > y)c[y] = {x, color};
            else if(c[y].second != color) check = 1;
        }
    }
    if(check)cout << "No";
    else cout << "Yes";
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