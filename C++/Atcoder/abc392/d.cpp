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
void solve(){
    vector num(maxN, pair<double, double>(0, 0));
    ll n;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        ll k;
        cin >> k;
        map<ll, double> cnt;
        set<ll> numFace;
        for(int i = 1; i <= k; i ++){
            ll x;
            cin >> x;
            cnt[x] ++;
            numFace.insert(x);
        }
        for(double x : numFace){
            double prob = cnt[x] / (double)k;
            if(num[x].second < prob && num[x].first != infi)num[x].second = prob;
            else if(num[x].first < prob)num[x].first = prob;
        }
    }
    double ans = 0.0;
    for(int i = 1; i <= maxN; i ++){
        maxSelf(ans, num[i].first * num[i].second);
    }
    cout << fixed << setprecision(7) << ans;

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