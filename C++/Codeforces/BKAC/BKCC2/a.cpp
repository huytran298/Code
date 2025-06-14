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

void solve(){
    ll n, m, t;
    cin >> n >> m >> t;
    if(t / 2 <= m)return void(cout << "NO");
    vector<ll> a(m + 1), b(t + 1);
    vector<ll> u(n + 2, 0), v(n + 2, 0);
    for(int i = 1; i <= m; i ++){
        cin >> a[i];
        u[a[i]] = 1;
    }
    for(int i = 1; i <= t; i ++){
        cin >> b[i];
        v[b[i]] = 1;
    }
    
    cout << endl;
}
signed main(){
    fast; 
    ll t;
    cin >> t;
    while(t --){
        solve();
    }
}