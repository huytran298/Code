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
    ll h[n + 1];
    for(int i = 1; i <= n; i ++){
        cin >> h[i];
    }
    ll t = 0;
    ll ans = 0;
    ll dmg[3] = {1, 1, 3}; 
    for(int i = 1; i <= n; i ++){
        //t ++;
        while(h[i] > 0){
            if(t % 3 == 0 && h[i] >= 5){
                // h[i] -= 5;
                // t += 3;
                ll tmp = h[i] / 5;
                h[i] = h[i] % 5;
                t += tmp * 3;
            }else {
                t ++;
                h[i] -= dmg[((t % 3 == 0)? 2 : t % 3 - 1)];
            }
        }
    }
    cout << t;
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