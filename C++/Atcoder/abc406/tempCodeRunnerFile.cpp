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

signed main(){
    fast; 
    ll h, w, n;
    cin >> h >> w >> n;
    vector<set<ll>> X(h + 1);
    vector<set<ll>> Y(w + 1);
    for(int i = 1; i <= n; i ++){
        ll u, v;
        cin >> u >> v;
        X[u].insert(v);
        Y[v].insert(u);
    }
    ll q;
    cin >> q;
    while(q --){
        ll t;
        cin >> t;
        if(t == 1){
            ll x;
            cin >> x;
            cout << X[x].size() << endl;
            for(auto u : X[x]){
                Y[u].erase(x);
            }
            X[x].clear();
        }else {
            ll y;
            cin >> y;
            cout << Y[y].size() << endl;
            for(auto v : Y[y]){
                X[v].erase(y);
            }
            Y[y].clear();
            
        }
        //cout << endl;
    }
    
}