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

/* 
 * Caution:
 *   *need to cast into and int before printing
 * source: Benq
*/
struct Mint {
  int v;
  explicit operator int() const { return v; }
  Mint() { v = 0; }
  Mint(long long _v) : v(_v % mod) { v += (v < 0) * mod; }
};
Mint &operator+=(Mint &a, Mint b) {
  if ((a.v += b.v) >= mod) a.v -= mod;
  return a;
}
Mint &operator-=(Mint &a, Mint b) {
  if ((a.v -= b.v) < 0) a.v += mod;
  return a;
}
Mint operator+(Mint a, Mint b) { return a += b; }
Mint operator-(Mint a, Mint b) { return a -= b; }
Mint operator*(Mint a, Mint b) { return Mint((long long)a.v * b.v); }
Mint &operator*=(Mint &a, Mint b) { return a = a * b; }
Mint pow(Mint a, long long p) {
  assert(p >= 0);
  return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
}
Mint inv(Mint a) {
  assert(a.v != 0);
  return pow(a, mod - 2);
}
Mint operator/(Mint a, Mint b) { return a * inv(b); }

vector<Mint> F;
vector<Mint> invF;

Mint  C(ll n, ll k){
    if(k < 0 || k > n)return 0;

    if(!F.size()) F.pb(1);
    
    if(!invF.size()) invF.pb(1);

    for(int i = F.size(); i < n + 1; i ++){
        F.pb(i * F.back());
        invF.pb(invF.back() * inv(Mint(i)));
    }
    return (F[n] * invF[k] * invF[n - k]);
}
void solve(){
    ll n, k;
    cin >> n >> k;
    ll cnt1 = 0, cnt0 = 0;
    for(int i = 1; i <= n; i ++){
        ll x;
        cin >> x;
        cnt1 += x;
    }
    cnt0 = n - cnt1;
    
    Mint ans = 0;
    for(int i = (k + 1) / 2; i <= k; i ++){
        ans += C(cnt1, i) * C(cnt0, k - i); 
    }
    cout << (int)ans;
}

signed main(){
    fast; 
    ll t = 1;
    
    cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}