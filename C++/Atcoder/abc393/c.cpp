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
ll state = 0;
vector comes (maxN, 0LL);
vector<vector<ll>> node(maxN + 1);
ll cnt = 0;
void dfs(ll u){
    comes[u] = state;
    for(auto v : node[u]){
        if(comes[v] == 0){
            dfs(v);
        }else if(comes[v] == state){
            cnt ++;
            return ;
        }
    }    
}
void solve(){
    ll n, m;
    cin >> n >> m;
    set<pair<ll, ll>> bruh;
    for(int i = 1; i <= m; i ++){
        ll u, v;
        cin >> u >> v;
        if(u == v)cnt ++;
        else {
            bruh.insert({min(u, v), max(u, v)});
        }
    }
    cout << m - bruh.size();
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