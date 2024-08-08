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
    string s, t;
    ll n;
    cin >> n;
    cin >> s >> t;
    ll cnt = 0;
    vector<vector<ll>> ps(500);
    vector<ll> cq;
    for(int i = 0; i < s.size(); i ++){
        if(s[i] != t[i]){
            cnt ++;
            ps[s[i]].pb(i);
            cq.pb(t[i]);
        }
    }
    if(cnt == 0)return void (cout << 0);
    else if(cnt == 1)return void (cout << 1 << "\n-1 -1");
    vector<ll> crs;
    for(auto x : cq){
        if(!ps[x].empty())crs.pb(x);
        if(crs.size() == 2)break;
    }
    if(crs.size() == 2){
        cout << cnt - 2 << endl;
        cout << ps[crs.front()].back() + 1 << ' ';
        ps[crs.front()].pop_back();
        cout << ps[crs.back()].back() + 1;
    }else if(crs.size() == 1) {
        cout << cnt - 1 << endl;
        for(int i = 0; i < s.size(); i ++){
            if(s[i] != t[i] && !ps[t[i]].empty()){
                cout << i + 1 << ' ' << ps[t[i]].back() + 1;
                return;
            }
        }
    }else {cout << cnt << "\n-1 -1";}
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