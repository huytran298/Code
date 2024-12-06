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
    ll n, k;
    cin >> n >> k;
    //ll a[n + 1];
    vector<ll> a(n), cnt(1001, 0);
    set<ll> q;
    for(int i = 0; i < n; i ++){
        cin >> a[i];
        cnt[a[i]] ++;
        q.insert(a[i]);
        
    }
    //sort(bend(a));
    ll tmp = 0;
    for(auto x : q){
        if(tmp >= k)break;
        //cout << cnt[x] << ' ';
        tmp += cnt[x];
    }
    //cout << tmp;
    if(tmp == k)cout << "YES";
    else cout << "NO";
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