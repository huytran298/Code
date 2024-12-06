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
    ll q;
    cin >> q;
    ll cnt = 0;
    deque<pair<ll, ll>> pq;
    ll time = 0, last = 0;
    for(int i = 1; i <= q; i ++){
        ll t;
        cin >> t;
        if(t == 1)cnt ++;
        else if(t == 2){
            ll h; cin >> h;
            pq.pb({time, cnt}); 
            time += h;
            last = h;
            cnt = 0;
        }
        else {
            ll h; cin >> h;
            ll ans = 0;
            while(!pq.empty()){
                if(time - pq.front().first >= h){
                    ans += pq.front().second;
                    pq.pop_front();
                }
                else break;
            }
            cout << ans << endl;
        }
    }
}

signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --) {
        solve();
        //cout << endl;
    }
}