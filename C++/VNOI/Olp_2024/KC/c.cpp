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
void solve(){
    ll n, k;
    cin >> n >> k;
    vector<ll> lstPrime(1e6, 1LL);
    lstPrime[2] = 1;
    for(ll i = 2; i * i <= 1e6; i ++){
        if(lstPrime[i]){
            for(int j = i * i; j <= 1e6; j += i){
                lstPrime[j] = 0;
            }
        }
    }
    vector<ll> prime;
    for(int i = 2; i < 1e6; i ++){
        if(lstPrime[i])prime.pb(i);
    }
    ll ans = 0;
    for(int i = prime.size() - 1; i >= 2; i --){
        if(prime[i] * prime[i - 1] * prime[i - 2] > n)continue;
        bool check = 0;
        for(ll a = 2; a <= k; a ++){
            for(ll b = 2; b <= k; b ++){
                if(a + b >= k)break;
                if(k % a != 0 || k % b != 0)continue;
                ll sA = pow(prime[i], a - 1), sB = pow(prime[i - 1], b - 1), sC = pow(prime[i - 2], k/(a * b) - 1);
                if(sA * sB * sC <= n){
                    ans = max(ans, sA * sB * sC);
                    check = 1;
                }
            }
        }
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