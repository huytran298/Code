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

ll tree[maxN * 4];
vector<ll> a(maxN + 1);
void build(ll l, ll r, ll i){
    if(l == r)tree[i] = a[l];
    else {
        ll mid = (l + r) / 2LL;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
}
ll query(ll l, ll r, ll i, ll u, ll v){
    if(r < u || l > v)return -infi;
    else if(l >= u && r <= v)return tree[i];
    else {
        ll mid = (l + r) / 2LL;
        return max(query(l, mid, i * 2, u, v), query(mid + 1, r, i * 2 + 1, u, v));
    }
}
bool cmp(pair<ll, ll> a, pair<ll, ll> b){
    if(a.first == b.first)return a.second < b.second;
    return a.first < b.first;
}
void solve(){
    ll n, c;
    cin >> n >> c;
    vector<pair<ll, ll>> node(n + 1, pair<ll, ll>{0LL, 0LL});
    for(int i = 1; i <= n; i ++){
        cin >> node[i].first;
    }      
    for(int i = 1; i <= n; i ++){
        cin >> node[i].second;
    }      
    sort(bend(node), cmp);
   
    for(int i = 1; i < n; i ++){
        a[i] = node[i + 1].first - node[i].first;
        if(node[i].second >= c)return void (cout << 0);
    }
    build(1, n - 1, 1);
    ll sum = node[1].second + node[2].second;
    ll ans = infi;
    ll l = 1;
    ll r = 2;
    
    while(r <= n){
        while(sum >= c){
            ans = min(ans, query(1, n - 1, 1, l, r - 1));
            sum -= node[l].second;
            l ++;
        }
        r ++;
        if(r > n)break;
        sum += node[r].second;
    }
    cout << ans;
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