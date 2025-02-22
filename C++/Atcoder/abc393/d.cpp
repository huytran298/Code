// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define int long long
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
    string s;
    cin >> s;
    vector<ll> num;
    ll state = -1;
    for(int i = 0; i < n; i ++){
        if(s[i] == '1'){
            if(state == -1){
                state = i;
                num.pb(0);
            }
            else {
                num.pb(i - state - 1);
                state = i;
            }
        }
    }
    
    ll l = 0, r = 0;
    ll tmp = 0;
    for(int i = 1; i < num.size(); i ++){
        tmp += num[i];
        r += tmp;
    }
    
    ll ans = infi;
    for(ll i = 0; i < num.size(); i ++){
        r -= num[i] * (num.size() - i);
        l += num[i] * (i);
        ans = min(ans, l + r);
        //cout << l << ' ' << r << endl;
        //if(i == 2) return; 
    }
    if(ans == infi)ans = 0;
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