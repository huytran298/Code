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
    vector<ll> a(n + 1);
    vector<ll> left(n + 2, 0);
    vector<ll> right(n + 2, 0);
    vector<ll> dis(n + 2, 0);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 2; i <= n; i ++){
        left[i] =left[i - 1] + (a[i] - a[i - 1]) / 2;
        right[n - i + 1] = right[n - i + 2] + abs(a[n - i + 1] - a[n - i + 2]) / 2;
        dis[i] = (a[i] - a[i - 1]) / 2;

    }
   
    for(int i = 1; i <= n; i ++){
        ll toRight = dis[i + 1] + max(right[i + 1], left[i]);
        ll toLeft = dis[i] + max(right[i], left[i - 1]);
        cout << min(toLeft, toRight) << endl;;
    }
}