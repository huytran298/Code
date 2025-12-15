#include<bits/stdc++.h>
#include<iostream>
using namespace std; 

#define ll long long
#define maxN (long long) 1e6 + 5
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

signed main(){
    fast; 
    ll n, m;
    cin >> n >> m;
    ll ans = 0;
    map<pair<ll,ll>, ll> table;
    for(int i = 1; i <= m; i ++){
        ll x, y;
        cin >> x >> y;
        vector<pair<ll, ll>> ls = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        ll failed = 0;
        for(auto u : ls){
            if(table[{x + u.first, y + u.second}] != 0)failed = 1;
        }
        if(failed) continue;
        ans ++;
        for(auto u : ls){
            table[{x + u.first, y + u.second}] = 1;
        }

    }
    cout << ans;
}