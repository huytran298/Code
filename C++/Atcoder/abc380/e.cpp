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

vector<ll> parent(maxN, -1), sz(maxN, 1), color(maxN, 0), num(maxN, 1), l(maxN, infi), r(maxN, 0);
int find_set(ll v) {
    return (v == parent[v])? v : parent[v] = find_set(parent[v]);
}
void unite(ll a, ll find){
    find = find_set(find);
    if(color[a] == color[find] && a != find){
        parent[find] = a;
        l[a] = min(l[a], l[find]);
        r[a] = max(r[a], r[find]);
        sz[a] += sz[find];
    }
}
void solve(){
    ll n;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        parent[i] = i;
        color[i] = i;
        l[i] = r[i] = i;
    }
    ll q;
    cin >> q;
    while(q --){
        ll t;
        cin >> t;
        if(t == 1){
            ll x, c;
            cin >> x >> c;
            ll tmp = find_set(x);
            num[color[tmp]] -= sz[tmp]; 
            color[tmp] = c;
            num[c] += sz[tmp];
            unite(tmp, max(l[tmp] - 1, 1LL));
            unite(tmp, min(r[tmp] + 1, n));
        }
        else {
            ll c;
            cin >> c;
            cout << num[c] << endl;
        }
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