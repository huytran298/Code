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
    ll n, k, T;
    cin >> n >> k >> T;
    vector<ll> a(n, 0);
    for(int i = 0; i < n; i ++){
        cin >> a[i];
    }
    //cout << "T";
    ll t = 0, idx = 0;
    ll ans = 0;
    sort(bend(a));
    vector<ll> space(n, 0);
    /*
        a_i + n * k <= a_{i + 1}
        n <= (a_{i + 1} - a{i}) / k 
    */
    ll sum = 0;
    for(int i = 0; i < n - 1; i ++){
        if(a[idx] < T){
            ll q = ceil(double(min(a[i + 1], T) - (a[i] + k)) / (double)k);
            space[i] = q;
            sum += (q);
        }else break;
    }
    if(a[n - 1] < T){
        space[n - 1] = ceil(double(T - a[n - 1]) / (double)k) - 1;
        sum += space[n - 1];
    }
    cout << sum + ceil(double(a[0]) / (double)k);
    
    
}