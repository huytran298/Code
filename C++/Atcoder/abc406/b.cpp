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
ll countNum(ll n){
    ll cnt = 0;
    while(n > 0){
        cnt ++;
        n /= 10;
    }
    return max(cnt, 1LL);
}
signed main(){
    fast; 
    ll n, k;
    cin >> n >> k;
    ll num = 1;
    ll L = pow(10LL, 18);
    for(int i = 1; i <= n; i ++){
        ll x; cin >> x;
        ll p;
        
        if(num >= 2 * L / x || countNum(num * x) > k)num = 1LL;
        else {
            num *= x;
        }
        //cout << num << endl;
    }
    cout << num;
}