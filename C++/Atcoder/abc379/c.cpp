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
bool cmp(pair<ll, ll> &a, pair<ll, ll> &b){
    return a.first < b.first;
}
void solve(){
    ll n, m;
    cin >> n >> m;
    vector<ll> x(m + 1), a(m + 1);
    vector<pair<ll, ll>> cells;
    ll sum = 0;
    for(int i = 1; i <= m; i ++)cin >> x[i];
    for(int i = 1; i <= m; i ++){
        cin >> a[i];
        sum += a[i];
        cells.pb({x[i], a[i]});
    }
    if(sum != n)return void (cout << -1);
    sort(bend(cells), cmp);
    //if(cells[m - 1].first == n || cells[0].first != 1)return void (cout << -1);
    ll ans = 0;
    //cells.pb({n, 0});
    for(int i = 1; i < m; i ++){
        if(cells[i].first - cells[i - 1].first > cells[i - 1].second)return void (cout << -1);
        ll tmp = cells[i - 1].second, tmp1 = (cells[i - 1].second - (cells[i].first - cells[i - 1].first));
        ans += ((tmp - 1) * tmp)/2LL - ((tmp1 - 1) * tmp1) / 2LL;
        cells[i].second += (cells[i - 1].second - (cells[i].first - cells[i - 1].first)); 
    }
    
    if(n - cells[m - 1].first != cells[m - 1].second - 1)return void (cout << -1);
    ll tmp = cells[m - 1].second - 1;
    ans += (((tmp + 1) * tmp) / 2LL);
    cout << ans;
}

signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}