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
bool cmp(pair<ll, ll> &a, pair<ll, ll> &b){return a.first < b.first;}
void solve(){
    ll n, m;
    cin >> n >> m;
    ll a[n + 1];
    vector<ll> p, pos;
    for(int i = 1; i <= n; i ++)cin >> a[i];
    p.pb(a[1]);
    pos.pb(1);
    for(int i = 2; i <= n; i ++){
        if(p.back() > a[i]){
            p.pb(a[i]);
            pos.pb(i);
        }
    }
    reverse(bend(p));
    reverse(bend(pos));
    for(int i = 1; i <= m; i ++){
        ll x;
        cin >> x;
        ll mid = lower_bound(bend(p), x) - p.begin();
        mid = min(mid, (ll)(p.size() - 1));
        if(p[mid] <= x)cout << pos[mid] << endl;
        else if(mid == 0) cout << -1 << endl;
        else cout << pos[mid - 1] << endl;
        
    }




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