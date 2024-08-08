// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne        
 Date :   $%D%$ /  $%M%$ /  $%Y%$   
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (ll) 1e5 + 5
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
vector<ll> graphs[maxN];
vector<ll> counts(maxN, 0);
vector<ll> visited(maxN, 0);
ll n, m;
void dfs(ll u, ll q){
    if(marks[u]){
        q --;
        if(q < 0)return;
    }else q = m;
    visited[u] = 1;
    bool go = false;
    if(graphs[u].size() == 1)counts[u] = 1;
    for(auto v : graphs[u]){
        if(!visited[v]) dfs(v, q);
        //go = go | !visited[v];
    }
    visited[u] = 0;
}
void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        cin >> marks[i];
    }
    for(int i = 1; i < n; i ++){
        ll u, v;
        cin >> u >> v;
        if(v == 1)swap(u, v);
        graphs[u].pb(v);
        graphs[v].pb(u);
    }
    dfs(1, m);
    ll cnt = 0;
    for(int i = 2; i <= n; i ++)cnt += counts[i];
    cout << cnt;
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