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
bool cmp (pair<ll, ll> &a , pair<ll, ll> &b){return a.first > b.first;}
void solve(){
    ll n, m;
    cin >> n >> m;
    vector<ll> fl(n + 1), qt(n + 1);
    for(int i = 1; i <= n; i ++)cin >> fl[i];
    for(int i = 1; i <= n; i ++)cin >> qt[i];
    vector<pair<ll, ll>> ls;
    for(int i = 1; i <= n; i ++)ls.pb({fl[i], qt[i]});
    sort(bend(ls), cmp);
    ll ans = 0, l = 0;
    for(int i = 1; i < n; i ++){
        if(ls[l].first - ls[i].first > 1){
            ll num = m - (ls[l].first * ls[l].second);
            ans = max(ans, (ls[l].first * ls[l].second) + ls[i].first * min(num / ls[i].first, ls[i].second));
            if(ls[i - 1].first - ls[i].first <= 1)l = i - 1;
            else l = i;
            continue;
        }else if(ls[i - 1].first * ls[i - 1].second + ls[i].first * ls[i].second > m){
            ll num = m - (ls[l].first * ls[l].second);
            ans = max(ans, (ls[l].first * ls[l].second) + ls[i].first * min(num / ls[i].first, ls[i].second));
            num = m - (ls[i].first * ls[i].second);
            ans = max(ans, (ls[i].first * ls[i].second) + ls[i - 1].first * min(num / ls[i - 1].first, ls[i - 1].second));
            l = i;
            continue;
        }
    }
    cout << ans;
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