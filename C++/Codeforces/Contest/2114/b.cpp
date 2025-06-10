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

void run(){
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<ll> cnt(2, 0LL);
    for(auto x : s){
        cnt[x - '0'] ++;
    }
    ll tmpk = k;
    ll minT = min(cnt[0], cnt[1]), maxT = max(cnt[0], cnt[1]);
    ll tmp = (n / 2 - k);
    if(minT >= tmp){
        cnt[0] -= tmp;
        cnt[1] -= tmp;
        //cout << cnt[1] << ' ' << cnt[0];
        if(cnt[0] / 2 + cnt[1] / 2 == k)return void(cout << "YES");
    }
    cout << "NO";
}
signed main(){
    fast; 
    ll t;
    cin >> t;
    while(t --){
        run();
        cout << endl;
    }
}