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
const long long INF = 2000000000000000000LL;
struct Edge{
    int v;
    long long w;
};
void dijkstra(ll n, ll S, vector<vector<Edge>> E, vector<ll> &D, vector<ll> &trace) {
    D.resize(n + 1, INF);
    trace.resize(n + 1, -1);

    vector<bool> P(n + 1, 0);
    D[S] = 0;

    for (int i = 1; i <= n; i++) {
        int uBest; // tìm đỉnh u chưa dùng, có khoảng cách nhỏ nhất
        long long Max = INF;
        for (int u = 1; u <= n; u++) {
            if(D[u] < Max && P[u] == false) {
                uBest = u;
                Max = D[u];
            }
        }

        // cải tiến các đường đi qua u
        int u = uBest;
        P[u] = true;
        for(auto x : E[u]) {
            int v = x.v;
            long long w = x.w;
            if(D[v] > D[u] + w) {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
}
vector<int> trace_path(vector<ll> &trace, int S, int u) {
    if (u != S && trace[u] == -1) return vector<int>(0); // không có đường đi

    vector<int> path;
    while (u != -1) { // truy vết ngược từ u về S
        path.push_back(u);
        u = trace[u];
    }
    reverse(path.begin(), path.end()); // cần reverse vì đường đi lúc này là từ u về S

    return path;
}
void solve(){
    ll n;
    cin >> n;
    vector<vector<Edge>> E(n + 1);
    vector<ll> D, trace;
    for(int i = 1; i <= n; i ++){
        ll u, v , w;
        cin >> u >> v >> w;
        Edge c;
        c.v = v;
        c.w = w;
        E[u].pb(c);
    }
    //dijkstra(n, 1, E, D, trace);
    vector<vector<ll>> dis(n + 1);
    for(int i = 1; i <= n; i ++){
        dijkstra(n, i, E, D, trace);
        for(auto x : D){
            dis[i].pb(x);
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