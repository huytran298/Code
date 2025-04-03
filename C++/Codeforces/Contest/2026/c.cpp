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
int c(int n){
    if(n % 2 != 0)return n / 2 + 1;
    return n / 2;
}
void solve(){
    ll n;
    cin >> n;
    string s;
    cin >> s;
    ll ans = (n * (n + 1)) / 2 , cnt = 0;
    for(int i = c(n); i < n; i ++){
        if(s[i] == '1'){
            ans -= (i + 1);
            cnt ++;
        }
    }
    if(n % 2 != 0)cnt = c(n) - cnt - 1;
    else cnt = c(n) - cnt;
   // cout << cnt;

    for(int i = c(n) - 1; i > 0; i --){
        if(cnt == 0)break;
        if(s[i] == '1'){
            ans -= (i + 1);
            cnt -= 2;
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