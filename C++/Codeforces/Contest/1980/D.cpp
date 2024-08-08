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
bool isIncrease(deque<ll> v){
    for(int i = 1; i < v.size(); i ++)if(v[i] < v[i - 1])return 0;
    return 1;
}
void solve(){
    ll n;
    cin >> n;
    ll a[n + 1];
    for(int i = 1; i <= n; i ++)cin >> a[i];
    deque<ll> b (n, 0);
    ll pos = 0, pos1 = 0;
    for(int i = 1; i < n; i ++){
        b[i] = gcd(a[i], a[i + 1]);;
        if(b[i] < b[i - 1] && pos == 0)pos = i;
    }
    
    for(int i = max(pos - 3, 1LL); i <= min(pos + 3, n); i ++){
        deque<ll> tm = b;
        if(i == 1)tm.erase(tm.begin() + 1);
        else if(i == n)tm.pop_back();
        else {
            tm.erase(tm.begin() + i - 1, tm.begin() + i + 1);
            tm.insert(tm.begin() + i - 1, gcd(a[i - 1], a[i + 1]));
        }
        
        if(isIncrease(tm))return void (cout << "YES");
    }
    cout << "NO";
}

signed main(){
    fast; 
    ll t = 1;
    cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}