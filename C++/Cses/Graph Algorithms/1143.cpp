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
ll st[maxN * 4], a[maxN + 5];
void build(ll l, ll r, ll i){
    if(l == r)st[i] = a[l];
    else {
        ll mid = (l + r) >> 1LL;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        st[i] = max(st[i * 2], st[i * 2 + 1]);
    }
}
void update(ll l, ll r, ll i, ll k, ll x){
    if(l > k || r < k)return;
    else if(l == r)st[i] = a[k] = x;
    else {
        ll mid = (l + r) >> 1LL;
        update(l, mid, i * 2, k, x);
        update(mid + 1, r, i * 2 + 1, k, x);
        st[i] = max(st[i * 2], st[i * 2 + 1]);
    }
}
ll query(ll l, ll r, ll i, ll x){
    if(st[i] < x)return 0;
    else if(l == r)return l;
    else {
        ll mid = (l + r) >> 1LL;
        if(st[i * 2] >= x)return query(l, mid, i * 2, x);
        return query(mid + 1, r, i * 2 + 1, x);
        
    }
}

void solve(){
    ll n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i ++)cin >> a[i];
    build(1, n, 1);
    
    while(q --){
        ll x; cin >> x;
        ll pos = query(1, n, 1, x);
        if(pos != 0){
            cout << pos << ' ';
            update(1, n, 1, pos, a[pos] - x);
        }else cout << pos << ' ';
        
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