#include<bits/stdc++.h>
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
    vector<string> s(n + 1);
    vector<ll> pts(n + 1, 0);
    for(int i = 1; i <= n; i ++)cin >> s[i];
    for(int i = 0; i < m; i ++){
        vector<ll> x, y;
        for(int j = 1; j <= n; j ++){
            if(s[j][i] == '0')x.pb(j);
            else y.pb(j);
        }
        if(!x.size() || !y.size())continue;
        else if(x.size() > y.size()){
            for(auto v : y){
                pts[v] ++;
            }
        }else {
            for(auto v : x){
                pts[v] ++;
            }
        }
    }
    ll maxpts = 0;
    for(int i = 1; i <= n; i ++){
        maxpts = max(maxpts, pts[i]);
    }
    for(int i = 1; i <= n; i ++){
        if(maxpts == pts[i])cout << i << ' ';
    }
    
    
}