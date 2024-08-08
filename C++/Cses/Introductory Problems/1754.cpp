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
ll bina(ll a, ll b){
    ll l = 0, r = (ll)1e10;
    while(l <= r){
        ll mid = (l + r) >> 1LL;
        if((a - (2 * mid) - (b - mid)) == 0)return mid;
        else if((a - (2 * mid) - (b - mid)) < 0)r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}
void solve(){
    ll a, b;
    cin >> a >> b;
    if(a < b)swap(a, b);
    ll k = a - b;
    if(a == 0 && b == 0)return void (cout << "YES");
    if(k == -1 || min(a, b) == 0 || (2 * k > a) || k > b)return void (cout << "NO");
    a -= 2 * k;
    b -= k;
    if(a == b && a % 3 == 0)return void (cout << "YES");
    else if(a == b)return void (cout << "NO");
    


    
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