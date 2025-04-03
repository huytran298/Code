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


vector<ll> lazy(maxN * 4, 0), tree(maxN * 4);
void update(ll l, ll r, ll i, ll u, ll v, ll h){
    if(l > v || r < u)return;
    else if(l >= u && r <= v){
        lazy[i] = h;
        tree[i] = h;
    }else {
        ll mid = (l + r) / 2LL;
        //tree[i * 2 + 1] = tree[i * 2] = lazy[i];
        if(lazy[i] > 0){
            tree[i * 2 + 1] = tree[i * 2] = lazy[i];
            lazy[i * 2] = lazy[i * 2 + 1] = lazy[i];
            lazy[i] = 0;
        }
        update(l, mid, i * 2, u, v, h);
        update(mid + 1, r, i * 2 + 1, u, v, h);
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
        
    }
}
ll get(ll l , ll r, ll i , ll u , ll v){
    if(l > v || r < u)return infi;
    else if(l >= u && r <= v)return tree[i];
    else {
        ll mid = (l + r) / 2;
        if(lazy[i] > 0){
            tree[i * 2 + 1] = tree[i * 2] = lazy[i];
            lazy[i * 2] = lazy[i * 2 + 1] = lazy[i];
            lazy[i] = 0;
        }
        return min(get(l, mid, i * 2, u, v), get(mid + 1, r, i * 2 + 1, u, v));
    }
}
struct block{
    ll x, y, l, i;
};
bool cmp(block &a , block &b){return a.x < b.x;}
void solve(){
    ll h, w, n;
    cin >> h >> w >> n;
    vector<block> p;
    for(int i = 0; i < n; i ++){
        block tmp;
        cin >> tmp.x >> tmp.y >> tmp.l;
        tmp.i = i + 1;
        p.pb(tmp);
    }
    for(int i = 1; i <= w * 4 + 1; i ++)tree[i] = h;
    sort(rbend(p), cmp);
    ll ans[n + 1];
    for(block x : p){
        ll tmp = get(1, w, 1, x.y, x.y + x.l - 1);
        ans[x.i] = tmp;
        //cout << x.i << ' ' << tmp << endl;
        update(1, w, 1, x.y, x.y + x.l - 1, tmp - 1);  
    }
    for(int i = 1; i <= n; i ++)cout << ans[i] << endl;
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