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
#define mod 998244353
int nxt(){ int n; cin >> n; return n;}
/*
 _  _             _____              
| || |_  _ _  _  |_   _| _ __ _ _ _  
| __ | || | || |   | || '_/ _` | ' \ 
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/                      
*/
vector<vector<ll>> graph;
vector<ll> visited;
set<ll> removeEdge;
map<pair<ll, ll>, ll> indexEdge;
void dfs(ll u, ll v){
    if(u != -1)visited[v] = visited[u];
    for(auto x : graph[v]){
        if(u != x && !visited[x]){
            dfs(v, x);
        }else if(u != x && visited[x]){
            removeEdge.insert(indexEdge[{min(x, v), max(x, v)}]);
        }
    }
}

void solve(){
    
    ll n, m;
    set<pair<ll, ll>> distinct;
    
    vector<pair<ll, ll>> addEdge;
    
    cin >> n >> m;
    visited = vector<ll>(n + 10);
    graph = vector<vector<ll>> (n + 10);

    for(ll i = 1; i <= m; i ++){
        ll u, v;
        cin >> u >> v;
        if(u == v){
            removeEdge.insert(i);
            continue;
        }

        ll sizeofPath = distinct.size();
        distinct.insert({min(u, v), max(u, v)});

        if(sizeofPath == distinct.size()){
            removeEdge.insert(i);
        }
        else {
            indexEdge[{min(u, v), max(u, v)}] = i;
            graph[u].pb(v);
            graph[v].pb(u);
        }
    }
    visited[1] = 1;
    dfs(-1, 1);
    for(ll i = 2; i <= n; i ++){
        if(!visited[i]){
            visited[i] = visited[i - 1];
            dfs(-1, i);
            addEdge.pb({visited[i - 1], i});
        }
    }
    cout << removeEdge.size() << endl;
    for(auto x : removeEdge) {
        cout << x << endl;
    }
    cout << addEdge.size() << endl;
    for(auto x : addEdge){
        cout << x.first << ' ' << x.second << endl;
    }
    
}

signed main(){
    fast; 
    ll t = 1;
    cin >> t;
    while(t --){
        solve();
        visited.clear();
        graph.clear();
        removeEdge.clear();
    }
}