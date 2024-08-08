/*
**********************************
 Author : Akkotsu / huyhuyne        
 Date :   20 /  07 /  2024   
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (ll) 3e5 + 5
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
vector<ll> marks(maxN, 0);
vector<ll> roads[maxN];

void dfs(ll u){
    marks[u] = 1;
    for(auto v : roads[u]){
        if(!marks[v]){
            dfs(v);
        }
    }
}

void solve(){
    ll n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        ll u, v;
        cin >> u >> v;
        roads[u].pb(v);
        roads[v].pb(u);
    }
    vector<pair<ll, ll>> missing;
    ll last = 0;
    for(int i = 1; i <= n; i ++){
        if(!marks[i]){
            dfs(i);
            if(last != 0)missing.pb({last, i});
            last = i;
        }   
    }
    cout << missing.size() << endl;
    for(auto x : missing){
        cout << x.first << ' ' << x.second << endl;
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