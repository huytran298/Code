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
vector<ll> graph[maxN], ans, visited(maxN, 0);
ll has = 0;
void dfs(ll u, ll v){
    if(has)return;
    if(abs(visited[u] - visited[v]) >= 2 && visited[v] != 0){
        ans.pb(u);
        has = u;
        return;
    }
    visited[v] = visited[u] + 1;
    
    for(auto x : graph[v]){
        if(visited[x] == 0 || abs(visited[x] - visited[v]) >= 2){
            dfs(v, x);
            if(has)return;
        }
    }
}
void solve(){
    ll n;
    cin >> n;
    ll m;
    cin >> m;
    for(int i = 1; i <= n; i ++){
        ll u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    for(int i = 1; i <= n; i ++){
        if(vis)
    }
    vector<ll> pt;

    do{
        pt.pb(ans.back());
        ans.pop_back();
    }while(ans.back() != has);
    cout << pt.size() << endl;
    while(!pt.empty()){
        cout << pt.back() << ' ';
        pt.pop_back(); 
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