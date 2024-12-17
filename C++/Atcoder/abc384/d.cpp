// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (ll) 4e5 + 5
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
    ll n, t;
    cin >> n >> t;
    ll sum = 0;
    vector<ll> a(2 * n + 1);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        sum += a[i];
        a[n + i] = a[i];
    }
    
    //build(1, n, 1);
    n *= 2;
    ll delta = (t % sum);
    bool check = 0;
    ll l = 1, r = 1;
    sum = 0;
    while(l != r || r <= n){
        if(delta == sum){
            check = true;
            break;
        }else if(delta > sum){
            if(r > n)break;
            sum += a[r];
            r ++;
        }else {
            sum -= a[l];
            l ++;
        }
        //cout << sum << endl;
    }
    if(check)cout << "Yes";
    else cout << "No";

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