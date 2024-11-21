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

vector<ll> tree(maxN * 4, 0);
void update(ll l, ll r, ll i, ll u, ll v){
    if(l > v || r < u)return ;
    else if(l >= u && r <= v)tree[i] ++;
    else {
        ll mid = (l + r) / 2LL;
        tree[i * 2] += tree[i];
        tree[i * 2 + 1] += tree[i];
        tree[i] = 0;
        update(l, mid, i * 2, u, v);
        update(mid + 1, r, i * 2 + 1, u, v);
    }
}
ll get(ll l, ll r, ll i, ll k){
    if(l > k || r < k)return infi;
    else {
        ll mid = (l + r) / 2LL;
        tree[i * 2] += tree[i];
        tree[i * 2 + 1] += tree[i];
        tree[i] = 0;
        return min(get(l, mid, i * 2, k), get(mid + 1, r, i * 2, k));
    }
}

void solve(){
    
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