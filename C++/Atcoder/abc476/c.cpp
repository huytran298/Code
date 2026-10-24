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
    ll n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i ++){
        cin >> a[i];
    }
    vector<ll> s;
    for(int i = 0; i < 3; i ++)s.pb(a[i]);
    sort(rbend(s));
    ll max1 = s[0], max2 = s[1], max3 = s[2];
    cout << max3 << endl;
    for(int k = 3; k < n; k ++){
        if(max1 <= a[k]){
            max3 = max2;
            max2 = max1; 
            max1 = a[k];
        }else if(max2 <= a[k]){
            max3 = max2;
            max2 = a[k];
        }else if(max3 <= a[k]){
            max3 = a[k];
        }
        cout << max3 << endl;
    }
}