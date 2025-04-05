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
void solve(){
    ll h, w, x, y;
    cin >> h >> w >> x >> y;
    vector<vector<char>> table(h + 1, vector<char>(w + 1));
    for(int i = 1; i <= h; i ++){
        for(int j = 1; j <= w; j ++){
            cin >> table[i][j];
        }
    }
    string t;
    cin >> t;
    vector<pair<ll, ll>> move(300);
    move['U'] = {-1, 0};
    move['L'] = {0, -1};
    move['D'] = {1, 0};
    move['R'] = {0, 1};
    vector vis(h + 1, vector(w + 1, 0));
    vis[x][y] = 1;
    ll cnt = 0;
    
    for(auto q : t){
        auto [u, v] = move[q];
        if(table[x + u][y + v] != '#'){
            x += u;
            y += v;
        }
        if(!vis[x][y] && table[x][y] == '@')cnt ++;
        vis[x][y] = 1;
    }
    cout << x << ' ' << y << ' ' << cnt;
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