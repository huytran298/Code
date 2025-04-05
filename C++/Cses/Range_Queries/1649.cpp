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
vector<ll> tree(maxN * 4), a(maxN + 1);
void build(ll l, ll r, ll i){
    if(l == r)tree[i] = a[l];
    else {
        ll mid = (l + r) / 2;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }
}
void update(ll l, ll r, ll i, ll pos, ll x){
    if(r < pos || l > pos)return ;
    //else if(u <= l && v >= r)return tree[i];
    else if(l == r)tree[i] = a[l] = x;
    else {
        ll mid = (l + r) / 2;
        //return min(get(l, mid, i * 2, u, v), get(mid + 1, r, i * 2 + 1, u, v));
        update(l, mid, i * 2, pos, x);
        update(mid + 1, r, i * 2 + 1 , pos, x);
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }
}
ll get(ll l, ll r, ll i, ll u, ll v){
    if(r < u || l > v)return infi;
    else if(u <= l && v >= r)return tree[i];
    else {
        ll mid = (l + r) / 2;
        return min(get(l, mid, i * 2, u, v) , get(mid + 1, r, i * 2 + 1, u, v));
    }
}
void solve(){
    ll n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    //return;
    build(1, n, 1);
    for(int i = 1; i <= k; i ++){
        ll t, u, v;
        cin >> t >> u >> v;
        if(t == 2)cout << get(1, n, 1, u, v) << endl;
        else update(1, n, 1, u, v);
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