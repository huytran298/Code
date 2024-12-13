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
bool check(ll x, ll y, ll h, ll w){
    return (x > 0) && (y > 0) && (x <= h) && (y <= w);
}
void solve(){
    ll h, w, d;
    cin >> h >> w >> d;
    char tbl[h + 1][w + 1];
    queue<pair<ll, ll>> q;
    vector<vector<ll>> vis(h + 1, vector<ll>(w + 1, 0)), distance(h + 1, vector<ll>(w + 1, 0));
    for(int i = 1; i <= h; i ++){
        for(int j = 1; j <= w; j ++){
            cin >> tbl[i][j];
            if(tbl[i][j] == 'H'){
                q.push({i, j});
                vis[i][j] = 1;
                distance[i][j] = d;
            }else if(tbl[i][j] == '#')vis[i][j] = 1;
            
        }
    }
    ll cnt = q.size();
    while(!q.empty()){
        auto[u, v] = q.front();
        q.pop();
        if(distance[u][v] == 0)continue;
        ll move[] = {-1, 1};
        for(int i = 0; i < 2; i ++){
            if(check(u + move[i], v, h, w) && !vis[u + move[i]][v]){
                q.push({u + move[i], v});
                distance[u + move[i]][v] = distance[u][v] - 1;
                vis[u + move[i]][v] = 1;
                cnt ++;
            }
        }
        for(int i = 0; i < 2; i ++){
            if(check(u, v + move[i], h, w) && !vis[u][v + move[i]]){
                q.push({u, v + move[i]});
                distance[u][v + move[i]] = distance[u][v] - 1;
                vis[u][v + move[i]] = 1;
                cnt ++;
            }
        }
    }
    cout << cnt;
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