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
bool cmp(const pair<ll, ll> &a, const pair<ll, ll> &b){
    if(a.first != b.first)return a.first < b.first;
    return a.second < b.second;
}

ll process(vector<pair<ll, ll>> pr){
    ll ans = 1, cnt = 1;
    if(pr.size() == 0)return 0;
    for(int i = 1; i < pr.size(); i ++){
        if(pr[i] == pr[i - 1])cnt ++;
        else cnt = 1;
        ans = max(ans, cnt);
    }
    return ans;
}

void solve(){
    ll n;
    cin >> n;
    ll a[n + 1], b[n + 1];
    for(int i = 1; i <= n; i ++)cin >> a[i];
    for(int i = 1; i <= n; i ++)cin >> b[i];
    //vector<ll> gcds(n + 1, -1), frac(n + 1, 0), status(n + 1, 0);
    ll spc = 0, spc1 = 0;
    map<ll, vector<pair<ll, ll>>> pr;
    for(int i = 1; i <= n; i ++){
        ll tmp = gcd(abs(a[i]), abs(b[i]));
        if(a[i] * b[i] > 0){
            pr[1].pb({abs(a[i]) / tmp, abs(b[i])  / tmp});
        }else if(a[i] * b[i] < 0){
            pr[0].pb({abs(a[i]) / tmp, abs(b[i]) / tmp});
        }else {
            if(a[i] == 0 && b[i] == 0)spc ++;
            else if(b[i] == 0)spc1 ++;
        }
    }

    sort(bend(pr[0]), cmp);
    sort(bend(pr[1]), cmp);
    
    cout << spc + max(spc1, max(process(pr[0]), process(pr[1])));
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