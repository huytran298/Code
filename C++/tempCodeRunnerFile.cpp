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
    ll c[6] ;
    for(int i = 0; i < 6; i ++)c[i] = 0;
    c[0] = -2;
    c[1] = 1;
    for(int z = 1; z <= 5; z ++){
        ll ctemp[6];
        for(int i = 0; i < 6; i ++)ctemp[i] = 0;
        for(int diff = 0; diff <= 5; diff ++){
            for(int l = -2; l <= 2; l ++){
                ctemp[diff] += c[abs(diff + l)];
            }
            for(ll k = 0; k <= 5; k ++){
                c[k] = ctemp[k];
            }
        }
    }
    for(int i = 0; i < 6; i ++)cout << c[i] << ' ';
    
}