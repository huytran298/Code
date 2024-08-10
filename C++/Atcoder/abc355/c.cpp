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
    ll n, t;
    cin >> n >> t;
    
    vector<pair<ll, ll>> pos(n * n + 1);
    vector<vector<ll>> line(2, vector<ll>(n + 1, 0));
    ll leftDiag = 0, rightDiag = 0;

    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            ll tmp = n * (i - 1) + j;
            pos[tmp] = {i, j};
        }
    }
    for(int i = 1; i <= t; i ++){
        ll x;
        cin >> x;
        ll u = pos[x].first, v = pos[x].second;
        //cout << u << ' ' << v << endl;
        line[0][u] ++;
        line[1][v] ++;
        if(u == v)leftDiag ++;
        if(u == (n + 1) - v){
            rightDiag ++;
            
        }
        //cout << u << ' ' << (n + 1) - v << endl;
        if(line[0][u] == n || line[1][v] == n || leftDiag == n || rightDiag == n)return void (cout << i);
    }
    cout << -1;
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