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
    string a, b;
    cin >> a >> b;
    vector<vector<ll>> chr1(n + 1, vector<ll> ('z' + 1, 0)), chr2(n + 1, vector<ll> ('z' + 1, 0));
    chr1[0][a[0]] ++;
    chr2[0][b[0]] ++;
    for(int i = 1; i <= n; i ++){
        for(int j = 'a'; j <= 'z'; j ++){
            chr1[i][j] = chr1[i - 1][j];
            chr2[i][j] = chr2[i - 1][j];
        }
        chr1[i][a[i - 1]] ++;
        chr2[i][b[i - 1]] ++;
    }
    for(int i = 1; i <= q; i ++){
        ll l, r;
        cin >> l >> r;
        ll ans = 0;
        for(int j = 'a'; j <= 'z'; j ++){
            ans += abs((chr1[r][j] - chr1[l - 1][j]) - (chr2[r][j] - chr2[l - 1][j]));
        }
        cout << ans / 2 << endl;
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