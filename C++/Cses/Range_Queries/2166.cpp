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
ll tree[maxN * 4], a[maxN], conn[maxN * 4];

//Segment Tree 

void build(ll l, ll r, ll i){
    if(l == r)tree[i] = conn[i] = a[l];
    else {
        ll mid = (l + r) / 2LL;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        tree[i] = max(max(tree[i * 2], tree[i * 2 + 1]), tree[i * 2] );
        
    }
}
void update(ll l, ll r, ll i, ll k, ll u){
    if(l > k || r < k)return;
    else if(l == r && l == k)tree[i] = u;
    else {
        ll mid = (l + r) / 2LL;
        update(l, mid, i * 2, k, u);
        update(mid + 1, r, i * 2 + 1, k, u);
        tree[i] = max(tree[i * 2] + tree[i * 2 + 1], max(tree[i * 2], tree[i * 2 + 1]));
    }
}
ll get(ll l, ll r, ll i, ll a, ll b){
    if(l > b || r < a)return -infi;
    else if(l <= b && l >= a)return tree[i]; 
    else {
        ll mid = (l + r) / 2LL;
        return max(get(l, mid, i * 2 , a, b), get(mid + 1, r, i * 2 + 1, a, b));
    }
}

// end 

void solve(){
    ll n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        conn[i] = conn[i - 1] + a[i];
    }
    for(int i = 1; i <= n * 4; i ++){
        //conn[i] = 0;
        tree[i] = 0;
    }     
    build(1, n, 1);
    while(q --){
        ll t; cin >> t;
        if(t == 1){
            ll k, u;
            cin >> k >> u;
            update(1, n, 1, k, u);
        }else {
            ll a, b;
            cin >> a >> b;
            cout << get(1, n, 1, a, b) << endl;
        }
    }
}

signed main(){
    fast; 
    ll t = 1;
//    cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}