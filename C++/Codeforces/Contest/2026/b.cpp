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
    ll n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x : a){
        cin >> x;
    }
    if(n == 1)return void(cout << 1);
    if(n % 2 == 0){
        ll ans = 1;
        for(int i = 1; i < n; i += 2){
            ans = max(ans, abs(a[i] - a[i - 1]));
        }
        reverse(bend(a));
        ll ans1 = 1;
        for(int i = 1; i < n; i += 2){
            ans1 = max(ans1, abs(a[i] - a[i - 1]));
        }
        cout << min(ans, ans1);
    }else {
        ll ans = infi;
        for(int p = 0; p < n; p ++){
            ll tmp = 1;
            ll ac = 1;
            for(int i = 1; i < n; i += 1){
                if((p == 0 && i == 1) || p == i){
                    i ++;
                    continue;
                }
                ac = 0;
                tmp = max(a[i] - a[i - 1], tmp);
            }
            if(ac)continue;
            ans = min(ans, tmp);
        }
        cout << ans;
    }
    
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