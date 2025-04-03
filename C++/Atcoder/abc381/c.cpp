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
    string s;
    cin >> s;
    ll cnt0 = 0, cnt1 = 0, cnt2 = 0;
    ll ans = 1;
    for(char x : s){
        if(x == '1'){
            if(cnt0 == 1){
                ll tmp = min(cnt1, cnt2);
                ans = max(2 * tmp + 1, ans);
                
            }
            cnt0 = cnt2 = 0;
            cnt1 ++;
        }else if(x == '/'){
            cnt0 ++;
            //ans = max(1LL, ans);
            if(cnt0 > 1|| cnt2 > 0){
                cnt1 = cnt2 = cnt0 = 0;
            }
        }
        else {
            cnt2 ++;
            if(cnt0 == 1){
                ll tmp = min(cnt1, cnt2);
                ans = max(2 * tmp + 1, ans);        
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