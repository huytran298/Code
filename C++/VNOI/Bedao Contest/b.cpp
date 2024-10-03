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
set<ll> num(ll n){
    set<ll> s;
    for(ll i = 1; i * i <= n; i ++){
        if(n % i == 0){
            s.insert(i);
            if(i * i != n)s.insert(n / i);
        }
    }
    return s;
}
void solve(){
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    set<ll> ans;
    ll s1, s2, s3;
    s1 = lcm(a, c);
    s2 = lcm(a, b);
    s3 = lcm(b, c);
    if(n % s1 == 0){
        set<ll> vl = num(n / s1);
        ans.insert(bend(vl));
    }
    if(n % s2 == 0){
        set<ll> vl = num(n / s2);
        ans.insert(bend(vl));
    }
    if(n % s3 == 0){
        set<ll> vl = num(n / s3);
        ans.insert(bend(vl));
    }
    
    cout << ans.size();
}

signed main(){
    fast; 
    ll t = 1;
   // cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}