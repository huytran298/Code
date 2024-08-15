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
    ll a[n + 1];
    ll cnt = 0;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        cnt += a[i];
    }
    string str;
    cin >> str;
    ll l = 0, r = n - 1, ans = 0;
    while(l <= r){
        if(str[l] == 'L' && str[r] == 'R'){
            ans += cnt;
            cnt -= a[l + 1] + a[r + 1];
            l ++;
            r --;
            continue;
        }
        if(str[r] == 'L'){
            cnt -= a[r + 1];
            r --;    
            continue;
        }
        if(str[l] == 'R'){
            cnt -= a[l + 1];
            l ++;
        }
    }
    cout << ans;
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