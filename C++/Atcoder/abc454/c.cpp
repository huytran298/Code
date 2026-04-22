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
vector<ll> tree[maxN], visitors(maxN, 0), costs(maxN, 0);

void dfs(ll u){
    
    for(auto v : tree[u]){
        if(visitors[v])continue;
        visitors[v] = 1;
        dfs(v);

    }

}
signed main(){
    fast; 
    ll n, m;
    cin >> n >> m;

    for(int i = 1; i <= m; i ++){
        ll a, b;
        cin >> a >> b;
        tree[a].pb(b);
    }
    visitors[1] = 1;
    dfs(1);
    ll ans = 0;
    
    for(int i = 1; i <= n; i ++)ans += visitors[i];
    cout << ans;

}