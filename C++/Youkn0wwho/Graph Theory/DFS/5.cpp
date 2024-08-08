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
struct Edge{
    ll u, v;
    ll w;
};
struct Tr{
    ll v, w;
};
bool Is_cycle(ll S, ll k, vector<vector<Tr>> tr, vector<ll> &ck){
    ck[k] = 1;
    for(auto x : tr[k]){
        if(x.v == S)return true;
        if(!ck[x.v]){
           bool value = Is_cycle(S, x.v, tr, ck);
           if(value)return true;
        }
    }
    return false;
}
void solve(){
    ll n;
    cin >> n;
    vector<vector<Tr>> tr(n + 1), rtr(n + 1);
    for(int i = 1; i <= n; i ++){
        ll u, v, w;
        cin >> u >> v >> w;
        Tr t;
        t.v = v;
        t.w = w;
        tr[u].pb(t);
        t.v = u;
        rtr[v].pb(t);
    }
    
    vector<ll> ck(n + 1, 0);
    
    if(Is_cycle(1, 1, tr, ck))return void (cout << "YES");
    ll cost = 0;
    for(int i = 1; i <= n; i ++){
        if(tr[i].size() == 0){
            ll minC = infi, tmpV = -1;
            for(auto x : rtr[i]){
                if(x.w < minC){
                    minC = x.w;
                    tmpV = x.v;
                }
            }
            for(int j = 0; j < tr[tmpV].size(); j ++){
                if(tr[tmpV][j].v == i){
                    tr[tmpV].erase(tr[tmpV].begin() + j);
                    break;
                }
            }
            Tr t;
            t.v = tmpV;
            t.w = minC;
            tr[i].pb(t);
            cost += minC;
        }
    }
    cout << cost;
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