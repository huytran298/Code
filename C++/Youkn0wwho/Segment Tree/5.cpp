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
ll stMin[maxN], stMax[maxN], arr[maxN];
void build(ll l, ll r, ll i){
    if(l == r){
        stMax[i] = stMin[i] = arr[l];
        //counts[i] = 1;
    }
    else {
        ll mid = (l + r) >> 1LL;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        stMin[i] = min(stMin[i * 2], stMin[i * 2 + 1]);
        stMax[i] = max(stMax[i * 2], stMax[i * 2 + 1]);
        //counts[i] = counts[i * 2] + counts[i * 2 + 1];  
    }
}
void change(ll l, ll r, ll i, ll k, ll x){
    if(l > k || r < k)return;
    else if(l == r)stMax[i] = stMin[i] = x;
    else {
        ll mid = (l + r) >> 1LL;
        change(l, mid, i * 2, k, x);
        change(mid + 1, r, i * 2 + 1, k, x);
        stMin[i] = min(stMin[i * 2], stMin[i * 2 + 1]);
        stMax[i] = max(stMax[i * 2], stMax[i * 2 + 1]);
    }
}
ll get(ll l, ll r, ll i, ll a, ll b){
    if(stMin[i] > b || stMax[i] < a)return 0;
    else if(stMin[i] >= a && stMax[i] <= b)return r - l + 1;
    else {
        ll mid = (l + r) >> 1LL, u, v;
        u = v = 0;
        u = get(l, mid, i * 2, a, b);
        v = get(mid + 1, r, i * 2 + 1, a, b);
        return u + v;
    }
}

signed main(){
    fast; 
    ll n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i ++)cin >> arr[i];
    build(1, n, 1);
    while(q --){
        char t;
        cin >> t;
        if(t == '!'){
            ll k, x; cin >> k >> x;
            change(1, n, 1, k, x);
        }else {
            ll a, b;
            cin >> a >> b;
            cout << get(1, n, 1, a, b) << '\n';
        }
    }
}