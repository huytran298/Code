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
#define mod 998244353
int nxt(){ int n; cin >> n; return n;}
/*
 _  _             _____              
| || |_  _ _  _  |_   _| _ __ _ _ _  
| __ | || | || |   | || '_/ _` | ' \ 
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/                      
*/
void solve(){
    ll n, q;
    cin >> n >> q;
    vector<ll> sq(n + 1, 0);
    ll cnt = 0;

    for(int i = 1; i <= q; i ++){
        ll x;
        cin >> x;
        if(!sq[x]){
            ll tmp = 0;
            if(x == 1 && !sq[x + 1])cnt ++;
            else if(x == n && !sq[x - 1])cnt ++;
            else if(!sq[x + 1] && !sq[x - 1])cnt ++;

            if((x > 1 && x < n) && sq[x + 1] && sq[x - 1])cnt --;
            //cout << sq[x - 1] << ' ';
        }else {
            if(x == 1 && !sq[x + 1])cnt --;
            else if(x == n && !sq[x - 1])cnt --;
            else if(!sq[x + 1] && !sq[x - 1])cnt --;
            
            if((x > 1 && x < n) &&sq[x + 1] && sq[x - 1])cnt ++;
        }
        sq[x] = !sq[x];
        cout << cnt << endl;
    }


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