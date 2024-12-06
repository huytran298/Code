#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (long long) 1e5 + 5
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
vector<ll> pre(maxN + 1, 0);
ll a[maxN + 1];
ll tree[maxN * 4];
void build(ll l, ll r, ll i){
    if(l == r){
        tree[i] = a[i];
    }else {
        ll mid = (l + r) / 2;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        ll tmp = pre[mid] - pre[l - 1];
        tree[i] = max(tree[i * 2] + (tree[i * 2 + 1] - tmp * tree[i * 2]), tree[i * 2]);
    }
}
void solve(){
    ll n, q;
    cin >> n >> q;
    
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    

}
signed main(){
    fast; 
    long long k;
    cin >> k;
    k ++;
    bool checkFirstBit = 0;
    for(long long i = 63; i >= 0; i --){
        if(k & (1LL << i)){
            if(checkFirstBit == 0){
                checkFirstBit = 1;
                continue;
            }
            cout << 8;
        }else if(checkFirstBit == 1){
            cout << 5;
        }
    }
}
