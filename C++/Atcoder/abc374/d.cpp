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
    ll n, s, t;
    cin >> n >> s >> t;
    long double ans = 0;
    long double x_o = 0, y_o = 0;
    for(int i = 1; i <= n; i ++){
        long double x, y;
        cin >> x >> y;
        ans += sqrt((x - x_o) * (x - x_o) - (y - y_o) * (y - y_o));
        x_o = x;
        y_o = y;
    }
    cout << ans;
}
signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --) {
        ll n;
        cin >> n;
        int b[n];
        for(int i = 0; i < n; i ++)cin >> b[i];
        int *ans;
        sol(ans, b, n);

        cout << endl;
    }
}