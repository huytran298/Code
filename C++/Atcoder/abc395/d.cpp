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
    ll n, q;
    cin >> n >> q;
    vector<ll> nest(n + 1), pigeons(n + 1), rev(n + 1);
    for(int i = 1; i <= n; i ++)nest[i] = pigeons[i] = rev[i] = i;
    while(q --){
        ll t;
        cin >> t;
        if(t == 1){
            ll a, b;
            cin >> a >> b;
            ll tmp = b;
           
            pigeons[a] = rev[b];

        }else if(t == 2){
            ll a, b;
            cin >> a >> b;
            ll posNestA = rev[a], posNestB = rev[b];
            swap(nest[posNestA], nest[posNestB]);
            swap(rev[a], rev[b]);
        }else {
            ll a;
            cin >> a;
            cout << nest[pigeons[a]] << endl;
        }
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