#include<bits/stdc++.h>
#include<iostream>
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
bool ischar(char x){
    return (x <= 'z' && x >= 'a');
} 

signed main(){
    fast; 
    ll h, w;
    cin >> h >> w;
    vector<vector<char>> table(h + 1, vector<char>(w + 1, '#'));
    vector<vector<ll>> ans(h + 1, vector<ll> (w + 1, 0));
    map<char, set<pair<ll, ll>>> teleport;
    for(int i = 1; i <= h; i ++){
        for(int j = 1; j <= w; j ++){
            cin >> table[i][j];
            if(ischar(table[i][j]))teleport[table[i][j]].insert({i, j});
        }
    } 
    queue<pair<ll, ll>> q;
    q.push({1, 1});
    ans[1][1] = 1;
    while(!q.empty()) {
        auto [u, v] = q.front();
        q.pop();
        //ans[u.first][u.second] = 1;
        if(ischar((table[u][v])) && !teleport[table[u][v]].empty()){
            for(auto [x, y] : teleport[table[u][v]]){
                if(x == u && v == y)continue;
                if(!ans[x][y]){
                    ans[x][y] = ans[u][v] + 1 ;
                    q.push({x, y});
                }

            }
            teleport[table[u][v]].clear();
        }
        vector<pair<ll, ll>> ls = {{0, 1}, {1, 0}, {-1 , 0}, {0, -1}};
        for(auto [x, y] : ls){
            if(u + x <= 0 || u + x > h || v + y <= 0 || v + y > w || table[u + x][v + y] == '#') continue;
            if(!ans[u + x][v + y] || ans[u + x][v + y] > ans[u][v] + 1){
                q.push({u + x, v + y});
                ans[u + x][v + y] = ans[u][v] + 1;
            }
        }
    }  
    // for(int i = 1; i <= h; i ++){
    //     for(int j = 1; j <= w; j ++)cout << ans[i][j] << ' ';
    //     cout << endl;
    // }
    // return 0;
    if(ans[h][w] == 0)cout << -1;
    else cout << ans[h][w] - 1;
}