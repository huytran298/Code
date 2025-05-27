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

signed main(){
    fast; 

    /*
        l + l = c
        c + c = c
        l + c = l
    */
    ll t; 
    cin >> t;
    vector<ll> v;
    while(t --){
        ll n;
        cin >> n;
        vector<ll> a(n, 0);
        for(int i = 0; i < n; i ++)cin >> a[i];
        sort(bend(a));
        ll ans = infi;
        for(int i = 0; i < n; i ++){
            for(int j = n - 1; j >= i; j --){
                if((a[i] + a[j]) % 2 == 0){
                    ans = min(ans, i + (n - (j + 1)));
                }
            }
        }
        v.pb(ans);
    }
    for(auto x : v)cout << x << '\n';
}