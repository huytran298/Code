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
ll color_i(int color, int index){
    return (color >> index) & 1;
}
signed main(){
    fast; 
    
    ll n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> edges;
    for(int i = 1; i <= m; i ++){
        ll u, v;
        cin >> u >> v;
        u--;
        v--;

        if(u == v)continue;
        edges.pb({u, v});
    }
    ll ans = m;
    for(int color = 0; color < (1 << n); color ++){
        ll cnt = 0;
        for(auto [u, v]: edges){
            cnt += (color_i(color, u) == color_i(color, v));
        }
        ans = min(ans, cnt);
    }
    cout << ans;
}