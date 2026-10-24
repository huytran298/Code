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

/*
    a_i v a_j (j >= k + i - 1) -> cost = a_i + a_j
    cost = a_i + a_j + a_k > a_i + a_k
*/

ll st[maxN * 4];
vector<ll> a(maxN + 1);
void build (ll i, ll l, ll r){
    if(l == r){
        st[i] = a[l];
    }else {
        ll mid = (l + r) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
        st[i] = min(st[i * 2], st[i * 2 + 1]);
    }
}
ll get(ll i, ll l, ll r, ll u, ll v){
    if (v < l || r < u) {
        
        return __LONG_LONG_MAX__;
    }
    if (u <= l && r <= v) {
        
        return st[i];
    }
    int mid = (l + r) / 2;
    return min(get(i * 2, l, mid, u, v),  get(i * 2 + 1, mid + 1, r, u, v));
}
void solve(){
    ll n, k;
    cin >> n >> k;
    
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    if(k == 1){
        ll cost = __LONG_LONG_MAX__;
        for(int i = 1; i <= n - k + 1; i ++){
            cost = min(cost, a[i]);
        }
        cout << cost << endl;
        return;
    }
    build(1, 1, n);
    ll cost = __LONG_LONG_MAX__;
    for(int i = 1; i <= n - k + 1; i ++){
        cost = min(cost, a[i] + get(1, 1, n, i + k - 1, n));
    }
    cout << cost << endl;

}
signed main(){
    fast; 
    ll t;
    cin >> t;
    while(t --){
        solve();
    }
}