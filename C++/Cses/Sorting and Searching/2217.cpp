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
void prcs(vector<ll> &pos, vector<ll> &a, ll u, ll v, ll n, ll &ans){
    ll tmp = 0;
    for(int i = max(a[u] - 1, 1LL); i < min(a[u] + 1, n); i ++){
        if(pos[i + 1] < pos[i])ans --;
    }
    //cout << ans << ' ';
    for(int i = max(a[v] - 1, 1LL); i < min(a[v] + 1, n); i ++){
        if(i == a[u] || i + 1 == a[u])continue;
        if(pos[i + 1] < pos[i])ans --;
    }
    swap(a[u], a[v]);
    swap(pos[a[u]], pos[a[v]]);

    for(int i = max(a[u] - 1, 1LL); i < min(a[u] + 1, n); i ++){
        if(pos[i + 1] < pos[i])ans ++;
    }
    for(int i = max(a[v] - 1, 1LL); i < min(a[v] + 1, n); i ++){
        if(i == a[u] || i + 1 == a[u])continue;
        if(pos[i + 1] < pos[i])ans ++;
    }
}
void solve(){
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), pos(n + 1, 0);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        pos[a[i]] = i;
    }
    ll ans = 1;
    for(int i = 1; i < n; i ++){
        if(pos[i + 1] < pos[i]){
            //chk[i] = 1;
            ans ++;
        }
    }
   
    for(int i = 1; i <= m; i ++){
        ll u, v;
        cin >> u >> v;
        ll tmp = 0;
        prcs(pos, a, u, v, n, ans);
        cout << ans << '\n';
    }
    //for(int i = 1; i <= n; i ++)cout << pos[i] << ' ';
    //cout << ans << endl;
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