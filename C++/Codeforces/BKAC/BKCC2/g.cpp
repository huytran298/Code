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
#define modulo (ll)1000000007
int nxt(){ int n; cin >> n; return n;}
/*
 _  _             _____              
| || |_  _ _  _  |_   _| _ __ _ _ _  
| __ | || | || |   | || '_/ _` | ' \ 
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/                      
*/
//Luỹ thừa nhị phân

ll power(long long x, ll y, ll p) 
{ 
    ll res = 1;     // Initialize result 

    x = x % p; // Update x if it is more than or 
                // equal to p
 
    if (x == 0) return 0; // In case x is divisible by p;

    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x) % p; 

        // y must be even now 
        y = y>>1LL; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 

signed main(){
    fast; 
    ll t;
    cin >> t;
    while(t --){
        ll T, n;
        cin >> T >> n;
        vector<ll> a(2, T), PoW(2, 1);
        ll tmp = 1, sum = 0, cnt = 1;
        for(int i = 2; i <= n; i ++){
            if(i % 2 == 0){
                sum += PoW[i / 2 - 1];
                tmp = (tmp % modulo * a[i / 2 - 1] % modulo) % modulo;
                cnt ++;
                PoW.pb(sum);
                a.pb(tmp);
            }else {
                a.pb(a[a.size() - 1]);
                PoW.pb(PoW[PoW.size() - 1]);
            }
            //cout << tmp << ' ';
            
            
        }
        //for (auto x : a)cout << x << ' ';
        cout << a[n] << '\n';
    }
}