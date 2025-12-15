#include<bits/stdc++.h>

using namespace std; 

#define ll long long
#define maxN (long long) 1e6 + 5
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

ll n = 3 * 1e5;
ll m = 3 * 1e5;
vector<vector<ll>> edges(n + 1);
vector<vector<ll>> edges_rev(n + 1);
vector<ll> checked(n + 1, 0);
void dfs(ll u){
    checked[u] = 1;
    for(auto x : edges_rev[u]){
        if(checked[x])continue;
        else dfs(x);
    }
}
signed main(){
    fast; 
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        ll u, v;
        cin >> u >> v;
        edges[u].pb(v);
        edges_rev[v].pb(u);
    }
    ll q;
    cin >> q;
    while(q --){
        ll t, u;
        cin >> t >> u;
        if(t == 1){
            if(!checked[u])dfs(u);
        }else {
            cout << ((checked[u])? "Yes" : "No") << endl;
        }
    }
    //for(int i = 1; i <= n; i ++)cout << checked[i] << ' ';

}