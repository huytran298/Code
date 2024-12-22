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
bool ck(ll x, ll y, ll h, ll w, vector<vector<ll>> vis){
    return x > 0 && y > 0 && x <= h && y <= w && !vis[x][y];
}
void solve(){
    ll h, w, x;
    cin >> h >> w >> x;
    ll p, q;
    cin >> p >> q;
    ll tbl[h + 1][w + 1];
    for(int i = 1; i <= h; i ++){
        for(int j = 1; j <= w; j ++)cin >> tbl[i][j];
    }
    queue<pair<ll, ll>> pt;
    pt.push({p, q});
    ll sum = tbl[p][q];
    vector<vector<ll>> vis(h + 5, vector<ll>(w + 5, 0));
    vis[p][q] = 1;
    while(!pt.empty()){
        auto [u, v] = pt.front();
        pt.pop();
        ll ab[] = {-1, 1};
        for(int i = 0; i < 2; i ++){
            if(ck(u + ab[i], v, h, w, vis) && tbl[u + ab[i]][v] < (double)sum/(double)x){
                pt.push({u + ab[i], v});
                sum += tbl[u + ab[i]][v];
                vis[u + ab[i]][v] = 1;
            }
            if(ck(u, v + ab[i], h, w, vis) && tbl[u][v + ab[i]] < (double)sum/(double)x){
                pt.push({u, v + ab[i]});
                sum += tbl[u][v + ab[i]];
                vis[u][v + ab[i]] = 1;
            }
        }
        for(int i = 0; i < 2; i ++){
            if(ck(u + ab[i], v, h, w, vis) && tbl[u + ab[i]][v] < (double)sum/(double)x){
                pt.push({u + ab[i], v});
                sum += tbl[u + ab[i]][v];
                vis[u + ab[i]][v] = 1;
            }
            if(ck(u, v + ab[i], h, w, vis) && tbl[u][v + ab[i]] < (double)sum/(double)x){
                pt.push({u, v + ab[i]});
                sum += tbl[u][v + ab[i]];
                vis[u][v + ab[i]] = 1;
            }
        }

    }
    cout << sum;

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